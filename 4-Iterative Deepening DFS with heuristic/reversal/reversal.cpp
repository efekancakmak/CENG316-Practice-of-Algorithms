#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_set>
using namespace std;

int len;
vector<pair<int,int>> path;
unordered_set<long> nondup;

int heuristic(int*& nums){
    int res = 0;
    for(int k=0; k<len-1; k++)
        if(! ( (nums[k]+1 == nums[k+1]) || (nums[k+1]+1 == nums[k]) ) )
            res++;
    if (res%2)
        return res/2 + 1;
    return res/2;
}

bool check(int*& nums){
    for(int i=1; i<len-1; i++)
        if (nums[i] != i)
            return false;
    return true;
}

void rev(int*& nums, int i, int j){
    for(;i<j; i++, j--) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}

long sum(int*& nums){
    long res = 0;
    for(int i=1; i<len-1; i++)
        res += nums[i]*pow(10,i);
    return res;
}

bool dfs(int* nums, int level, int limit){
    if (check(nums))
        return true;
    if(nondup.find(sum(nums)) != nondup.end())
        return false;
    if(level + heuristic(nums) > limit)
        return false;
        
    vector<pair<int,pair<int,int>>> route; 
    for(int i=1; i < len-2; i++){
        for(int j=i+1; j < len-1; j++){
            rev(nums,i,j);
            route.push_back(make_pair(-heuristic(nums),make_pair(i,j)));
            rev(nums,i,j);
        }
    }
    sort(route.begin(), route.end());
    for(int r=route.size()-1; r>=0; r--){
        int i = route[r].second.first;
        int j = route[r].second.second;
        rev(nums,i,j);
        path.push_back(pair<int,int>(i,j));
        if (dfs(nums,level+1,limit))
            return true;
        path.pop_back();
        rev(nums,i,j);
    }
    nondup.insert(sum(nums));
    return false;
}

int main() {
    vector<int> numbers = {0};
    int last = -1;
    do{
        int temp;
        cin >> temp;
        if(last!=temp)
            numbers.push_back(temp);
        last = temp;
    }while(!cin.eof());
    numbers.push_back(numbers.size());
    len = numbers.size();

    int* nums =new int[len];
    for(int i=0; i<len; i++)
        nums[i] = numbers[i];
    
    bool dfsres = false;
    for(int i=0; !dfsres; i++){
        nondup.clear();
        dfsres = dfs(nums,0,i);
    }
    cout << path.size() << endl;
    for(pair<int,int> p : path)
        cout << p.first << " " << p.second << endl;
    return 0;
}