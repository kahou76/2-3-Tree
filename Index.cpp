#include "Index.h"

//public constructor
    Index::Index(){
        root = nullptr;
    }


    //Insert an element in the index, associate the integer value with the element
    void Index::Insert(shared_ptr<string> strptr, int val){
        //same key same val
        if(Find)
        if(Find(strptr) == val){
            cout << "same key with same val already inserted" << endl;
            return;
        }else{
            InsertHelp(root,strptr,val);
        }

        
    }

    //Insert help
    void Index::InsertHelp(shared_ptr<Node> curr, shared_ptr<string> strptr, int val){
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

                Split(curr);

            }
        }

    

        //Search
        //if twonode (A)
        else if(IfTwoNode(curr)){

            //when see the same key, replace it with diff val
            if(str.compare(curr->getSmallKey()->getKey()) == 0){
                curr->getSmallKey()->setValue(val);
                //cout << "1" << endl;
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
               //cout << "2" << endl;
            }

            else if(str.compare(curr->getSmallKey()->getKey()) < 0){
                InsertHelp(curr->getLeft(),strptr,val);
            }

            //when seeing the same key, replace with new val
            else if(str.compare(curr->getMiddleKey()->getKey()) == 0){
                curr->getMiddleKey()->setValue(val);
                //cout << "3" << endl;
            }

            else if(str.compare(curr->getSmallKey()->getKey()) > 0 && str.compare(curr->getMiddleKey()->getKey()) < 0){
               InsertHelp(curr->getMiddleLeft(),strptr,val);
            }

            else{
                InsertHelp(curr->getRight(),strptr,val);
            }
        }



        
    }

    //Split Main Function
    void Index::Split(shared_ptr<Node> curr){
        //START SPLITING
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
            else if(IfTwoNode(curr->getParent()) && curr->getParent()->getLeft() == curr){
                curr->getParent()->setMiddleKey(curr->getParent()->getSmallKey());
                curr->getParent()->setSmallKey(curr->getMiddleKey());

                curr->getParent() = SplitWithParentLeftTwoNode(curr);
                
            }

            //else the parent is three node (A B)
            //situation of left, middle, right
            // after insert it, fix the parent (A B C)

            //left
            else if(IfThreeNode(curr->getParent()) && curr->getParent()->getLeft() == curr){
                curr->getParent() = AddThreeNode(curr->getParent(),curr->getMiddleKey());
                curr->getParent() = SplitWithParentLeftThreeNode(curr);

                Split(curr->getParent());
                
            }

            //right
            else if(IfThreeNode(curr->getParent()) && curr->getParent()->getRight() == curr){

                curr->getParent()->setLargeKey(curr->getMiddleKey());
                curr->getParent() = SplitWithParentRightThreeNode(curr);


                //no matter what the parent has to be split
                Split(curr->getParent());

            }

            //middle
            else if(IfThreeNode(curr->getParent()) && curr->getParent()->getMiddleLeft() == curr){
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

                Split(curr->getParent());

            }
        }    
    }


    //Find an element in the index
    int Index::Find(shared_ptr<string> strptr){
        return FindHelp(root,strptr);
    }

    //Find Help
    int Index::FindHelp(shared_ptr<Node> curr, shared_ptr<string> strptr){
        string str = *strptr;
        //Base
        if(curr == nullptr){
            return -1;
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




        return -1;
    }

   


    //Remove an element from the index
    void Index::Remove(shared_ptr<string> strptr){
        //If cant find, return
        if(Find(strptr) == -1){
            
            return;
        }

        //Search the key strptr and delele it
        string str = *strptr;
        //Base
        if(root == nullptr){
            //return -99;
            return;
        }

        //cout << "string: "<< str << endl;
        //Base case when only one node in tree
        if(IfTwoNode(root)  && Ifleaf(root)){
            //cout << "yes I enter" << endl;
            root->setSmallKey(nullptr);
            //curr = nullptr;
            //cout << "asssdss" << endl;
            root = nullptr;
            //cout << "2131321" << endl;
        }
        //cout << "string passed: "<< str << endl;

        shared_ptr<Node> curr = root;
        while(curr != nullptr){

        //if leaf
        if(Ifleaf(curr)){
            
            //cout << "Entering DELELEAF" << endl;
            DeleteLeaf(curr,str);
            break;
        }

        //If internal Node:
        //If two node with children
        else if(IfTwoNode(curr)){

            if(str.compare(curr->getSmallKey()->getKey()) == 0){
                //replace curr with two node
                ReplaceTwoNode(curr);
                break;
            }

            else if(str.compare(curr->getSmallKey()->getKey()) < 0){
                //return FindHelp(curr->getLeft(),strptr);
                 curr = curr->getLeft();
            }else{
                //return FindHelp(curr->getMiddleLeft(),strptr);
                
                curr = curr->getMiddleLeft();
            }
            
        }else{//three with children
            if(str.compare(curr->getSmallKey()->getKey()) == 0){
                //return curr->getSmallKey()->getValue();
                
                ReplaceThreeNodeSmall(curr);
                break;
            }

            else if(str.compare(curr->getSmallKey()->getKey()) < 0){
                 //RemoveHelp(curr->getLeft(),strptr);
                 curr = curr->getLeft();
            }

            else if(str.compare(curr->getMiddleKey()->getKey()) == 0){
                //return curr->getMiddleKey()->getValue();
                ReplaceThreeNodeMid(curr);
                break;
            }

            else if(str.compare(curr->getSmallKey()->getKey()) > 0 && str.compare(curr->getMiddleKey()->getKey()) < 0){
                 //RemoveHelp(curr->getMiddleLeft(),strptr);
                 curr = curr->getMiddleLeft();
            }

            else{
                //  RemoveHelp(curr->getRight(),strptr);
                curr = curr->getRight();
            }

        }

        }

        
        //cout << "test: " << root->getSmallKey()->getKey() << endl;
        //return -1;
    }

    //Restructure Left Leaf
    void Index::RestructureLeftNodeLeaf(shared_ptr<Node>& curr){

        //middle friend has three node
        if(IfThreeNode(curr->getParent()->getMiddleLeft())){
            //RedistributeLeft(curr);
            curr->setSmallKey( curr->getParent()->getSmallKey());
            curr->getParent()->setSmallKey(curr->getParent()->getMiddleLeft()->getSmallKey());
            curr->getParent()->getMiddleLeft()->setSmallKey(curr->getParent()->getMiddleLeft()->getMiddleKey());
            curr->getParent()->getMiddleLeft()->setMiddleKey(nullptr);

            if(!Ifleaf(curr)){
                //connect all bottom lines
                //from Merge Left
                if(curr->getLeft() != nullptr){
                    //curr->setLeft(curr->getMiddleLeft());
                    curr->setMiddleLeft(curr->getParent()->getMiddleLeft()->getLeft());
                    curr->getParent()->getMiddleLeft()->setLeft(curr->getParent()->getMiddleLeft()->getMiddleLeft());
                    curr->getParent()->getMiddleLeft()->setMiddleLeft(curr->getParent()->getMiddleLeft()->getRight());
                    curr->getParent()->getMiddleLeft()->setRight(nullptr);
                    //done
                }


                
            }
            
        }

        //pull the parent key down
        else { 
            
            curr->setSmallKey(curr->getParent()->getSmallKey());
            curr->getParent()->setSmallKey(curr->getParent()->getMiddleKey());
            curr->getParent()->setMiddleKey(nullptr);
            curr->setMiddleKey(curr->getParent()->getMiddleLeft()->getSmallKey());
            
            if(!Ifleaf(curr)){
                //connect all bottom lines
                //from Merge Left
                
                if(curr->getLeft() != nullptr){
                    
                    curr->setMiddleLeft(curr->getParent()->getMiddleLeft()->getLeft());
                    curr->setRight(curr->getParent()->getMiddleLeft()->getMiddleLeft());
                    
                    
                }

            }

            curr->getParent()->setMiddleLeft(curr->getParent()->getRight());
            curr->getParent()->setRight(nullptr);
        }

        


    }

    //Restructure Middle Leaf
    void Index::RestructureMiddleNodeLeaf(shared_ptr<Node>& curr){
        //right first
        if(IfThreeNode(curr->getParent()->getRight())){
            curr->setSmallKey(curr->getParent()->getMiddleKey());
            curr->getParent()->setMiddleKey(curr->getParent()->getRight()->getSmallKey());
            curr->getParent()->getRight()->setSmallKey(curr->getParent()->getRight()->getMiddleKey());
            curr->getParent()->getRight()->setMiddleKey(nullptr);
            if(!Ifleaf(curr)){
                if(curr->getLeft() != nullptr){
                    curr->setMiddleLeft(curr->getParent()->getRight()->getLeft());
                    curr = curr->getParent()->getRight();
                    curr->setLeft(curr->getMiddleLeft());
                    curr->setMiddleLeft(curr->getRight());
                    curr->setRight(nullptr);
                    //done
                }
            }
        }
        // then left
        else if(IfThreeNode(curr->getParent()->getLeft())){
            curr->setSmallKey(curr->getParent()->getSmallKey());
            curr->getParent()->setSmallKey(curr->getParent()->getLeft()->getMiddleKey());
            curr->getParent()->getLeft()->setMiddleKey(nullptr);  
            if(!Ifleaf(curr)){
                if(curr->getLeft() != nullptr){
                    curr->setMiddleLeft(curr->getLeft());
                    curr->setLeft(curr->getParent()->getLeft()->getRight());
                    curr = curr->getParent()->getLeft();
                    curr->setRight(nullptr);
                }
            }
        }
        // then all children are twonode (A)
        // move the parent mid key to right node
        else{
            
            curr->getParent()->getMiddleLeft()->setMiddleKey(curr->getParent()->getRight()->getSmallKey());
            curr->getParent()->getMiddleLeft()->setSmallKey(curr->getParent()->getMiddleKey());
            curr->getParent()->setMiddleKey(nullptr);
            if(!Ifleaf(curr)){
                if(curr->getLeft() != nullptr){
                    
                    curr->setMiddleLeft(curr->getParent()->getRight()->getLeft());
                    curr->setRight(curr->getParent()->getRight()->getMiddleLeft());
                }
            }
            curr->getParent()->setRight(nullptr);
           
        }
    }

    //Restructure Right Leaf
    void Index::RestructureRightNodeLeaf(shared_ptr<Node>& curr){
        //if middle is threenode
        if(IfThreeNode(curr->getParent()->getMiddleLeft())){
            curr->setSmallKey(curr->getParent()->getMiddleKey());
            curr->getParent()->setMiddleKey(curr->getParent()->getMiddleLeft()->getMiddleKey());
            curr->getParent()->getMiddleLeft()->setSmallKey(curr->getParent()->getMiddleLeft()->getMiddleKey());
            curr->getParent()->getMiddleLeft()->setMiddleKey(nullptr);
            if(!Ifleaf(curr)){
                if(curr->getLeft() != nullptr){
                    curr->setMiddleLeft(curr->getLeft());
                    curr->setLeft(curr->getParent()->getMiddleLeft()->getRight());
                    curr->getParent()->getMiddleLeft()->setRight(nullptr);
                }
            }
            //break;
        }
        
        //else parent merge into two node
        else{
            curr->getParent()->getMiddleLeft()->setMiddleKey(curr->getParent()->getMiddleKey());
            curr->getParent()->setMiddleKey(nullptr);
            if(!Ifleaf(curr)){
                if(curr->getLeft() != nullptr){
                    curr->getParent()->getMiddleLeft()->setRight(curr->getLeft());
                }
            }
                
            curr->getParent()->setRight(nullptr);

            //break;
            
        }
    }

    //Restructure 
    void Index::Restructure(shared_ptr<Node>& curr){
        // left
        if(curr->getParent()->getLeft() == curr){
           
            RestructureLeftNodeLeaf(curr);            
        }
        // mid
        else if(curr->getParent()->getMiddleLeft() == curr){
            
            RestructureMiddleNodeLeaf(curr);
        }
        // right
        else if(curr->getParent()->getRight() == curr){
            
            RestructureRightNodeLeaf(curr);
        }
    }

    //Delete Leaf
    //curr taking the leaf node
    void Index::DeleteLeaf(shared_ptr<Node>& curr,string str){
        //Base case when only one node in tree
        // if(IfTwoNode(curr)&& curr->getParent()==nullptr  && Ifleaf(curr)){
        //     curr->setSmallKey(nullptr);
        //     //curr = nullptr;
        //     root = nullptr;
        // }

        //delete leaf
            if(IfTwoNode(curr)){
                //two node
                if(str.compare(curr->getSmallKey()->getKey()) == 0){
                    //return curr->getSmallKey()->getValue();
                    //Check if parent are two node or three node

                    //cout << "OK it is two node" << endl;
                    //If parent is threenode
                    if(IfThreeNode(curr->getParent())){
                        Restructure(curr);
                        
                    }
                    //Parent is two node
                    else
                    {
                        //delete MiddleLeft
                        if(curr->getParent()->getMiddleLeft() == curr){
                            

                            RedistributeRight(curr);
                            //break;
                            
                        }
                        //delete left
                        else if(curr->getParent()->getLeft() == curr){
                            //cout << "COMING FOR YOU G: RedistributeLeft" << endl;
                            RedistributeLeft(curr);
                        }


                    }

                    //

                }
            }else{
                //three
                if(str.compare(curr->getSmallKey()->getKey()) == 0){//small
                    //return curr->getSmallKey()->getValue();
                    curr->setSmallKey(curr->getMiddleKey());
                    curr->setMiddleKey(nullptr);
                    //break;
                }else if(str.compare(curr->getMiddleKey()->getKey()) == 0){//large
                    //return curr->getMiddleKey()->getValue();
                    curr->setMiddleKey(nullptr);
                    //break;
                }

            }
    }

    //If leaf
    bool Index::Ifleaf(shared_ptr<Node> curr){
        return curr->getLeft() == nullptr && curr->getMiddleLeft() == nullptr && curr->getMiddleRight() == nullptr  && curr->getRight() == nullptr;
    }

        //Redistribute Left
    void Index::RedistributeLeft(shared_ptr<Node>& curr){
        // if it friend is threenode (A B): only refactoring the small part
        // if leaf 
        if(Ifleaf(curr)){
            
            //if the midleft is threenode
            if(IfThreeNode(curr->getParent()->getMiddleLeft())){
            
                curr->setSmallKey(curr->getParent()->getSmallKey());
                curr->getParent()->setSmallKey(curr->getParent()->getMiddleLeft()->getSmallKey());
                curr->getParent()->getMiddleLeft()->setSmallKey(curr->getParent()->getMiddleLeft()->getMiddleKey());
                curr->getParent()->getMiddleLeft()->setMiddleKey(nullptr);
            }

            // if not: look for parent parent help
            // join the bottom node with parent node
            // then delete parent node for internal node
            else{
                //join the left node
                //cout << "COMING TO YOU G: ENTERING MERGE" << endl;
                Merge(curr);

            }
        }

        //not leaf but internal node
        //not matter parent is two or threenode, just redistribute the small key
        else if(curr->getSmallKey() == nullptr && curr->getLeft() != nullptr){
            //if right is threenode
            // and if parent is twonode only
            //if(IfTwoNode(curr->getParent())){
                if(IfThreeNode(curr->getParent()->getMiddleLeft())){
                curr->setSmallKey(curr->getParent()->getSmallKey());
                curr->getParent()->setSmallKey(curr->getParent()->getMiddleLeft()->getSmallKey());
                curr->getParent()->getMiddleLeft()->setSmallKey(curr->getParent()->getMiddleLeft()->getMiddleKey());
                curr->getParent()->getMiddleLeft()->setMiddleKey(nullptr);

                //curr->setLeft(curr->getLeft());
                curr->setMiddleLeft(curr->getParent()->getMiddleLeft()->getLeft());
                curr->getParent()->getMiddleLeft()->setLeft(curr->getParent()->getMiddleLeft()->getMiddleLeft());
                curr->getParent()->getMiddleLeft()->setMiddleLeft(curr->getParent()->getMiddleLeft()->getRight());
                curr->getParent()->getMiddleLeft()->setRight(nullptr);
                }

                else{
                    
                    Merge(curr);
                }
            //}

            
        }

    }


    //Redistribute Right
    void Index::RedistributeRight(shared_ptr<Node>& curr){
        // if it friend is threenode (A B): only refactoring the small part
        // if leaf 
        if(Ifleaf(curr)){
            //if left is threenode
            if(IfThreeNode(curr->getParent()->getLeft())){
            
                curr->setSmallKey(curr->getParent()->getSmallKey());
                curr->getParent()->setSmallKey(curr->getParent()->getLeft()->getMiddleKey());
                curr->getParent()->getLeft()->setMiddleKey(nullptr);
            }

            // if not: look for parent parent help
            // join the bottom node with parent node
            // then delete parent node for internal node
            else{
                //join the left node
                Merge(curr);

            }
        }

        //not leaf but internal node
        //not matter parent is two or threenode, just redistribute the small key
        else if(curr->getSmallKey() == nullptr && curr->getLeft() != nullptr){
            //parent is two node only
            //if left is threenode
            if(IfThreeNode(curr->getParent()->getLeft()) && IfTwoNode(curr->getParent())){
                curr->setSmallKey(curr->getParent()->getSmallKey());
                curr->getParent()->setSmallKey(curr->getParent()->getLeft()->getMiddleKey());
                curr->getParent()->getLeft()->setMiddleKey(nullptr);
                curr->setMiddleLeft(curr->getLeft());
                curr->setLeft(curr->getParent()->getLeft()->getRight());
                
            }

            else{
                Merge(curr);
            }
        }


    }

    // Merge to Left node
    void Index::Merge(shared_ptr<Node>& curr){

        if(curr->getParent()->getMiddleLeft() == curr && curr->getParent() != nullptr){
            
            curr->getParent()->getLeft()->setMiddleKey(curr->getParent()->getSmallKey());
            curr->getParent()->setSmallKey(nullptr);
            //curr = curr->getParent();

            if(!Ifleaf(curr)){
                
                curr->getParent()->getLeft()->setRight(curr->getLeft());
            }
              
        }

        else if(curr->getParent()->getLeft() == curr && curr->getParent() != nullptr){
            //cout << "OK RIGHT HERE" << endl;
            curr->setSmallKey(curr->getParent()->getSmallKey());
            curr->setMiddleKey(curr->getParent()->getMiddleLeft()->getSmallKey());
            curr->getParent()->setSmallKey(nullptr);
            //curr = curr->getParent();

            if(!Ifleaf(curr)){
                //cout << "shouldnt output" << endl;
                curr->setMiddleLeft(curr->getParent()->getMiddleLeft()->getLeft());
                curr->setRight(curr->getParent()->getMiddleLeft()->getMiddleLeft());
            }
        }

        //cout << "asdljla" << endl;
        curr = curr->getParent();
        

        curr->setMiddleLeft(nullptr); 
        
        //curr->setSmallKey(nullptr);     
        //cout << "asdakdjl" << endl;
        //cout << curr->getSmallKey()->getKey() << " " << curr->getLeft()->getSmallKey()->getKey() << " " << curr->getLeft()->getMiddleKey()->getKey() << endl;
        if(curr->getParent() == nullptr && curr->getSmallKey() == nullptr && curr->getLeft() != nullptr){
            
            curr = curr->getLeft();
            curr->setParent(nullptr);
            root = curr;
            root->setParent(nullptr);
            //cout << "ashdhdeoahod" << endl;

            // root = curr->getParent()->getLeft();
            // root->setParent(nullptr);
        }
        //time to separate the direction:
        //if parent is two node
        else if(IfTwoNode(curr->getParent())){
            
            //if curr is stored on right
            if(curr->getParent()->getMiddleLeft() == curr && IfThreeNode(curr->getParent()->getLeft())){
                RedistributeRight(curr);
            }
            //if curr is stored on left
            else if(curr->getParent()->getLeft() == curr && IfThreeNode(curr->getParent()->getMiddleLeft()) ){
                
                RedistributeLeft(curr);
            }

            else
            {
                // cout << "BACKING TO MERGE FOR FRIENDS ARE NOT THREENODE" << endl;
                Merge(curr);
            }
        }
            
        //if parent is three node
        else if(IfThreeNode(curr->getParent())){
            //go ahead and use Restructure
            
            Restructure(curr);
            //done
        }

        //If parent is nullptr, which means reaching the root aleady
        //Base case

        else{
            // cout << "FUCKKKKKKKKKKKKKKKk" << endl;
            // if(curr->getParent() == nullptr){
            //     cout << "1" << endl;
            // }else{
            //     //cout << curr->getParent()->getSmallKey()->getKey() << endl;
            //     if(curr->getParent()->getSmallKey() == nullptr){
            //         cout << "asd" << endl;
            //     }

            //     if(curr->getParent()->getMiddleKey() == nullptr){
            //         cout << "asdhasd" << endl;
            //     }

            //     if(curr->getParent()->getLargeKey() == nullptr){
            //         cout << "64545" << endl;
            //     }
            // }
            // if(curr->getSmallKey() == nullptr){
            //     cout << "2" << endl;
            // }
            // if(curr->getLeft() != nullptr){
            //     cout << "3" << endl;
            // }


            if(curr->getSmallKey() == nullptr && curr->getLeft() != nullptr){
                 curr = curr->getLeft();
                curr->setParent(nullptr);
                root = curr;
                //root->setParent(nullptr);
                cout << "FUCKING DEAL" << endl;
            }
        }
        

        

    }



    



    //Replace with curr two node
    void Index::ReplaceTwoNode(shared_ptr<Node>& curr){
        //return curr->getSmallKey()->getValue();
        shared_ptr<Node> midleft = curr->getMiddleLeft();
        shared_ptr<Node> left = curr->getLeft();
        shared_ptr<Node>& min = FindMin(midleft);
        shared_ptr<Node>& max = FindMax(left);
        if(IfThreeNode(min)){
            curr->setSmallKey(min->getSmallKey());
            DeleteLeaf(min,min->getSmallKey()->getKey());
            //break;
        }
        //else if(IfThreeNode(max)){
        //     curr->setSmallKey(max->getMiddleKey());
        //     DeleteLeaf(max,max->getMiddleKey()->getKey());
        //     //break;
        else{
            //all min and max are two node
            curr->setSmallKey(max->getSmallKey());
            DeleteLeaf(max,max->getSmallKey()->getKey());
            //break;
        }
    }

    //Replace with curr three node small key
    void Index::ReplaceThreeNodeSmall(shared_ptr<Node>& curr){
        //return curr->getSmallKey()->getValue();
        shared_ptr<Node> midright = curr->getMiddleLeft();
        shared_ptr<Node> left = curr->getLeft();
        shared_ptr<Node>& min = FindMin(midright);
        shared_ptr<Node>& max = FindMax(left);
        // if(IfThreeNode(min)){
        //     curr->setSmallKey(min->getSmallKey());
        //     DeleteLeaf(min,min->getSmallKey()->getKey());
        //     //break;
        if(IfThreeNode(max)){
            curr->setSmallKey(max->getMiddleKey());
            DeleteLeaf(max,max->getMiddleKey()->getKey());
            //break;
        }else{
            //all min and max are two node
            curr->setSmallKey(min->getSmallKey());
            DeleteLeaf(min,min->getSmallKey()->getKey());
            //break;
        }
    }

    //Replace with curr three node
    void Index::ReplaceThreeNodeMid(shared_ptr<Node>& curr){
        //return curr->getSmallKey()->getValue();
        shared_ptr<Node> right = curr->getRight();
        shared_ptr<Node> midleft = curr->getMiddleLeft();
        shared_ptr<Node>& min = FindMin(right);
        shared_ptr<Node>& max = FindMax(midleft);
        // if(IfThreeNode(min)){
        //     curr->setMiddleKey(min->getSmallKey());
        //     DeleteLeaf(min,min->getSmallKey()->getKey());
        //     //break;
        // }else 
        
        if(IfThreeNode(max)){
            curr->setMiddleKey(max->getMiddleKey());
            DeleteLeaf(max,max->getMiddleKey()->getKey());
            //break;
        }else{
            //all min and max are two node
            curr->setMiddleKey(min->getSmallKey());
            DeleteLeaf(min,min->getSmallKey()->getKey());
        }
            
            //break;
        // }
    }

    //Find Min 
    shared_ptr<Node>& Index::FindMin(shared_ptr<Node>& curr){
        if(curr == nullptr){
            throw "Min value not found";
        }
        
        while(curr->getLeft() != nullptr){
            // if(curr->getLeft() == nullptr){
            //     return curr;
            //     break;
            // }else{
                //return this->FindMin(curr->getLeft());
                curr = curr->getLeft();
            // }

        }
        return curr;
         
    }

    //Find Max 
    shared_ptr<Node>& Index::FindMax(shared_ptr<Node>& curr) {
        if(curr == nullptr){
            throw "Max value not found";
        }
        
        while(curr->getMiddleLeft() != nullptr){
            if(IfThreeNode(curr)){
                if(curr->getRight() == nullptr){
                    return curr;
                    break;
                }else{
                    //return this->FindMax(curr->getRight());
                    curr = curr->getRight();
                }
            }else if(IfTwoNode(curr)){
                if(curr->getMiddleLeft() == nullptr){
                    return curr;
                    break;
                }else{
                    //return FindMax(curr->getMiddleLeft());
                    curr = curr->getMiddleLeft();
                }
            }
        }
        
        // cout << "findMax: never approve this message " << endl;
        return curr;
        //return nullptr;
    }


    //Get root ptr
    shared_ptr<Node> Index::getRoot(){
        return root;
    }

    //Print travserse, visit the key
    void Index::Print(){
        PrintHelp(root);
 
        
    }

    //ascii
    // int asc(string str){
    //     return (int)str[0];
    // }

    //Print Help
    void Index::PrintHelp(shared_ptr<Node> curr){
        if(curr == nullptr){
            cout << "ITS EMPTY" << endl;
            return;
        }

        //if leaf
        else if(curr->getLeft() == nullptr && curr->getMiddleLeft() == nullptr && curr->getMiddleRight() == nullptr && curr->getRight() == nullptr){
            //If two node
            if(IfTwoNode(curr)){
                cout << "TwoNode key: " << curr->getSmallKey()->getKey() << " TwoNode Value: " << curr->getSmallKey()->getValue() << endl;
                //cout << "TwoNode key ascii: " << curr->getSmallKey()->getKey() << " TwoNode Value: " << curr->getSmallKey()->getValue() << endl;
                return;
            }else{
                //Is three node then
                cout << "ThreeNode Small key: " << curr->getSmallKey()->getKey() << " ThreeNode Small Value: " << curr->getSmallKey()->getValue() << endl;
                cout << "ThreeNode Middle key: " << curr->getMiddleKey()->getKey() << " ThreeNode Middle Value: " << curr->getMiddleKey()->getValue() << endl;
                
                return;
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
        return;
    }

    //If two node 
    // (A)
    bool Index::IfTwoNode(shared_ptr<Node> curr){ 
        //return curr->getLStr() == "" && curr->getLValue() == -99;
        return curr->getSmallKey() != nullptr && curr->getMiddleKey() == nullptr && curr->getLargeKey() == nullptr;
    }

    //If three node
    // (A B)
    bool Index::IfThreeNode(shared_ptr<Node> curr){
        //return curr->getLStr() != "" && curr->getLValue() != -99;
        return curr->getSmallKey() != nullptr && curr->getMiddleKey() != nullptr && curr->getLargeKey() == nullptr;
    }

    // if four node
    // (A B C)
    bool Index::IfFourNode(shared_ptr<Node> curr){
        //return curr->getLStr() != "" && curr->getLValue() != -99;
        return curr->getSmallKey() != nullptr && curr->getMiddleKey() != nullptr && curr->getLargeKey() != nullptr;
    }

    //inserting two node situation
    shared_ptr<Node> Index::AddTwoNode(shared_ptr<Node> curr,shared_ptr<Key> newkeyptr){
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
    shared_ptr<Node> Index::AddThreeNode(shared_ptr<Node> curr,shared_ptr<Key> newkeyptr){
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
    shared_ptr<Node> Index::SplitWithNoParent(shared_ptr<Node>& curr){
        shared_ptr<Node> left, top, right;  
        left = make_shared<Node>(curr->getSmallKey());
        //cout << curr->getSmallKey()->getKey() << endl;
        top = make_shared<Node>(curr->getMiddleKey());
        //cout << curr->getMiddleKey()->getKey() << endl;
        right = make_shared<Node>(curr->getLargeKey());
        //cout << curr->getLargeKey()->getKey() << endl;


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

    //split with parent (left) twonode
    shared_ptr<Node> Index::SplitWithParentLeftTwoNode(shared_ptr<Node> curr){
        shared_ptr<Node> left = make_shared<Node>(curr->getSmallKey());
        shared_ptr<Node> middleleft = make_shared<Node>(curr->getLargeKey());

        //left
        curr->getParent()->setLeft(left);
        left->setParent(curr->getParent());

        // in case parent has midleft childern -> move to right
        if(curr->getParent()->getMiddleLeft() != nullptr){
            curr->getParent()->setRight(curr->getParent()->getMiddleLeft());
        }

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

    //split with parent (left) threenode
    shared_ptr<Node> Index::SplitWithParentLeftThreeNode(shared_ptr<Node> curr){
        shared_ptr<Node> left = make_shared<Node>(curr->getSmallKey());
        shared_ptr<Node> middleleft = make_shared<Node>(curr->getLargeKey());

        //left
        curr->getParent()->setLeft(left);
        left->setParent(curr->getParent());

        // in case parent has midleft childern -> move to midright
        if(curr->getParent()->getMiddleLeft() != nullptr){
            curr->getParent()->setMiddleRight(curr->getParent()->getMiddleLeft());
        }

        // in case parent has right childern -> move to midright
        // nothing
        
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
     shared_ptr<Node> Index::SplitWithParentRightTwoNode(shared_ptr<Node> curr){
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
    shared_ptr<Node> Index::SplitWithParentRightThreeNode(shared_ptr<Node> curr){
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