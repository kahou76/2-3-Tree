#pragma once
#include<iostream>
#include<memory>
#include<queue>
#include<string>
#include "Node.h"

using namespace std;

class Index{
private:
    shared_ptr<Node> root;

public:

    //public constructor
    Index(){
        root = nullptr;
    }

    //greater
    struct greater{
        bool operator()( shared_ptr<Key> l, shared_ptr<Key> r ){
            return l->getKey() > r->getKey();
        }
    };

    //Insert an element in the index, associate the integer value with the element
    void Insert(shared_ptr<string> strptr, int val){
        //same key same val
        if(Find(strptr) == val){
            cout << "same key with same val already inserted" << endl;

        //same key diff val -> replace the key with new val
        }else if(Find(strptr) != -99 && Find(strptr) != val){
            InsertHelp(root,strptr,val);
        }
        
        //diff key with same val or diff val
        else if(Find(strptr) == -99){
            InsertHelp(root,strptr,val);
        }

        //InsertHelp(root,strptr,val);
        
    }

    //Insert help
    void InsertHelp(shared_ptr<Node> curr, shared_ptr<string> strptr, int val){
        string str = *strptr;
        //Node newnode = Node(*strptr,val);
        Key newkey = Key(*strptr,val);
        shared_ptr<Key> newkeyptr = make_shared<Key>(newkey);
        shared_ptr<Node> newnodeptr = make_shared<Node>(*strptr,val);
        //priority_queue<shared_ptr<Key>,vector<shared_ptr<Key>>,greater> pq;

        //Base case
        if(curr == nullptr){
            //Empty, set root to the new one
            curr = newnodeptr;
            root = curr;
        }

        //If leaf, start inserting
        else if(curr->getLeft() == nullptr && curr->getMiddleLeft() == nullptr && curr->getMiddleRight() == nullptr  && curr->getRight() == nullptr){
            //If two node (A)
            if(IfTwoNode(curr)){
                //cout << "two two function is working" << endl;
                curr = AddTwoNode(curr,newkeyptr);

            }else if(IfThreeNode(curr)){ // three node (A B)
                // comes with a four node
                curr = AddThreeNode(curr,newkeyptr);

                //if parent is null
                if(curr->getParent() == nullptr){
                    curr = SplitWithNoParent(curr);
                    root = curr;
                }else {
                    //else merge the top one to the parent
                    //if parent is two node (A) 
                    //situation of left and right

                    //right
                    if(IfTwoNode(curr->getParent()) && curr->getParent()->getMiddleLeft() == curr){
                        curr->getParent()->setMiddleKey(curr->getMiddleKey());


                        curr->getParent() = SplitWithParentRightTwoNode(curr);
                    }

                    //left
                    if(IfTwoNode(curr->getParent()) && curr->getParent()->getLeft() == curr){
                        curr->getParent()->setMiddleKey(curr->getParent()->getSmallKey());
                        curr->getParent()->setSmallKey(curr->getMiddleKey());

                        curr->getParent() = SplitWithParentLeft(curr);
                        
                    }

                    //else the parent is three node (A B)
                    //situation of left, middle, right
                    // after insert it, fix the parent (A B C)

                    //left
                    if(IfThreeNode(curr->getParent()) && curr->getParent()->getLeft() == curr){
                        curr->getParent() = AddThreeNode(curr->getParent(),curr->getMiddleKey());


                        curr->getParent() = SplitWithParentLeft(curr);
                        
                    }

                    //right
                    if(IfThreeNode(curr->getParent()) && curr->getParent()->getRight() == curr){
                        // curr->getParent()->setLargeKey(curr->getMiddleKey());

                        // curr->getParent() = SplitWithParentRightThreeNode(curr);

                        

                        //while(curr->getParent() != nullptr){
                            curr->getParent()->setLargeKey(curr->getMiddleKey());
                            curr->getParent() = SplitWithParentRightThreeNode(curr);
                            cout << "top small: " << curr->getParent()->getSmallKey()->getKey() << " top mid: " << curr->getParent()->getMiddleKey()->getKey() 
                            << " top large: " << curr->getParent()->getLargeKey()->getKey() << endl;
                            cout << "small left: " << curr->getParent()->getLeft()->getSmallKey()->getKey() << endl;
                            cout << "small midleft: " << curr->getParent()->getMiddleLeft()->getSmallKey()->getKey() << endl;
                            cout << "small midright: " << curr->getParent()->getMiddleRight()->getSmallKey()->getKey() << endl;
                            cout << "small right: " << curr->getParent()->getRight()->getSmallKey()->getKey() << endl;
                            //curr = curr->getParent();
                        //}

                        if(curr->getParent()->getParent() == nullptr){
                            curr->getParent() = SplitWithNoParent(curr->getParent());
                            PrintHelp(curr->getParent());
                            // cout << "top: " << curr->getParent()->getSmallKey()->getKey() << " left: " << curr->getParent()->getLeft()->getSmallKey()->getKey() 
                            // << " right: " << curr->getParent()->getMiddleLeft()  ->getSmallKey()->getKey() << endl;
                             root = curr->getParent();
                        }
                    }

                    //middle
                    if(IfThreeNode(curr->getParent()) && curr->getParent()->getMiddleLeft() == curr){
                        curr->getParent()->setLargeKey(curr->getParent()->getMiddleKey());
                        curr->getParent()->setMiddleKey(curr->getMiddleKey());

                        shared_ptr<Node> middleleft = make_shared<Node>(curr->getSmallKey());
                        shared_ptr<Node> middleright = make_shared<Node>(curr->getLargeKey());

                        curr->getParent()->setMiddleLeft(middleleft);
                        middleleft->setParent(curr->getParent());

                        curr->getParent()->setMiddleRight(middleright);
                        middleright->setParent(curr->getParent());

                        if(curr->getLeft() != nullptr){
                            middleleft->setLeft(curr->getLeft());
                            curr->getLeft()->setParent(middleleft);
                        }

                        if(curr->getMiddleLeft() != nullptr){
                            middleleft->setMiddleLeft(curr->getMiddleLeft());
                            curr->getMiddleLeft()->setParent(middleleft);
                        }

                        if(curr->getMiddleRight() != nullptr){
                            middleright->setLeft(curr->getMiddleRight());
                            curr->getMiddleRight()->setParent(middleright);
                        }
                        
                        if(curr->getRight() != nullptr){
                            middleright->setMiddleLeft(curr->getRight());
                            curr->getRight()->setParent(middleright);
                        }



                    }
                }

            }
        }

        //Search
        //if twonode (A)
        else if(IfTwoNode(curr)){

            //when see the same key, replace it with diff val
            if(str.compare(curr->getSmallKey()->getKey()) == 0){
                curr->getSmallKey()->setValue(val);
            }

            else if(str.compare(curr->getSmallKey()->getKey()) < 0){
                 InsertHelp(curr->getLeft(),strptr,val);
            }else{
                InsertHelp(curr->getMiddleLeft(),strptr,val);
            }
            
        }

        //if three node (A B)
        else if(IfThreeNode(curr)){
            
            //when seeing the same key, replace with new val
            if(str.compare(curr->getSmallKey()->getKey()) == 0){
               curr->getSmallKey()->setValue(val);
            }

            else if(str.compare(curr->getSmallKey()->getKey()) < 0){
                InsertHelp(curr->getLeft(),strptr,val);
            }

            //when seeing the same key, replace with new val
            else if(str.compare(curr->getMiddleKey()->getKey()) == 0){
                curr->getMiddleKey()->setValue(val);
            }

            else if(str.compare(curr->getSmallKey()->getKey()) > 0 && str.compare(curr->getMiddleKey()->getKey()) < 0){
               InsertHelp(curr->getMiddleLeft(),strptr,val);
            }

            else{
                InsertHelp(curr->getRight(),strptr,val);
            }
        }



        
    }

