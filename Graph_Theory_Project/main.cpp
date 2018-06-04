#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include "./map.h"
#include "./graph.h"

#define NMAX 30005

void solveTask1(vector < int > inDegree, myMap < int, string, intHash > M,
                ofstream &fout){
    int maxValue = 0;

    for (auto it : inDegree)
        maxValue = max(maxValue, it);

    for (unsigned int i = 0; i < inDegree.size(); i++){
        if (inDegree[i] == maxValue){
            fout << M.get(i) << " " << maxValue << "\n";
            break;
        }
    }
}

void dfs(int x, bool viz[NMAX], const Graph < int > &G, vector < int >*Stack){
    viz[x] = 1;

    for (auto it : G.LDA[x]){
        if (!viz[it.info]) dfs(it.info, viz, G, Stack);
    }

    Stack->push_back(x);
}

void dfs2(int x, int rs[NMAX], int cnt, const Graph < int > &G){
    rs[x] = cnt;

    for (auto it : G.ILDA[x]){
        if (rs[it.info] == -1) dfs2(it.info, rs, cnt, G);
    }
}

void solveTask2(const Graph < int > &G, vector < int > *C, ofstream &fout){
    int rs[G.nrNodes], cnt = 0;
    bool viz[G.nrNodes];
    vector < int > Stack;

    for (int i = 0; i < G.nrNodes; i++) rs[i] = -1, viz[i] = 0;

    for (int i = 0; i < G.nrNodes; i++){
        if (!viz[i]) dfs(i, viz, G, &Stack);
    }

    while (Stack.size()){
        int curr = Stack[Stack.size() - 1];

        if (rs[curr] == -1){
            cnt++;
            dfs2(curr, rs, cnt, G);
        }

        Stack.pop_back();
    }

    for (int i = 0; i < G.nrNodes; i++) C->push_back(rs[i]);

    fout << (cnt == 1 ? "VALID" : "INVALID") << "\n";
}

void solveTask3(int N, vector < string > V, myMap <string, int, stringHash> MAP,
            myMap <int, string, intHash> MI, vector < int > C, ofstream &fout){
    bool valid = 1;
    vector < string > Vec;

    for (auto it : V){
        int node = MAP.get(it);
        for (int i = 0; i < N; i++){
            if (C[i] != C[node]) Vec.push_back(MI.get(i));
        }

        if (Vec.empty()) continue;

        valid = 0;
        sort(Vec.begin(), Vec.end());
        fout << "Inaccessible cities for " << it << ": ";
        for (auto it2 : Vec) fout << it2 << " ";
        fout << "\n";
        Vec.clear();
    }

    if (valid == 1) fout << "There is a road between each two cities\n";
}

int bfs(Graph < int > G, int node, vector < bool > F){
    vector < int > Q(G.nrNodes);
    int st = 0, en = -1;
    int dist[G.nrNodes];
    bool viz[G.nrNodes];

    for (int i = 0; i < G.nrNodes; i++) viz[i] = 0, dist[i] = 2e9;

    Q[++en] = node;
    viz[node] = 1;
    dist[node] = 0;

    while (st <= en){
        int elem = Q[st++];

        for (auto it : G.LDA[elem]){
            if (!viz[it.info]){
                Q[++en] = it.info;
                viz[it.info] = 1;
                dist[it.info] = dist[elem] + 1;

                if (F[it.info]) return dist[it.info];
            }
        }
    }

    return 1000000;
}

void solveTask4(Graph < int > G, myMap < string, int, stringHash > M,
                vector < string > city, vector < int > l, vector < int > pU,
                vector < bool > F, ofstream &fout){
    int cnt = 0;

    for (auto it : city){
        int node = M.get(it), result = bfs(G, node, F);

        if (result * pU[cnt] > l[cnt])
            fout << "NO\n";
        else
            fout << "YES " << l[cnt] - result * pU[cnt] << "\n";

        cnt++;
    }
}

