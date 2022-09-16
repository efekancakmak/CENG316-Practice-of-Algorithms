#include <iostream>
#include <vector>

using namespace std;

int target;

int h3(const vector<int> &chain){
    int h = 0;
    int back = chain[chain.size()-1];
    int v = chain.back();
    while (v < target){        
        int temp = v;
        v += back;
        back = temp;
        h++;
    }
    return h;
}

bool dfs(vector<int> &chain, int limit)
{
    if ((int)chain.size() + h3(chain) > limit)
        return false;
    else if (chain.back() == target)
        return true;
    else{
        for (int i = chain.size() - 1; i >= 1; i--){
            for (int j = i-1; j >= 0; j--){
                int v = chain[i] + chain[j];
                if (chain.back() < v && v <= target){
                    chain.push_back(v);
                    if (dfs(chain, limit))
                        return true;
                    chain.pop_back();
                }
            }
        }
        return false;
    }
}

int main(void){
    cin >> target;
    vector<int> res = {1,2};
    for(int limit = 1; !dfs(res, limit) && limit < 25; limit++)
        ;
    for(int i : res)
        cout << i << " ";
    return 0;
}