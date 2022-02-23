#include<iostream>
#include<memory>
#include "Index.h"

using namespace std;

int main(){
    cout << " Hello world" << endl;

    Index in = Index();
    in.Insert(make_shared<string>("j"),10); 
    in.Insert(make_shared<string>("t"),20);
    in.Insert(make_shared<string>("a"),1);
    // in.Insert(make_shared<string>("h"),8);
    // in.Insert(make_shared<string>("e"),5);
    // in.Insert(make_shared<string>("i"),9);
    // in.Insert(make_shared<string>("f"),6);


    // in.Insert(make_shared<string>("o"),15);
    // in.Insert(make_shared<string>("i"),9);
    // in.Insert(make_shared<string>("f"),6);
    // in.Insert(make_shared<string>("n"),14);
    // in.Insert(make_shared<string>("g"),7);
    // in.Insert(make_shared<string>("d"),4);


    // in.Insert(make_shared<string>("a"),1);
    // in.Insert(make_shared<string>("b"),2);
    // in.Insert(make_shared<string>("c"),3);
    // in.Insert(make_shared<string>("d"),4);
    // in.Insert(make_shared<string>("e"),5);
    // in.Insert(make_shared<string>("f"),6);
    // in.Insert(make_shared<string>("g"),7);
    // in.Insert(make_shared<string>("h"),8);
    // in.Insert(make_shared<string>("i"),9);
    // in.Insert(make_shared<string>("j"),10);
    // in.Insert(make_shared<string>("k"),11);
    // in.Insert(make_shared<string>("l"),12);
    // in.Insert(make_shared<string>("m"),13);
    // in.Insert(make_shared<string>("n"),14);
    // in.Insert(make_shared<string>("o"),15);
    // in.Insert(make_shared<string>("p"),16);
    // in.Insert(make_shared<string>("q"),17);
    // in.Insert(make_shared<string>("r"),18);

    // cout << in.Find(make_shared<string>("q")) << endl;
    // in.Print();
    // cout << endl;

    // in.Remove(make_shared<string>("o"));
    // in.Remove(make_shared<string>("p"));
    // in.Remove(make_shared<string>("c"));
    in.Print();
    //shared_ptr<Node> root = in.getRoot();
    // in.PrintHelp(root->getLeft()->getLeft());
    // shared_ptr<Node> min = in.FindMin(root);
    // cout << min->getSmallKey()->getKey() << endl;
    cout << endl;

};