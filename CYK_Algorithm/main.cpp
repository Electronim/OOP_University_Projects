#include <bits/stdc++.h>
#define NMAX 300

using namespace std;

int n, cnt = 1, nrWords;
bool dp[NMAX][NMAX][100];
string s, garbage, sequence, word[1005];

vector < pair < string, string > > Unit;
vector < pair < string, pair < string, string > > > Production;
map < string, int > M;
string start;

int main(){
    ifstream cin("test.in");

    cin >> n;
    getline(cin, garbage);

    while (n--){
        getline(cin, s);

        int count = 0;
        for (auto it : s) count += (it == ' ');

        if (count == 1){
            int i = 0;
            string a = "", b = "";

            for (i = 0; s[i] != ' '; ++i) a += s[i];
            for (++i; i < s.size(); ++i) b += s[i];

            Unit.push_back({a, b});
            if (!M[a]) M[a] = cnt++;
        }else{
            int i = 0;
            string a = "", b = "", c = "";

            for (i = 0; s[i] != ' '; ++i) a += s[i];
            for (++i; s[i] != ' '; ++i) b += s[i];
            for (++i; i < s.size(); ++i) c += s[i];

            Production.push_back({a, {b, c}});
            if (!M[a]) M[a] = cnt++;
            if (!M[b]) M[b] = cnt++;
            if (!M[c]) M[c] = cnt++;
        }
    }

    cin >> start;

    getline(cin, garbage);
    getline(cin, sequence);

    for (int i = 0; i < sequence.size(); i++){
        if (sequence[i] == ' '){
            nrWords++;
            continue;
        }

        word[nrWords] += sequence[i];
    }
    nrWords++;

    for (int i = 0; i < nrWords; i++)
        for (auto it : Unit)
            if (it.second == word[i]){
                dp[1][i][M[it.first]] = 1;
            }

    for (int l = 2; l <= nrWords; ++l)
        for (int s = 0; s + l - 1 < nrWords; ++s)
            for (int p = 1; p < l; ++p)
                for (auto it : Production){
                    dp[l][s][M[it.first]] |= (dp[p][s][M[it.second.first]] && dp[l - p][s + p][M[it.second.second]]);
                }

    if (dp[nrWords][0][M[start]] == 1) cout << "The sequence IS a member of the language!\n";
    else cout << "The sequence ISN'T a member of the language!\n"; 

    return 0;
}