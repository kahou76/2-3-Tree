#pragma once
#include<iostream>
#include<memory>

using namespace std;


class Node {
private:
    shared_ptr<Node> left;
    shared_ptr<Node> middle;
    shared_ptr<Node> right;
    string smallstr;
    string largestr;
    string extrastr;
    int smallval;
    int largeval;
    int extraval;

public:
    Node(string key, int val){
        left = nullptr;
        middle = nullptr;
        right = nullptr;
        smallstr = key;
        smallval = val;
        largestr = "";
        largeval = -99;
    }

    ~Node(){}

    void setSStr(string s){
        smallstr = s;
    }

    void setLStr(string l){
        largestr = l;
    }

    string getSStr(){
        return smallstr;
    }

    string getLStr(){
        return largestr;
    }

    void setSValue(int sval){
        smallval = sval;
    }

    void setLValue(int lval){
        largeval = lval;
    }

    int getSValue(){
        return smallval;
    }

    int getLValue(){
        return largeval;
    }

    void setLeft(shared_ptr<Node> l){
        this->left = l;
    }

    void setMiddle(shared_ptr<Node> m){
        this->left = m;
    }

    void setRight(shared_ptr<Node> r){
        this->right = r;
    }

    shared_ptr<Node> getLeft(){
        return left;
    }

    shared_ptr<Node> getMiddle(){
        return middle;
    }

    shared_ptr<Node> getRight(){
        return right;
    }


};