//
//  main.cpp
//  1004
//
//  Created by qiang on 2020/1/27.
//  Copyright © 2020 qiang. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>

const int maxn = 1e3+10;
const int sup = 62;
const int INF = 0x7fffff;
const int num = 107;
using namespace std;

struct Node {
    int len, valid;
    int cnt[sup];
    bool operator < (const Node & node) const {
        return valid > node.valid;
    }
} node[num];

int n, result, cnt, limit = 200;
int target[sup], current[sup], total[sup], accmulate[num][sup];
int c2i(char ch) {
    if(ch >= '0' && ch <= '9') return ch - '0';
    if(ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
    if(ch >= 'a' && ch <= 'z') return ch - 'a' + 36;
    return INF;
}

bool check(int arr1[], int arr2[]) {
    for(int j = 0; j < sup; j++) {
        if(arr1[j] < arr2[j]) {
            return false;
        }
    }
    return true;
}
void dfs(int id, int sum) {
    cnt++;
    if(cnt > limit) return ;
    if(sum >= result) return ;
    if(check(current, target)) {
        result = sum;
        return ;
    }
    if(id == n) return ;
    
    for(int j = 0; j < sup; j++) {
        if(current[j] + accmulate[id][j] < target[j]) {
            return ;
        }
    }
    bool flag = false;
    for(int j = 0; j < sup; j++) {
        if(current[j] < target[j] && node[id].cnt[j]) {
            flag = true;
            break;
        }
    }
    if(flag) {
        // 用当前id
        for(int j = 0; j < sup; j++) {
            current[j]  += node[id].cnt[j];
        }
        dfs(id+1, sum + node[id].len);
        for(int j = 0; j < sup; j++) {
            current[j]  -= node[id].cnt[j];
        }
    }
    dfs(id+1, sum);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    freopen("input.txt", "r", stdin);
    char str[maxn], temp[maxn];
    scanf("%s%d", str, &n);
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        target[c2i(str[i])]++;
    }
    for(int i = 0; i < n; i++) {
        scanf("%s", temp);
        node[i].len = strlen(temp);
        for(int j = 0; j < node[i].len; j++) {
            node[i].cnt[c2i(temp[j])]++;
            total[c2i(temp[j])]++;
        }
        for(int j = 0; j < sup; j++) {
            node[i].valid += min(node[i].cnt[j], target[j]);
        }
    }
    result = 0;
    for(int j = 0; j < sup; j++) {
        if(total[j] < target[j]) {
            result += target[j] - total[j];
        }
    }
    if(result) {
        printf("No %d\n", result);
    } else {
        sort(node, node+n);
        for(int i = n-1; i >= 0; i--) {
            for(int j = 0; j < sup; j++) {
                accmulate[i][j] = accmulate[i+1][j] + node[i].cnt[j];
            }
        }
        result = INF;
        dfs(0, 0);
        printf("Yes %d\n", result - len);
    }
    return 0;
}