void computeAndPrint(Graph< int > G, myMap < int, string, intHash > M,
                    int sstart, int eend, ofstream &fout){
    vector < int > Q(G.nrNodes);
    int st = 0, en = -1;
    int dist[G.nrNodes], nextNode[G.nrNodes];
    bool viz[G.nrNodes];

    for (int i = 0; i < G.nrNodes; i++) viz[i] = 0, dist[i] = 2e9;

    Q[++en] = sstart;
    dist[sstart] = 0;
    viz[sstart] = 1;

    while (st <= en){
        int elem = Q[st++];

        for (auto it : G.LDA[elem]){
            if (!viz[it.info]){
                Q[++en] = it.info;
                viz[it.info] = 1;
                dist[it.info] = dist[elem] + 1;
            }
        }
    }

    st = 0, en = -1;
    for (int i = 0; i < G.nrNodes; i++) viz[i] = 0, nextNode[i] = -1;

    Q[++en] = eend;

    while (st <= en){
        int elem = Q[st++];

        for (auto it : G.ILDA[elem]){
            if (dist[it.info] != dist[elem] - 1) continue;
            Q[++en] = it.info;

            if (nextNode[it.info] == -1){
                nextNode[it.info] = elem;
            } else{
                string fst = M.get(elem);
                string scd = M.get(nextNode[it.info]);
                if (fst < scd) nextNode[it.info] = elem;
            }
        }
    }

    while (sstart != eend){
        fout << M.get(sstart) << " ";
        sstart = nextNode[sstart];
    }

    fout << M.get(eend) << " ";
}

void solveTask5(Graph < int > G, vector < GraphEdge < int > > Edges,
    myMap < int, string, intHash > M, ofstream &fout){
    myMap < myPair, int, myPair > MAP;
    int maxValue = 0, sstart = -1, eend = -1;

    for (auto it : Edges){
        myPair elem = {it.from, it.to};
        int diff = 0;

        if (MAP.isMapped(elem) == true){
            diff = MAP.get(elem);
            MAP.remove(elem);
        }

        MAP.put(elem, it.val + diff);
        if (it.val + diff > maxValue){
            maxValue = it.val + diff;
            sstart = it.from;
            eend = it.to;
        }
    }

    fout << maxValue << " ";
    computeAndPrint(G, M, sstart, eend, fout);
}

int main(){
    ofstream foutTask1("task1.out");
    ofstream foutTask2("task2.out");
    ofstream foutTask3("task3.out");
    ofstream foutTask4("task4.out");
    ofstream foutTask5("task5.out");

    int N, M, B, K, L, P, people, from, to, val1, val2;
    string city, city1, city2;

    vector < bool > isGasStation;
    vector < int > inDegree, component, perUnit, litre;
    vector < string > cityName;
    vector < GraphNode<int> > Nodes;
    vector < GraphEdge<int> > Edges, Container;

    myMap < string, int, stringHash > StoI;
    myMap < int, string, intHash > ItoS;

    cin >> N >> M;
    isGasStation.resize(N);
    inDegree.resize(N);

    for (int i = 0; i < N; i++){
        cin >> city;
        StoI.put(city, i);
        ItoS.put(i, city);
        Nodes.push_back({i, 0});
    }

    for (int i = 0; i < M; i++){
        cin >> city1 >> city2;
        from = StoI.get(city1);
        to = StoI.get(city2);

        Edges.push_back({from, to, 0});
        inDegree[to]++;
    }

    Graph < int > G(N, M, Edges, Nodes);

    solveTask1(inDegree, ItoS, foutTask1);
    solveTask2(G, &component, foutTask2);

    cin >> B;
    for (int i = 0; i < B; i++){
        cin >> city;
        int index = StoI.get(city);
        isGasStation[index] = true;
    }

    cin >> K;
    for (int i = 0; i < K; i++){
        cin >> city;
        cityName.push_back(city);
    }

    solveTask3(N, cityName, StoI, ItoS, component, foutTask3);

    cityName.clear();
    cin >> L;
    for (int i = 0; i < L; i++){
        cin >> city >> val1 >> val2;
        cityName.push_back(city);
        litre.push_back(val1);
        perUnit.push_back(val2);
    }

    solveTask4(G, StoI, cityName, litre, perUnit, isGasStation, foutTask4);

    cin >> P;
    for (int i = 0; i < P; i++){
        cin >> city1 >> city2 >> people;
        from = StoI.get(city1);
        to = StoI.get(city2);

        Container.push_back({from, to, people});
    }

    solveTask5(G, Container, ItoS, foutTask5);

    foutTask1.close();
    foutTask2.close();
    foutTask3.close();
    foutTask4.close();
    foutTask5.close();
    return 0;
}
