//
// Created by Max Wang on 2022/5/11.
//

#include "TreeGenerator.h"

void TreeGenerator::setTable(const map<pair<string, string>, string> &table) {
    Table = table;
}

void TreeGenerator::setProg(const string &prog) {
    TreeGenerator::prog = prog;
}
void TreeGenerator::printSystem() {
    for(string x :T){
        cout<<x<<endl;
    }
    cout<<endl;
    for(string x :NT){
        cout<<x<<endl;
    }

}
void TreeGenerator::printTable() {
    cout<<"LL(1)分析表："<<endl;

    vector<string>x=T;//含界符的终结符号集合
    x.push_back("#");

    //输出表格横轴
    cout.setf(ios::left);
    for (auto it1 = x.begin(); it1 != x.end(); it1++)
    {
        if (it1==x.begin())
            cout<<setw(15)<<" ";
        cout<<setw(20)<<*it1;
    }
    cout<<endl;

    for(string A:NT)
    {
        cout<<setw(15)<<A;

        for(string a:x)
        {
            pair<string,string>symbol;
            symbol=make_pair(A,a);
            if(!Table[symbol].empty())
                cout<<setw(20)<<Table[symbol]<<"|";
            else
                cout<<setw(20)<<"----------";
        }
        cout<<endl;
        cout<<endl;
        cout<<endl;
    }
    cout<<endl<<"LL(1)分析表构建完成"<<endl<<endl;
}
void TreeGenerator::dps(TNode * S,stack<string> &Analysis,deque<string> &stream,int layer){
if(Analysis.top()=="#"||stream.front()=="#")
    return;
    for(int i=0;i<layer;i++){
        cout<<"\t";
    }cout<<S->name<<endl;
    if(find(NT.begin(),NT.end(),S->name)!=NT.end()){//N为非终结符

        string first_Analysis = Analysis.top();
        string first_token = stream.front();
        pair<string,string> pair;
        pair.first=first_Analysis;
        pair.second=first_token;
        string pro = Table[pair];
        //cout<<Table[pair]<<endl;
        Analysis.pop();//将first_Analysis出栈，并换入生成式右边的
        int time =1;
        while(pro.find(" ")!=string::npos){
            time++;
            string lastToken = pro.substr(pro.rfind(" ")+1);
            //cout<<lastToken<<endl;
            Analysis.push(lastToken);
            pro=pro.substr(0,pro.rfind(" "));
        }if(pro.substr(pro.find("->")+2)!="@") {
            Analysis.push(pro.substr(pro.find("->") + 2));
        } if(pro.substr(pro.find("->")+2)=="@"){
          //  cout<<S->name<<"是@的父亲"<<endl;
            for(int i=0;i<layer+1;i++){
                cout<<"\t";
            }cout<<"E"<<endl;
            return;
        }
        stack<string> s = Analysis;

        for(int i=0;i<time;i++){//该产生式右部有time个右部，即为time个子节点
            TNode * child = new TNode;
            child->name = Analysis.top();
           // cout<<S->name<<"是"<<child->name<<"的父亲"<<endl;
           // cout<<"现在还在栈中："<<child->name<<endl;
            dps(child,Analysis,stream,layer+1);
            delete child;

        }


    }else{//N为终结符
        Analysis.pop();
        stream.pop_front();
        return ;
    }







}
void TreeGenerator::printTree() {
    string startSymbol = S;
    stack<string>Analysis;//分析串
    deque<string>stream;
    string result;
    Analysis.push("#");
    Analysis.push("compoundstmt");//读入串
    prog ="{\n"
          "while ( ID == NUM ) \n"
          "{ \n"
          "ID = NUM ; \n"
          "}\n"
          "}";
    stringstream  input(prog);
    while(input>>result){
        stream.push_back(result);
        //cout<<result<<endl;
    }
    stream.push_back("#");
    string first_Analysis;
    string first_Tokens;
    int layer = 0;
    TNode * S = new TNode;
    S->name ="compoundstmt";
    cout<<startSymbol<<" "<<layer<<endl;
    dps(S,Analysis,stream,layer+1);
}

void TreeGenerator::setT(const vector<string> &t) {
    T = t;
}

void TreeGenerator::setNt(const vector<string> &nt) {
    NT = nt;
}

void TreeGenerator::setS(const string &s) {
    S = s;
}
