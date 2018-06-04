//
// Created by Petrasco Sandu on the 11th of April 2018
//
#include <bits/stdc++.h>

using namespace std;

ifstream fin("test.in");
ofstream fout("test.out");
const int NMAX = 205;

class ExprToDFA{
    struct my{
        char ch;
        int count, pos;
    };

    string NormalExpr;
    my Expr[NMAX], root;
    queue < my > Polish;
    vector < my > Tree[NMAX], firstpos[NMAX], lastpos[NMAX];
    bool nullable[NMAX], viz[NMAX];
    vector < int > Follow[NMAX];
    map < int , char > Map;
    
    map < vector < int >, int > DFA;
    map < pair < int , char >, int > Delta, GOD;
    vector < int > FinalStates;
    set < char > Alfa;
    set < int > States;
    int initState = 1;

public:
    ExprToDFA(string _NormalExpr = "") : NormalExpr("(" + _NormalExpr + ")#") { }
    
    ExprToDFA(const ExprToDFA& other){
        this->NormalExpr = other.NormalExpr;
    }

    void setValue(){
        int cnt = 0;

        for (int i = 0; i < NormalExpr.size(); i++){
            if (isOk(NormalExpr[i])){
                Expr[i] = {NormalExpr[i], ++cnt, i};
                Map[cnt] = NormalExpr[i];
                
                if (NormalExpr[i] != '#') Alfa.insert(NormalExpr[i]);
            }

            if (!isOk(NormalExpr[i])){
                Expr[i] = {NormalExpr[i], -1, i};
            }
        }
    }

    string getExpr(){
        return NormalExpr;
    }

    void getValues(){
        for (int i = 0; i < NormalExpr.size(); i++)
            fout << Expr[i].ch << " "  << Expr[i].count << " " << Expr[i].pos << "\n";
    }

    void getPolish(){
        while (Polish.size()){
            cout << Polish.front().ch;
            Polish.pop();
        }
        cout << "\n";
    }

    my getRoot(){
        fout << root.ch << " " << root.count << " " << root.pos << "\n";
    }

    void getPos(){
        fout << NormalExpr << "\n";

        for (int i = 0; i < NormalExpr.size(); i++){
            auto root = Expr[i];

            fout << root.ch << " -> FP { ";

            for (auto it : firstpos[root.pos]) fout << it.count << " ";
            fout << "} LP { ";
            for (auto it : lastpos[root.pos]) fout << it.count << " ";

            fout << "}\n";
        }
    }

    void getTree(my x){
        cout << x.pos << " ( " << x.ch << " , " << x.count << " )\n";
        
        if (Tree[x.pos].size()){
            cout << "St. " << x.pos << "( " << x.ch << " , " << x.count << " ) = ";
            getTree(Tree[x.pos][0]);
        }
        
        if (Tree[x.pos].size() > 1){
            cout << "Dr. " << x.pos << "( " << x.ch << " , " << x.count << " ) = ";
            getTree(Tree[x.pos][1]);
        }
    }

    void getFollow(){
        fout << "\n\n\n";
        for (int i = 0; i < NormalExpr.size(); i++){
            if (Expr[i].count == -1) continue;

            fout << Expr[i].count << " -> ";
            for (auto it : Follow[Expr[i].count]) fout << it << " ";

            fout << "\n";
        }
    }

    void getResult(){
        queue < int > Q;
        bitset < 1000005 > B;

        Q.push(initState);
        B[initState] = 1;

        while (Q.size()){
            int node = Q.front(); Q.pop();
            States.insert(node);
            
            for (auto it : Alfa){
                int nnode = Delta[{node, it}];
                if (!nnode) continue;
                if (!B[nnode]) B[nnode] = 1, Q.push(nnode);
            }
        }
    }

    void getDFAinfo(){
        fout << States.size() << "\n";
        for (auto it : States) fout << it << " ";
        fout << "\n";

        fout << Alfa.size() << "\n";
        for (auto it : Alfa) fout << it << " ";
        fout << "\n";

        fout << initState << "\n";

        fout << FinalStates.size() << "\n";
        for (auto it : FinalStates) fout << it << " ";
        fout << "\n";

        for (auto it : Delta){
            if (it.first.second == '#' || !it.second) continue;
            GOD[it.first] = it.second;
        }

        fout << GOD.size() << "\n";
        for (auto it : GOD){
            fout << it.first.first << " " << it.first.second << " " << it.second << "\n";
        }
    }

