#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class PartialSums{
    private:
        vector<int> s;
        static size_t lsb(size_t i){
            return i&(i^(i-1));
        }
    public:
        PartialSums(size_t n) : s(n + 1, 0){
        }

        size_t size() const{
            return s.size() - 1;
        }
        
        void update(size_t k){   
            for (size_t i = k; i <= size(); i = i + lsb(i))
                s[i]++;
        }
        
        int query(size_t k) const{
            int sum = 0;
            for (size_t i = k; i > 0; i = i - lsb(i))
                sum += s[i];
            return sum;
        }
};

int main(){
    int N;
    cin >> N;
    long *scores = new long[N];
    set<long> sorted_set;
    for (int i=0; i<N; i++){
        cin >> scores[i];
        sorted_set.insert(scores[i]);
    }
    unordered_map<long, int> score_to_index;
    set<long>::iterator itr = sorted_set.begin();
    int j = 1;
    for (; itr != sorted_set.end(); itr++)
        score_to_index[*itr] = j++;

    PartialSums S(sorted_set.size());
    int* results = new int[N];
    results[0] = 1;
    S.update( score_to_index[scores[0]] );
    for (int i=1; i<N; i++){
        results[i] = i + 1 - S.query( score_to_index[scores[i]]-1 );
        S.update( score_to_index[scores[i]] );
    }
    delete [] scores;
    for (int i=0; i<N-1; i++)
        cout << results[i] << " ";
    cout << results[N-1];
    delete [] results;
    return 0;
}