    //Find an element in the index
    int Find(shared_ptr<string> strptr){
        return FindHelp(root,strptr);
    }

    //Find Help
    int FindHelp(shared_ptr<Node> curr, shared_ptr<string> strptr){
        string str = *strptr;
        //Base
        if(curr == nullptr){
            return -99;
        }

        //if leaf
        else if(curr->getLeft() == nullptr && curr->getMiddleLeft() == nullptr && curr->getMiddleRight() == nullptr  && curr->getRight() == nullptr){
            if(IfTwoNode(curr)){
                //two node
                if(str.compare(curr->getSmallKey()->getKey()) == 0){
                    return curr->getSmallKey()->getValue();
                }
            }else{
                //three
                if(str.compare(curr->getSmallKey()->getKey()) == 0){//small
                    return curr->getSmallKey()->getValue();
                }else if(str.compare(curr->getMiddleKey()->getKey()) == 0){//large
                    return curr->getMiddleKey()->getValue();
                }

            }
        }

        //If two node with children
        else if(IfTwoNode(curr)){

            if(str.compare(curr->getSmallKey()->getKey()) == 0){
                return curr->getSmallKey()->getValue();
            }

            else if(str.compare(curr->getSmallKey()->getKey()) < 0){
                return FindHelp(curr->getLeft(),strptr);
            }else{
                return FindHelp(curr->getMiddleLeft(),strptr);
            }
            
        }else{//three with children
            if(str.compare(curr->getSmallKey()->getKey()) == 0){
                return curr->getSmallKey()->getValue();
            }

            else if(str.compare(curr->getSmallKey()->getKey()) < 0){
                return FindHelp(curr->getLeft(),strptr);
            }

            else if(str.compare(curr->getMiddleKey()->getKey()) == 0){
                return curr->getMiddleKey()->getValue();
            }

            else if(str.compare(curr->getSmallKey()->getKey()) > 0 && str.compare(curr->getMiddleKey()->getKey()) < 0){
                return FindHelp(curr->getMiddleLeft(),strptr);
            }

            else{
                return FindHelp(curr->getRight(),strptr);
            }

        }




        return -99;
    }

