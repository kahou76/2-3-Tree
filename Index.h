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
    Index();

    //greater
    struct greater{
        bool operator()( shared_ptr<Key> l, shared_ptr<Key> r ){
            return l->getKey() > r->getKey();
        }
    };

    //Insert an element in the index, associate the integer value with the element
    void Insert(shared_ptr<string> strptr, int val);

    //Insert help
    void InsertHelp(shared_ptr<Node> curr, shared_ptr<string> strptr, int val);

    //Split Main Function
    void Split(shared_ptr<Node> curr);


    //Find an element in the index
    int Find(shared_ptr<string> strptr);

    //Find Help
    int FindHelp(shared_ptr<Node> curr, shared_ptr<string> strptr);

   


    //Remove an element from the index
    void Remove(shared_ptr<string> strptr);

    //Restructure Left Leaf
    void RestructureLeftNodeLeaf(shared_ptr<Node>& curr);

    //Restructure Middle Leaf
    void RestructureMiddleNodeLeaf(shared_ptr<Node>& curr);

    //Restructure Right Leaf
    void RestructureRightNodeLeaf(shared_ptr<Node>& curr);

    //Restructure 
    void Restructure(shared_ptr<Node>& curr);

    //Delete Leaf
    //curr taking the leaf node
    void DeleteLeaf(shared_ptr<Node>& curr,string str);

    //If leaf
    bool Ifleaf(shared_ptr<Node> curr);

        //Redistribute Left
    void RedistributeLeft(shared_ptr<Node>& curr);


    //Redistribute Right
    void RedistributeRight(shared_ptr<Node>& curr);

    // Merge to Left node
    void Merge(shared_ptr<Node>& curr);



    



    //Replace with curr two node
    void ReplaceTwoNode(shared_ptr<Node>& curr);

    //Replace with curr three node small key
    void ReplaceThreeNodeSmall(shared_ptr<Node>& curr);

    //Replace with curr three node
    void ReplaceThreeNodeMid(shared_ptr<Node>& curr);

    //Find Min 
    shared_ptr<Node>& FindMin(shared_ptr<Node>& curr);

    //Find Max 
    shared_ptr<Node>& FindMax(shared_ptr<Node>& curr);


    //Get root ptr
    shared_ptr<Node> getRoot();

    //Print travserse, visit the key
    void Print();

    //Print Help
    void PrintHelp(shared_ptr<Node> curr);

    //If two node 
    // (A)
    bool IfTwoNode(shared_ptr<Node> curr);

    //If three node
    // (A B)
    bool IfThreeNode(shared_ptr<Node> curr);

    // if four node
    // (A B C)
    bool IfFourNode(shared_ptr<Node> curr);

    //inserting two node situation
    shared_ptr<Node> AddTwoNode(shared_ptr<Node> curr,shared_ptr<Key> newkeyptr);

    //inserting three node situation
    shared_ptr<Node> AddThreeNode(shared_ptr<Node> curr,shared_ptr<Key> newkeyptr);

    //split with no parent (A B C)
    shared_ptr<Node> SplitWithNoParent(shared_ptr<Node>& curr);

    //split with parent (left) twonode
    shared_ptr<Node> SplitWithParentLeftTwoNode(shared_ptr<Node> curr);

    //split with parent (left) threenode
    shared_ptr<Node> SplitWithParentLeftThreeNode(shared_ptr<Node> curr);

    //split with parent (right) twonode
     shared_ptr<Node> SplitWithParentRightTwoNode(shared_ptr<Node> curr);


    //split with parent (right) threenode
    shared_ptr<Node> SplitWithParentRightThreeNode(shared_ptr<Node> curr);



};