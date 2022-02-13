#include<iostream>
#include<memory>
#include "Index.h"

using namespace std;

int main(){
    cout << " Hello world" << endl;

    Index in = Index();
    in.Insert(make_shared<string>("a"),10);
    in.Insert(make_shared<string>("b"),20);
    in.Insert(make_shared<string>("c"),10);
    in.Insert(make_shared<string>("d"),11);
    in.Insert(make_shared<string>("e"),11);
    in.Insert(make_shared<string>("f"),11);
    in.Insert(make_shared<string>("g"),11);
    //cout << in.Find(make_shared<string>("d")) << endl;
    //in.Print();
    cout << endl;

};