    //Remove an element from the index
    void Remove(shared_ptr<string> str);

    //Print travserse, visit the key
    void Print(){
        PrintHelp(root);
    }

    //Print Help
    void PrintHelp(shared_ptr<Node> curr){
        if(curr == nullptr){
            return;
        }

        //if leaf
        else if(curr->getLeft() == nullptr && curr->getMiddleLeft() == nullptr && curr->getMiddleRight() == nullptr && curr->getRight() == nullptr){
            //If two node
            if(IfTwoNode(curr)){
                cout << "TwoNode key: " << curr->getSmallKey()->getKey() << " TwoNode Value: " << curr->getSmallKey()->getValue() << endl;
            }else{
                //Is three node then
                cout << "ThreeNode Small key: " << curr->getSmallKey()->getKey() << " ThreeNode Small Value: " << curr->getSmallKey()->getValue() << endl;
                cout << "ThreeNode Middle key: " << curr->getMiddleKey()->getKey() << " ThreeNode Middle Value: " << curr->getMiddleKey()->getValue() << endl;

            }
        }

        //two node
        else if(IfTwoNode(curr)){
            PrintHelp(curr->getLeft());
            cout << "TwoNode key: " << curr->getSmallKey()->getKey() << " TwoNode Value: " << curr->getSmallKey()->getValue() << endl;
            PrintHelp(curr->getMiddleLeft());
        }else{
            //three node
            PrintHelp(curr->getLeft());
            cout << "TwoNode Small key: " << curr->getSmallKey()->getKey() << " TwoNode Small Value: " << curr->getSmallKey()->getValue() << endl;
            PrintHelp(curr->getMiddleLeft());
            cout << "ThreeNode Middle key: " << curr->getMiddleKey()->getKey() << " ThreeNode Middle Value: " << curr->getMiddleKey()->getValue() << endl;
            PrintHelp(curr->getRight());



        }
    }

