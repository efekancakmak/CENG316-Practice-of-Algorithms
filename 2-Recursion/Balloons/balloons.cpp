#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int** forS;
int** forSrev;
int** whichPop;
int** whichPoprev;
int* tutucu;

int S_out(vector<int>&, int, int&, int&, int&);
int S(vector<int>&, int, int, int);
int S_rev(vector<int>&, int, int, int);

void popAll(int i, int j, int N){
    if ( i+1 != j ){
        int obtain1 = whichPop[i][j];
        popAll(i,obtain1,N);
        popAll(obtain1,j,N);
        cout << tutucu[obtain1] << " ";
        for(int q=obtain1; q<N; q++){
            tutucu[q]--;
        }    
    }    
}

void popAllrev(int i, int j, int N){
    if ( j != 0 || i!=N-1 ){
        int obtain2 = whichPoprev[i][j];
        if(obtain2 < j){
            popAll(obtain2,j,N);
            popAllrev(i,obtain2,N);

        }
        else if(obtain2 > i){
            popAll(i,obtain2,N);
            popAllrev(obtain2,j,N);
        }
        cout << tutucu[obtain2] << " ";
        for(int q=obtain2; q<N; q++){
            tutucu[q]--;
        } 
    }
}

int S_out(vector<int>& bs, int N, int& left, int& middle, int& right){
    int themax = -1;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(j>i){
                int temp1,temp2;
                if (j==N-1 && i == 0){
                    temp1 = S(bs,i,j,N);
                    if (temp1 && temp1 > themax){
                        themax = temp1;
                        left = i;
                        right = j;
                        middle = whichPop[i][j];
                    }  
                    continue;
                }
                else if (i+1 == j){
                    temp2 = S_rev(bs,j,i,N);
                    if (temp2 > themax){
                        themax = temp2;
                        left = i;
                        right = j;
                        middle = whichPoprev[j][i];
                    }
                        continue;
                }
                
                temp1 = S(bs,i,j,N)+S_rev(bs,j,i,N);
                temp2 = temp1;

                vector<int> A = {bs[i] , bs[whichPop[i][j]] , bs[j]};
                sort(A.begin(),A.end());
                temp1 += A[2]*A[2]*A[2] + A[2]*A[2]*A[1];
                
                vector<int> D = {bs[i] , bs[whichPoprev[j][i]] , bs[j]};
                sort(D.begin(),D.end());
                temp2 += D[2]*D[2]*D[2] + D[2]*D[2]*D[1];
                
                if (temp1 >= temp2 && temp1 > themax){
                    themax = temp1;
                    left = i;
                    right = j;
                    middle = whichPop[i][j];
                }
                else if (temp2 >= temp1 && temp2 > themax){
                    themax = temp2;
                    left = i;
                    right = j;
                    middle = whichPoprev[j][i];
                }
            }
        }
    }
    return themax;
}

int S_rev(vector<int>& bs, int x, int y, int N){
    if ( y == 0 && x==N-1 )
        return 0;
    if (forSrev[x][y]!=-1)
        return forSrev[x][y];
    int themax = -1;
    int ind = -1;
    for(int k=x+1; k<N; k++){
        int temp = bs[x] * bs[k] * bs[y] + S(bs,x,k,N) + S_rev(bs,k,y,N);
        if (temp > themax) {
            themax = temp;
            ind = k;
        }
    }
    for(int k=0; k<y; k++){
        int temp = bs[x] * bs[k] * bs[y] + S_rev(bs,x,k,N) + S(bs,k,y,N);
        if (temp > themax) {
            themax = temp;
            ind = k;
        }
    }
    forSrev[x][y] = themax;
    whichPoprev[x][y] = ind;
    return themax;
}

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
    forSrev = new int*[N]; 
    whichPop = new int*[N]; 
    whichPoprev = new int*[N]; 
    for (int i=0; i<N; i++){
        tutucu[i] = i+1;
        forS[i] = new int[N];
        forSrev[i] = new int[N];
        whichPop[i] = new int[N]; 
        whichPoprev[i] = new int[N]; 
        for(int j=0; j<N; j++){
            forS[i][j] = -1;
            forSrev[i][j] = -1;
            whichPop[i][j] = -1; 
            whichPoprev[i][j] = -1; 
        }
    }
    
    int left,right,middle;
    int result = S_out(bs,N,left,middle,right);
    int themin = min(bs[left],min(bs[middle],bs[right]));
    int themax = max(bs[left],max(bs[middle],bs[right]));
    cout << result << endl;
    if(left < middle && middle < right){
        popAll(left,middle,N);
        popAll(middle,right,N);
        popAllrev(right,left,N);
    }
    else if(middle < left){
        popAll(middle,left,N);
        popAllrev(right,middle,N);
        popAll(left,right,N);
    }
    else if(middle > right){
        popAll(right,middle,N);
        popAllrev(middle,left,N);
        popAll(left,right,N);
    }
    
    int imax = max(left,max(middle,right));
    int imin = min(left,min(middle,right));
    int imid = left + right + middle - imax - imin;
    if (themin == bs[imin]){
        cout << 1 << " ";
        if (themax == bs[imax])
            cout << 1 << " ";
        else
            cout << 2 << " ";
    }
    else if(themin == bs[imid]){
        cout << 2 << " ";
        if (themax == bs[imax])
            cout << 1 << " ";
        else
            cout << 2 << " ";
    }
    else if(themin == bs[imax]){
        cout << 3 << " ";
        if (themax == bs[imid])
            cout << 1 << " ";
        else
            cout << 2 << " ";
    }
    cout << 1;
    
    for (int i=0; i<N; i++){
        delete [] forS[i];
        delete [] forSrev[i];
        delete [] whichPop[i]; 
        delete [] whichPoprev[i]; 
    }
    delete [] tutucu;
    delete [] forS;
    delete [] forSrev;
    delete [] whichPop;
    delete [] whichPoprev;

    return 0;
}