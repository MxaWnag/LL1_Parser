//
// Created by Max Wang on 2022/5/11.
//
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <utility>
#include <iomanip>
#include <vector>
#include <sstream>
#ifndef LL1_TRY_TREEGENERATOR_H
#define LL1_TRY_TREEGENERATOR_H
using namespace std;

struct TNode{
    int layer;
    string name;
    deque<TNode*> child;
};

class TreeGenerator {
    map<pair<string,string>,string>Table;
    string prog;
    vector<string>T;//终结符号集合
    vector<string>NT;//非终结符号集合
    string S;//开始符号
    map<string,vector<string>>production;//产生式

public:
    void dps(TNode * S,stack<string> &Analysis,deque<string> &stream,int layer);
    void printSystem();
    void printTable();
    void setTable(const map<pair<string, string>, string> &table);

    void setT(const vector<string> &t);

    void setNt(const vector<string> &nt);

    void setS(const string &s);

    void setProg(const string &prog);
    void printTree();
};


#endif //LL1_TRY_TREEGENERATOR_H