    //If two node 
    // (A)
    bool IfTwoNode(shared_ptr<Node> curr){ 
        //return curr->getLStr() == "" && curr->getLValue() == -99;
        return curr->getSmallKey() != nullptr && curr->getMiddleKey() == nullptr && curr->getLargeKey() == nullptr;
    }

    //If three node
    // (A B)
    bool IfThreeNode(shared_ptr<Node> curr){
        //return curr->getLStr() != "" && curr->getLValue() != -99;
        return curr->getSmallKey() != nullptr && curr->getMiddleKey() != nullptr && curr->getLargeKey() == nullptr;
    }

    // if four node
    // (A B C)
    bool IfFourNode(shared_ptr<Node> curr){
        //return curr->getLStr() != "" && curr->getLValue() != -99;
        return curr->getSmallKey() != nullptr && curr->getMiddleKey() != nullptr && curr->getLargeKey() != nullptr;
    }

    //inserting two node situation
    shared_ptr<Node> AddTwoNode(shared_ptr<Node> curr,shared_ptr<Key> newkeyptr){
        priority_queue<shared_ptr<Key>,vector<shared_ptr<Key>>,greater> pq;
        pq.push(curr->getSmallKey());
        pq.push(newkeyptr);
        shared_ptr<Key> small = pq.top();
        pq.pop();
        shared_ptr<Key> middle = pq.top();
        pq.pop();
        curr->setSmallKey(small);
        curr->setMiddleKey(middle);
        // cout << "two node small key: " << curr->getSmallKey()->getKey() << " two node small value: " << curr->getSmallKey()->getValue() << endl;
        // cout << "two node middle key: " << curr->getMiddleKey()->getKey() << " two node small value: " << curr->getMiddleKey()->getValue() << endl;

        return curr;
    }

    //inserting three node situation
    shared_ptr<Node> AddThreeNode(shared_ptr<Node> curr,shared_ptr<Key> newkeyptr){
        priority_queue<shared_ptr<Key>,vector<shared_ptr<Key>>,greater> pq;
        pq.push(curr->getSmallKey());
        pq.push(curr->getMiddleKey());
        pq.push(newkeyptr);
        shared_ptr<Key> small = pq.top();
        pq.pop();
        shared_ptr<Key> middle = pq.top();
        pq.pop();
        shared_ptr<Key> large = pq.top();
        pq.pop();
        curr->setSmallKey(small);
        curr->setMiddleKey(middle);
        curr->setLargeKey(large);
        return curr;
    }

    //split with no parent (A B C)
    shared_ptr<Node> SplitWithNoParent(shared_ptr<Node> curr){
        shared_ptr<Node> left, top, right;  
        left = make_shared<Node>(curr->getSmallKey());
        cout << curr->getSmallKey()->getKey() << endl;
        top = make_shared<Node>(curr->getMiddleKey());
        cout << curr->getMiddleKey()->getKey() << endl;
        right = make_shared<Node>(curr->getLargeKey());
        cout << curr->getLargeKey()->getKey() << endl;


        top->setLeft(left);
        left->setParent(top);
        top->setMiddleLeft(right);
        right->setParent(top);
        

        if(curr->getLeft() != nullptr){
            left->setLeft(curr->getLeft());
            curr->getLeft()->setParent(left);
        }
        
        if(curr->getMiddleLeft() != nullptr){
            left->setMiddleLeft(curr->getMiddleLeft());
            curr->getMiddleLeft()->setParent(left);
        }
        
        if(curr->getMiddleRight() != nullptr){
            right->setLeft(curr->getMiddleRight());
            curr->getMiddleRight()->setParent(right);
        }

        if(curr->getRight() != nullptr){
            right->setMiddleLeft(curr->getRight());
            curr->getRight()->setParent(right);
        }

        return top;
    }

