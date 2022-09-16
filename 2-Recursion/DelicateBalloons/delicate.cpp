#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int** forS;
int** clips;
int** whichPop;
int** xxx;
int* tutucu;
/*
int S(vector<int>& bs, int x, int y, int N){
    if ( x + 1 == y )
        return 0;
    if (forS[x][y]!=-1)
        return forS[x][y];
    int themax = -1;
    int ind = -1;
    for(int k=x+1; k<y; k++){
        int temp = bs[x] * bs[k] * bs[y] + S(bs,x,k,N) + S(bs,k,y,N);
        if (temp > themax) {
            themax = temp;
            ind = k;
        }
    }
    forS[x][y] = themax;
    whichPop[x][y] = ind;
    return themax;
}
*/


void popAll(int i, int j){
    int obt = whichPop[i][j];
    //cout << "i: " << i << " j: " << j << " Obt: " << obt << endl;
    if ( i+1 == j || i>=j)
        return;
    popAll(i+1,obt-1);
    popAll(obt+1,j-1);
    cout << obt+1 << " ";
}


int S(vector<int>& bs, int x, int y, int N){
    if ( x + 1 == y || x >= y)
        return 0;
    if (forS[x][y]!=-1)
        return forS[x][y];
    int themax = -1;
    int ind = -1;
    for(int k=x+1; k<y; k+=3){
        int temp = bs[x] * bs[k] * bs[y] + S(bs,x+1,k-1,N) + S(bs,k+1,y-1,N);
        if (temp > themax) {
            themax = temp;
            ind = k;
        }
    }
    forS[x][y] = themax;
    whichPop[x][y] = ind;
    if (themax == -1 || ind == -1)
        cout<< "sorun\n";
    return themax;
}

/*
int S_clip(vector<int>& bs, int start, int clip, vector<int>& cs){
    //if ( x + 1 == y || x >= y)
    //    return 0;
    //if (forS[x][y]!=-1)
    //    return forS[x][y];
    int themax = -1;
    int ind = -1;
    for(int k=x+1; k<y; k+=3){
        int temp = bs[x] * bs[k] * bs[y] + S(bs,x+1,k-1,N) + S(bs,k+1,y-1,N);
        if (temp > themax) {
            themax = temp;
            ind = k;
        }
    }
    forS[x][y] = themax;
    whichPop[x][y] = ind;
    if (themax == -1 || ind == -1)
        cout<< "sorun\n";
    return themax;
}
*/
int main(){
    int N;
    cin >> N;
    int buff;
    vector<int> bs;
    for (int i=0; i<N; i++){
        cin >> buff;
        bs.push_back(buff);
    }
    tutucu = new int[N];
    forS = new int*[N];
    clips = new int*[N]; 
    whichPop = new int*[N]; 
    xxx = new int*[N]; 
    for (int i=0; i<N; i++){
        tutucu[i] = i+1;
        forS[i] = new int[N];
        clips[i] = new int[N];
        whichPop[i] = new int[N]; 
        xxx[i] = new int[N]; 
        for(int j=0; j<N; j++){
            forS[i][j] = -1;
            clips[i][j] = -1;
            whichPop[i][j] = -1; 
            xxx[i][j] = -1; 
        }
    }
    /*
    vector<int> steps;
    for(int i=3; i<=N; i+=3)
        steps.push_back(i);
    for(int d = 0; d < N/3; d++){

    }
    */
    int themax = -1;
    int them = -1;
    int thev = -1;
    /*
    for(int m=0; m<=N; m+=3){
        for(int v=0; v<=N; v+=3){
            if (m>v)
                continue;
            //int temp = S(bs,0,m-1,N) + S(bs,m,v-1,N) + S(bs,v,N-1,N);
            int temp
            if (temp>themax){
                themax = temp;
                them = m;
                thev = v;
            }
        }
    }
    */
    // devide 2
    //cout << bs[0]*bs[N-2]*bs[N-1]+ S(bs,1,N-3,N) << endl;
    //cout << bs[0]*bs[1]*bs[N-1]+ S(bs,2,N-2,N) << endl;
    for(int m=0; m<=N; m+=3){
        //int temp = S(bs,0,m-1,N) + S(bs,m,v-1,N) + S(bs,v,N-1,N);
        int temp = S(bs,0,m-1,N) + S(bs,m,N-1,N);
        if (temp>themax){
            themax = temp;
            them = m;
        }
    }
    for(int m=1; m<=N; m+=3){
        //int temp = S(bs,0,m-1,N) + S(bs,m,v-1,N) + S(bs,v,N-1,N);
        int temp = bs[0]*bs[N-2]*bs[N-1]+S(bs,1,m-1,N) + S(bs,m,N-3,N);
        if (temp>themax){
            themax = temp;
            them = m;
        }
    }
    for(int m=2; m<=N; m+=3){
        //int temp = S(bs,0,m-1,N) + S(bs,m,v-1,N) + S(bs,v,N-1,N);
        int temp = bs[0]*bs[1]*bs[N-1]+S(bs,2,m-1,N) + S(bs,m,N-2,N);
        if (temp>themax){
            themax = temp;
            them = m;
        }
    }

    cout << themax <<endl;
    //int result = S(bs,0,N-1,N);
    //cout << result << endl;
    /*
    popAll(0,them-1);
    popAll(them,thev-1);
    popAll(thev,N-1);
    */
    popAll(0,them-1);
    popAll(them,N-1);
    //cout << whichPop[0][N-1]+1;
    return 0;
}