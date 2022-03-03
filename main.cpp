#include<iostream>
#include<memory>
#include "Index.h"

using namespace std;

int main(){
    cout << " Hello world" << endl;

    Index in = Index();
    // in.Insert(make_shared<string>("j"),10); 
    // in.Insert(make_shared<string>("t"),20);
    // in.Insert(make_shared<string>("a"),1);
    // in.Insert(make_shared<string>("h"),8);
    // in.Insert(make_shared<string>("e"),5);
    // in.Insert(make_shared<string>("i"),9);
    // in.Insert(make_shared<string>("f"),6);

    // in.Insert(make_shared<string>("c"),3);
    // in.Insert(make_shared<string>("g"),7);
    // in.Insert(make_shared<string>("k"),11);
    // in.Insert(make_shared<string>("o"),15);
    
    // in.Insert(make_shared<string>("n"),14);
    // in.Insert(make_shared<string>("l"),12);
    // in.Insert(make_shared<string>("m"),13);
    // in.Insert(make_shared<string>("p"),16);
    // in.Insert(make_shared<string>("q"),17);
    // in.Insert(make_shared<string>("r"),18);
    // in.Insert(make_shared<string>("s"),19);
    // in.Insert(make_shared<string>("t"),20);

    in.Insert(make_shared<string>("a"),1);
    in.Insert(make_shared<string>("b"),2);
    in.Insert(make_shared<string>("c"),3);
    in.Insert(make_shared<string>("d"),4);
    in.Insert(make_shared<string>("e"),5);
    in.Insert(make_shared<string>("f"),6);
    in.Insert(make_shared<string>("g"),7);
    in.Insert(make_shared<string>("h"),8);
    in.Insert(make_shared<string>("i"),9);
    // in.Insert(make_shared<string>("j"),10);
    // in.Insert(make_shared<string>("k"),11);
    // in.Insert(make_shared<string>("l"),12);
    // in.Insert(make_shared<string>("m"),13);
    // in.Insert(make_shared<string>("n"),14);
    // in.Insert(make_shared<string>("o"),15);
    // in.Insert(make_shared<string>("p"),16);
    // in.Insert(make_shared<string>("q"),17);
    // in.Insert(make_shared<string>("r"),18);
    // in.Insert(make_shared<string>("s"),19);
    // in.Insert(make_shared<string>("t"),20);
    // in.Insert(make_shared<string>("u"),21);
    // in.Insert(make_shared<string>("v"),22);
    // in.Insert(make_shared<string>("w"),23);
    // in.Insert(make_shared<string>("x"),24);
    // in.Insert(make_shared<string>("y"),25);
    // in.Insert(make_shared<string>("z"),26);

    // cout << in.Find(make_shared<string>("q")) << endl;
    in.Print();
    cout << endl;

    //test01 for 1- 18
    // in.Remove(make_shared<string>("o"));
    // in.Remove(make_shared<string>("p"));
    // in.Remove(make_shared<string>("c"));


    //test02 for 10, 20 ,1
    // in.Remove(make_shared<string>("h"));
    // in.Remove(make_shared<string>("i"));
    // in.Remove(make_shared<string>("j"));
    // in.Remove(make_shared<string>("t"));
    // in.Remove(make_shared<string>("d"));



    in.Remove(make_shared<string>("a"));
    in.Remove(make_shared<string>("b"));
    in.Remove(make_shared<string>("c"));
    in.Remove(make_shared<string>("d"));
    in.Remove(make_shared<string>("e"));
    in.Remove(make_shared<string>("f"));
    in.Remove(make_shared<string>("g"));
    in.Remove(make_shared<string>("h"));
    in.Remove(make_shared<string>("i"));
    // in.Remove(make_shared<string>("j"));
    // in.Remove(make_shared<string>("k"));
    // in.Remove(make_shared<string>("l"));
    // in.Remove(make_shared<string>("m"));
    // in.Remove(make_shared<string>("n"));
    // in.Remove(make_shared<string>("o"));
    // in.Remove(make_shared<string>("p"));
    // in.Remove(make_shared<string>("q"));
    // in.Remove(make_shared<string>("r"));
    // in.Remove(make_shared<string>("s"));
    // in.Remove(make_shared<string>("t"));
    // in.Remove(make_shared<string>("u"));
    // in.Remove(make_shared<string>("v"));
    // in.Remove(make_shared<string>("w"));
    // in.Remove(make_shared<string>("x"));
    // in.Remove(make_shared<string>("y"));
    // in.Remove(make_shared<string>("z"));
    
    in.Print();
    //shared_ptr<Node> root = in.getRoot();
    // in.PrintHelp(root->getLeft()->getLeft());
    // shared_ptr<Node> min = in.FindMin(root);
    // cout << min->getSmallKey()->getKey() << endl;
    cout << endl;

};