    //split with parent (left)
    shared_ptr<Node> SplitWithParentLeft(shared_ptr<Node> curr){
        shared_ptr<Node> left = make_shared<Node>(curr->getSmallKey());
        shared_ptr<Node> middleleft = make_shared<Node>(curr->getLargeKey());

        curr->getParent()->setLeft(left);
        left->setParent(curr->getParent());
        curr->getParent()->setMiddleLeft(middleleft);
        middleleft->setParent(curr->getParent());

        if(curr->getLeft() != nullptr){
            left->setLeft(curr->getLeft());
            curr->getLeft()->setParent(left);
        }

        if(curr->getMiddleLeft() != nullptr){
            left->setMiddleLeft(curr->getMiddleLeft());
            curr->getMiddleLeft()->setParent(left);
        }

        if(curr->getMiddleRight() != nullptr){
            middleleft->setLeft(curr->getMiddleRight());
            curr->getMiddleLeft()->setParent(middleleft);
        }

         if(curr->getRight() != nullptr){
            middleleft->setMiddleLeft(curr->getRight());
            curr->getRight()->setParent(middleleft);
        }
        
        return curr->getParent();
}

    //split with parent (right) twonode
     shared_ptr<Node> SplitWithParentRightTwoNode(shared_ptr<Node> curr){
        shared_ptr<Node> middleleft = make_shared<Node>(curr->getSmallKey());
        shared_ptr<Node> right = make_shared<Node>(curr->getLargeKey());

        curr->getParent()->setMiddleLeft(middleleft);
        middleleft->setParent(curr->getParent());
        curr->getParent()->setRight(right);
        right->setParent(curr->getParent());

        if(curr->getLeft() != nullptr){
            middleleft->setLeft(curr->getLeft());
            curr->getLeft()->setParent(middleleft);
        }

        if(curr->getMiddleLeft() != nullptr){
            middleleft->setMiddleLeft(curr->getMiddleLeft());
            curr->getMiddleLeft()->setParent(middleleft);
        }

        if(curr->getMiddleRight() != nullptr){
            right->setLeft(curr->getMiddleRight());
            curr->getMiddleRight()->setParent(right);
        }

        if(curr->getRight() != nullptr){
            right->setMiddleLeft(curr->getRight());
            curr->getRight()->setParent(right);
        }

        return curr->getParent();
     }


    //split with parent (right) threenode
    shared_ptr<Node> SplitWithParentRightThreeNode(shared_ptr<Node> curr){
        shared_ptr<Node> middleright = make_shared<Node>(curr->getSmallKey());
        shared_ptr<Node> right = make_shared<Node>(curr->getLargeKey());

        curr->getParent()->setMiddleRight(middleright);
        middleright->setParent(curr->getParent());
        curr->getParent()->setRight(right);
        right->setParent(curr->getParent());

        if(curr->getLeft() != nullptr){
            middleright->setLeft(curr->getLeft());
            curr->getLeft()->setParent(middleright);
        }

        if(curr->getMiddleLeft() != nullptr){
            middleright->setMiddleLeft(curr->getMiddleLeft());
            curr->getMiddleLeft()->setParent(middleright);
        }

        if(curr->getMiddleRight() != nullptr){
            right->setLeft(curr->getMiddleRight());
            curr->getMiddleRight()->setParent(right);
        }

        if(curr->getRight() != nullptr){
            right->setMiddleLeft(curr->getRight());
            curr->getRight()->setParent(right);
        }

        return curr->getParent();
     }

    





    //when !IfTwoNode and !IfThreeNode, then there are one node trying to merge into a three node
    // void split(shared_ptr<Node> curr){
    //     //compare three string and arrange them
    //     //pq push all string into it
    //     shared_ptr<Node> left, top, right;
    //     //top->getLeft() == left;
    //     //top->getMiddle() == right;
    // }



};