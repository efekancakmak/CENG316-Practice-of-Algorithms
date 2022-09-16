#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath> // for max
#include <algorithm> // for sorting

using namespace std;

class PartialMaxs
{
    private:
        vector<int> s;
        static size_t lsb(size_t i){
            return i&(i^(i-1));
        }
    
    public:
        PartialMaxs(size_t n) : s(n + 1, 0){
        }

        size_t size() const{
            return s.size() - 1;
        }
        
		void update(size_t k, int delta){   
			int themax = delta;
            for (size_t i = k; i <= size(); i = i + lsb(i))
				s[i] = max(s[i],themax);    
        }

        int query(size_t k) const{        
            int themax = 0;
            for (size_t i = k; i > 0; i = i - lsb(i))
                themax = max(s[i],themax);
            return themax;
        }
};

struct Box{
	unsigned int w,h;
};

// FOR SORTING PURPOSES..
bool width(Box const &a, Box const &b){
	return a.w < b.w;
}
bool height(Box const &a, Box const &b){
	return a.h < b.h;
}

int main(){
	int N; 
	cin >> N;
	struct Box* boxes = new struct Box[N];
	for(int i=0; i<N; i++)
		cin >> boxes[i].w >> boxes[i].h;

	vector<Box> w_sorted;
	vector<Box> h_sorted;
	for(int i=0; i<N; i++){
		w_sorted.push_back(boxes[i]);
		h_sorted.push_back(boxes[i]);
	}
	delete [] boxes;
	
	sort(w_sorted.begin(),w_sorted.end(),width);
	sort(h_sorted.begin(),h_sorted.end(),height);
	
	unordered_map<int,int> width_to_rank;
	vector<vector<Box>> w_rank;
	unsigned int dummy = 0, order = 0;
	for(int i=0; i<N;i++){
		if (dummy != w_sorted[i].w){
			dummy = w_sorted[i].w;
			w_rank.push_back(vector<Box>());
			w_rank[order].push_back(w_sorted[i]);
			width_to_rank[w_sorted[i].w] = order++;
		}
		else
			w_rank[order-1].push_back(w_sorted[i]);
	}

	unordered_map<int,int> height_to_rank;
	vector<vector<Box>> h_rank;
	dummy = order = 0;
	for(int i=0; i < N; i++){
		if (dummy != h_sorted[i].h){
			dummy = h_sorted[i].h;
			h_rank.push_back(vector<Box>());
			h_rank[order].push_back(h_sorted[i]);
			height_to_rank[h_sorted[i].h] = order++;
		}
		else
			h_rank[order-1].push_back(h_sorted[i]);
	}
	
	int solution[N]; for(int i=0; i<N; i++) solution[i]=0;
	// init FT
	PartialMaxs tree(height_to_rank.size());
	// algo starts
	int wsize = w_rank.size();
	int total1=0, total2=0;
	for(int i=0; i<wsize; i++){
		int hsize = w_rank[i].size();		
		for(int j=0; j<hsize; j++){
			struct Box temp = w_rank[i][j];
			solution[total1++] = tree.query( height_to_rank[temp.h] ) + 1;
		}
		for(int j=0; j<hsize; j++){
			struct Box temp = w_rank[i][j];
			tree.update( height_to_rank[temp.h]+1, solution[total2++]);
		}
	}
	
	int result = -1;
	for(int i=0; i<N; i++)
		result = max(result,solution[i]);
	cout << result;
	return 0;
}