    bool isOk(char c){
        return !(c == '|' || c == '*' || c == '(' || c == ')'  || c == '.');
    }

    void addConcat(){
        string res = "";

        for (int i = 0; i < NormalExpr.size(); i++){
            res += NormalExpr[i];

            if (i < NormalExpr.size() - 1 && (NormalExpr[i + 1] != '*' && NormalExpr[i + 1] != ')' && NormalExpr[i + 1] != '|') && 
                (NormalExpr[i] != '|' && NormalExpr[i] != '('))
                res += '.';

        }

        NormalExpr = res;
    }

    void toPolish(){
        stack < my > Op;
        
        for (int i = 0; i < NormalExpr.size(); i++){
            if (NormalExpr[i] != '|' && NormalExpr[i] != '.' && NormalExpr[i] != '(' && NormalExpr[i] != ')')
                Polish.push(Expr[i]);

            if (NormalExpr[i] == '(') Op.push(Expr[i]);

            if (NormalExpr[i] == ')'){
                while (Op.top().ch != '('){
                    Polish.push(Op.top());
                    Op.pop();
                }

                Op.pop();
            }

            if (NormalExpr[i] == '|'){
                while (Op.size() && (Op.top().ch == '.' || Op.top().ch == '|')){
                    Polish.push(Op.top());
                    Op.pop();
                }

                Op.push(Expr[i]);
            }

            if (NormalExpr[i] == '.'){
                while (Op.size() && Op.top().ch == '.'){
                    Polish.push(Op.top());
                    Op.pop();
                }

                Op.push(Expr[i]);
            }

        }

        while(Op.size()){
            Polish.push(Op.top());
            Op.pop();
        }

    }

    void toSyntaxTree(){
        stack < my > Eval;

        while (Polish.size()){
            my elem = Polish.front(); Polish.pop();
            if (isOk(elem.ch)){
                Eval.push(elem);
            }

            if (elem.ch == '|'){
                Tree[elem.pos].resize(2);
                Tree[elem.pos][0] = Eval.top(); Eval.pop();
                Tree[elem.pos][1] = Eval.top(); Eval.pop();
                Eval.push(elem);
            }

            if (elem.ch == '*'){
                Tree[elem.pos].resize(1);
                Tree[elem.pos][0] = Eval.top(); Eval.pop();
                Eval.push(elem);
            }

            if (elem.ch == '.'){
                Tree[elem.pos].resize(2);
                Tree[elem.pos][0] = Eval.top(); Eval.pop();
                Tree[elem.pos][1] = Eval.top(); Eval.pop();
                Eval.push(elem);
            }
        }

        root = Eval.top(); Eval.pop();
    }

    void normalize(){
        for (int i = 0; i < NormalExpr.size(); i++){
            if (Tree[i].size() > 1) swap(Tree[i][0], Tree[i][1]);
        }
    }

