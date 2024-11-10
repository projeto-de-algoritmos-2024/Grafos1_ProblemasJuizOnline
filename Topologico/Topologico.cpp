#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Solution {
    void DFS(int x, int atual, vector<vector<int>> &resp, vector<vector<int>> &filho){

        for(int u : filho[atual]){
            if(resp[u].empty() || resp[u].back() != x){
                resp[u].push_back(x);
                DFS(x, u, resp, filho);
            }
        }
    }

public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> resp(n), filho(n);
        for(auto& e : edges){
            filho[e[0]].push_back(e[1]);
        }
        for(int i=0; i<n; i++) DFS(i, i, resp, filho);
        return resp;
    }
};