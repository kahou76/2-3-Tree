#pragma once
#include<iostream>
#include<memory>
//#include<compare>
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

    //Insert an element in the index, associate the integer value with the element
    void Insert(shared_ptr<string> strptr, int val);

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
        if(curr->getLeft() == nullptr && curr->getMiddle() == nullptr && curr->getRight() == nullptr){
            if(IfTwoNode(curr)){
                //two node
                if(curr->getSStr() == *strptr){
                    return curr->getSValue();
                }
            }else{
                //three
                if(curr->getSStr() == *strptr){//small
                    return curr->getSValue();
                }else if(curr->getLStr() == *strptr){//large
                    return curr->getLValue();
                }

            }
        }

        //If two node with children
        if(IfTwoNode(curr)){

            if(str.compare(curr->getSStr()) == 0){
                return curr->getSValue();
            }

            else if(str.compare(curr->getSStr()) < 0){
                return FindHelp(curr->getLeft(),strptr);
            }else{
                return FindHelp(curr->getRight(),strptr);
            }
            
        }else{//three with children
            if(str.compare(curr->getSStr()) == 0){
                return curr->getSValue();
            }

            else if(str.compare(curr->getSStr()) < 0){
                return FindHelp(curr->getLeft(),strptr);
            }

            else if(str.compare(curr->getLStr()) == 0){
                return curr->getLValue();
            }

            else if(str.compare(curr->getSStr()) > 0 && str.compare(curr->getLStr()) < 0){
                return FindHelp(curr->getMiddle(),strptr);
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
        if(curr->getLeft() == nullptr && curr->getMiddle() == nullptr && curr->getRight() == nullptr){
            //If two node
            if(IfTwoNode(curr)){
                cout << "TwoNode key: " << curr->getSStr() << " TwoNode Value: " << curr->getSValue() << endl;
            }else{
                //Is three node then
                cout << "TwoNode Small key: " << curr->getSStr() << " TwoNode Small Value: " << curr->getSValue() << endl;
                cout << "TwoNode Large key: " << curr->getLStr() << " TwoNode Large Value: " << curr->getLValue() << endl;

            }
        }

        //two node
        if(IfTwoNode(curr)){
            PrintHelp(curr->getLeft());
            cout << "TwoNode key: " << curr->getSStr() << " TwoNode Value: " << curr->getSValue() << endl;
            PrintHelp(curr->getMiddle());
        }else{
            //three node
            PrintHelp(curr->getLeft());
            cout << "TwoNode Small key: " << curr->getSStr() << " TwoNode Small Value: " << curr->getSValue() << endl;
            PrintHelp(curr->getMiddle());
            cout << "TwoNode Large key: " << curr->getSStr() << " TwoNode Large Value: " << curr->getSValue() << endl;
            PrintHelp(curr->getRight());


        }
    }

    //If two node
    bool IfTwoNode(shared_ptr<Node> curr){
        return curr->getLStr() == "" && curr->getLValue() == -99;
    }

    //If three node
    bool IfThreeNode(shared_ptr<Node> curr){
        return curr->getLStr() != "" && curr->getLValue() != -99;
    }

    //when !IfTwoNode and !IfThreeNode, then there are one node trying to merge into a three node
    void split(shared_ptr<Node> curr){
        //compare three string and arrange them
        //pq push all string into it
        shared_ptr<Node> left, top, right;
        //top->getLeft() == left;
        //top->getMiddle() == right;
    }



};