    void computeHelpers(my root){
        viz[root.pos] = 1;
        
        if (Tree[root.pos].empty()){
            nullable[root.pos] = 0;
            firstpos[root.pos].push_back(root);
            lastpos[root.pos].push_back(root);
            return ;
        }

        for (auto it : Tree[root.pos]){
            if (!viz[it.pos]){
                computeHelpers(it);
            }
        }

        if (root.ch == '|'){
            nullable[root.pos] = nullable[Tree[root.pos][0].pos] | nullable[Tree[root.pos][1].pos];

            for (auto it : firstpos[Tree[root.pos][0].pos]) firstpos[root.pos].push_back(it);
            for (auto it : firstpos[Tree[root.pos][1].pos]) firstpos[root.pos].push_back(it);

            for (auto it : lastpos[Tree[root.pos][0].pos]) lastpos[root.pos].push_back(it);
            for (auto it : lastpos[Tree[root.pos][1].pos]) lastpos[root.pos].push_back(it);
        }

        if (root.ch == '.'){
            nullable[root.pos] = nullable[Tree[root.pos][0].pos] & nullable[Tree[root.pos][1].pos];

            for (auto it : firstpos[Tree[root.pos][0].pos]) firstpos[root.pos].push_back(it);
            if (nullable[Tree[root.pos][0].pos])
                for (auto it : firstpos[Tree[root.pos][1].pos]) firstpos[root.pos].push_back(it);

            for (auto it : lastpos[Tree[root.pos][1].pos]) lastpos[root.pos].push_back(it);
            if (nullable[Tree[root.pos][1].pos])
                for (auto it : lastpos[Tree[root.pos][0].pos]) lastpos[root.pos].push_back(it);
        }

        if (root.ch == '*'){
            nullable[root.pos] = 1;

            for (auto it : firstpos[Tree[root.pos][0].pos]) firstpos[root.pos].push_back(it);

            for (auto it : lastpos[Tree[root.pos][0].pos]) lastpos[root.pos].push_back(it);
        }

        sort(firstpos[root.pos].begin(), firstpos[root.pos].end(), [&](my a, my b){return a.pos < b.pos;});
        sort(lastpos[root.pos].begin(), lastpos[root.pos].end(), [&](my a, my b){return a.pos < b.pos;});
        
        vector < my > Help;
        for (auto it : firstpos[root.pos])
            if (Help.empty() || it.pos != Help[Help.size() - 1].pos) Help.push_back(it);
        swap(firstpos[root.pos], Help);

        Help.clear();
        for (auto it : lastpos[root.pos])
            if (Help.empty() || it.pos != Help[Help.size() - 1].pos) Help.push_back(it);
        swap(lastpos[root.pos], Help);
    }

    void computeFollowpos(){
        for (int i = 0; i < NormalExpr.size(); i++){
            if (Expr[i].ch == '.'){
                for (auto it : lastpos[Tree[i][0].pos])
                    for (auto it2 : firstpos[Tree[i][1].pos])
                        Follow[it.count].push_back(it2.count);
            }

            if (Expr[i].ch == '*'){
                for (auto it : lastpos[i]){
                    for (auto it2 : firstpos[i])   
                        Follow[it.count].push_back(it2.count);
                }
            }
        }
    }

    void normalize2(){
        for (int i = 0; i < NormalExpr.size(); i++){
            if (Follow[i].empty()) continue;

            sort(Follow[i].begin(), Follow[i].end());
            auto it = unique(Follow[i].begin(), Follow[i].end());
            Follow[i].resize(distance(Follow[i].begin(), it));
        }
    }

    void bigBang(){
        int cnt = 0;
        vector < int > Curr;
        queue < vector < int > > Q;

        for (auto it : firstpos[root.pos]){
            Curr.push_back(it.count);
        }

        Q.push(Curr);
        DFA[Curr] = ++cnt;

        while (Q.size()){
            Curr = Q.front(); Q.pop();

            bool is = 0;
                for (auto it2 : Curr){
                    if (it2 == Expr[NormalExpr.size() - 1].count) is = 1;
                }

            if (is) FinalStates.push_back(DFA[Curr]);
            
            unordered_map < char , vector < int > > Help;

            for (auto it : Curr){
                Help[Map[it]].push_back(it);
            }

            for (auto it : Help){
                vector < int > Union;

                for (auto it2 : it.second){
                    Union.insert(Union.end(), Follow[it2].begin(), Follow[it2].end());
                }

                if (Union.size() == 0) continue;

                sort(Union.begin(), Union.end());
                auto ii = unique(Union.begin(), Union.end());
                Union.resize(distance(Union.begin(), ii));
                
                if (!DFA[Union]){
                    Q.push(Union);
                    DFA[Union] = ++cnt;
                }

                Delta[make_pair(DFA[Curr], it.first)] = DFA[Union];
            }
        }

        sort(FinalStates.begin(), FinalStates.end());
        auto it = unique(FinalStates.begin(), FinalStates.end());
        FinalStates.resize(distance(FinalStates.begin(), it));
    }

    void Solve(){
        addConcat();
        setValue();
        toPolish();
        toSyntaxTree();
        //getTree(root);
        normalize();
        computeHelpers(root);
        computeFollowpos();
        normalize2();
        bigBang();
        getResult();
        getDFAinfo();
    }
};

int main(){
    string s;
    fin >> s;

    ExprToDFA A(s);
    A.Solve();

    return 0;
}
//
// Created by Petrasco Sandu on the 11th of April 2018
//
