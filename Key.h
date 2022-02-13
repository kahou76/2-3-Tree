#pragma once
#include<iostream>
#include<memory>

using namespace std;

class Key{
private:
    string key;
    int value;

public:
    Key(string k, int v){
        key = k;
        value = v;
    }

    void setKey(string k){
        key = k;
    }

    void setValue(int v){
        value = v;
    }

    string getKey(){
        return key;
    }

    int getValue(){
        return value;
    }

};