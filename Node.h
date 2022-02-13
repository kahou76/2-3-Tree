#pragma once
#include<iostream>
#include<memory>
#include "Key.h"

using namespace std;


class Node {
private:
    shared_ptr<Node> left;
    shared_ptr<Node> middleleft;
    shared_ptr<Node> middleright;
    shared_ptr<Node> right;
    shared_ptr<Node> parent;
    // string smallstr;
    // string largestr;
    // string extrastr;
    // int smallval;
    // int largeval;
    // int extraval;
    shared_ptr<Key> smallkey;
    shared_ptr<Key> middlekey;
    shared_ptr<Key> largekey;


public:
    //constructor with key and val
    Node(string key, int val){
        left = nullptr;
        middleleft = nullptr;
        middleright = nullptr;
        right = nullptr;
        parent = nullptr;
        // smallstr = key;
        // smallval = val;
        // largestr = "";
        // largeval = -99;
        // leftkey->setKey(key);
        // leftkey->setValue(val);
        Key k = Key(key,val);
        smallkey = make_shared<Key>(k);
        middlekey = nullptr;
        largekey = nullptr;
    }

    //constructor with shared_ptr<Key>
    Node(shared_ptr<Key> k){
        left = nullptr;
        middleleft = nullptr;
        middleright = nullptr;
        right = nullptr;
        parent = nullptr;
        smallkey = k;
        middlekey = nullptr;
        largekey = nullptr;
    }



    ~Node(){}


    void setLeft(shared_ptr<Node> l){
        if(l != nullptr){
            this->left = l;
        }
    }

    void setMiddleLeft(shared_ptr<Node> ml){
        if(ml != nullptr){
            this->middleleft = ml;
        }
    }

    void setMiddleRight(shared_ptr<Node> mr){
        if(mr != nullptr){
            this->middleright = mr;
        }
    }

    void setRight(shared_ptr<Node> r){
        if(r != nullptr){
            this->right = r;
        }
    }

    void setParent(shared_ptr<Node> p){
        if(p != nullptr){
            this->parent = p;
        }
    }

    shared_ptr<Node> getLeft(){
        return left;
    }

    shared_ptr<Node> getMiddleLeft(){
        return middleleft;
    }

    shared_ptr<Node> getMiddleRight(){
        return middleright;
    }

    shared_ptr<Node> getRight(){
        return right;
    }

    shared_ptr<Node> getParent(){
        return parent;
    }

    void setSmallKey(shared_ptr<Key> sk){
        smallkey = sk;
    }

    void setMiddleKey(shared_ptr<Key> mk){
        middlekey = mk;
    }

    void setLargeKey(shared_ptr<Key> lk){
        largekey = lk;
    }

    shared_ptr<Key> getSmallKey(){
        return smallkey;
    }

    shared_ptr<Key> getMiddleKey(){
        return middlekey;
    }

    shared_ptr<Key> getLargeKey(){
        return largekey;
    }


};