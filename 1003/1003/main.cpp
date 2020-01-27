//
//  main.cpp
//  1003
//
//  Created by qiang on 2020/1/21.
//  Copyright © 2020 qiang. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <string.h>
using namespace std;
const int maxn = 1010;
const int INF = 0x7fffff;
struct edge {
    int to, cap, rev;
};
vector<edge> G[maxn];
bool used[maxn];

void add_edge(int from, int to, int cap) {
    G[from].push_back((edge){to, cap, (int)G[to].size()});
    G[to].push_back((edge){from, 0, (int)G[from].size()-1});
}

int dfs(int v, int t, int f) {
    if(v == t) return f;
    used[v] = true;
    for(int i = 0; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if(!used[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));
            if(d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    for(;;) {
        memset(used, 0, sizeof(used));
        int f = dfs(s, t, INF);
        if(f == 0) return flow;
        flow += f;
    }
}

int main(int argc, const char * argv[]) {
    freopen("input.txt", "r", stdin);
    map<string, int> mp;
    string str_s, str_t;
    int n;
    int idx = 1;
    cin >> str_s >> str_t >> n;
    if(!mp[str_s]) mp[str_s] = idx++;
    if(!mp[str_t]) mp[str_t] = idx++;
    int s = mp[str_s], t = mp[str_t];
    string str_from, str_to;
    int capcity, from, to;
    for(int i = 0; i < n; i++) {
        cin >> str_from >> str_to >> capcity;
        if(!mp[str_from]) {
            mp[str_from] = idx++;
        }
        if(!mp[str_to]) {
            mp[str_to] = idx++;
        }
        from = mp[str_from];
        to = mp[str_to];
        add_edge(from, to, capcity);
    }
    cout << max_flow(s, t) << endl;
    return 0;
}
