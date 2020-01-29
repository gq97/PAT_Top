//
//  main.cpp
//  1017
//
//  Created by qiang on 2020/1/29.
//  Copyright © 2020 qiang. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e4+10;
const int INF = 0x7fffff;
int upseq_left[maxn], upseq_right[maxn], arr[maxn];

void dynamic_programming(int N) {

    for(int i = 1; i <= N; i++) {
        for(int j = i + 1; j <= N; j++) {
            if(arr[j-1] > arr[i-1]) {
                upseq_left[j] = max(upseq_left[i]+1, upseq_left[j]);
            }
        }
    }
    
    for(int i = N - 1; i >= 0; i--) {
        for(int j = i - 1; j >= 0; j--) {
            if(arr[j] > arr[i]) {
                upseq_right[j] = max(upseq_right[i] + 1, upseq_right[j]);
            }
        }
    }
    
}
int main(int argc, const char * argv[]) {
    // insert code here...
    // freopen("input3.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    dynamic_programming(N);
    int peak_length = 0;
    int peak_index = 0;
    int diff = INF;
    for(int i = 0; i < N; i++) {
        if(upseq_left[i+1] && upseq_right[i] && upseq_left[i+1] + upseq_right[i] >= peak_length) {
            if(upseq_left[i+1] + upseq_right[i] > peak_length) {
                peak_length = upseq_left[i+1] + upseq_right[i];
                peak_index = i + 1;
                diff = abs(upseq_left[i+1] - upseq_right[i]);
            } else if(upseq_left[i+1] + upseq_right[i] == peak_length){
                if(abs(upseq_left[i+1] - upseq_right[i]) < diff) {
                    diff = abs(upseq_left[i+1] - upseq_right[i]);
                    peak_index = i + 1;
                }
            }
        }
    }
    if(peak_length) {
        printf("%d %d %d\n", peak_length+1, peak_index, arr[peak_index-1]);
    } else {
        printf("No peak shape\n");
    }
    return 0;
}
