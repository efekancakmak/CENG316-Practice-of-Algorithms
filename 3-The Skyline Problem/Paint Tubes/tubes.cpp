#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
 
typedef struct Building{
    long l,h,r;
} Building;

typedef struct Xiterator{
    long x,h,mode; // -1 for entry 1 for exit
} Xiterator;

bool lowerThanX(Xiterator& A, Xiterator& B){
    if (A.x < B.x)
        return true;
    else if (A.x == B.x)
        return A.mode < B.mode;
    else
        return false;
}

long N,F;
Building* buildings;
Xiterator* Xarray;
vector<pair<long,long>> theskyline;
multiset<long> yukseklikler;

int main()
{
    cin >> N;
    buildings = new Building[N];
    for(long i = 0; i < N; i++){
        cin >> buildings[i].l >> buildings[i].h >> buildings[i].r;
    }
    Xarray = new Xiterator[2*N];
    for(long i=0; i<N; i++){
        Xarray[2*i].h = buildings[i].h;
        Xarray[2*i].mode = 1;
        Xarray[2*i].x = buildings[i].l;
        Xarray[2*i+1].h = buildings[i].h;
        Xarray[2*i+1].mode = -1;
        Xarray[2*i+1].x = buildings[i].r;
    }

    sort(Xarray,Xarray+2*N, lowerThanX);

    yukseklikler.insert(0);
    long max_h = 0;
    for(long i=0; i<2*N; i++){
        if (Xarray[i].mode == 1) 
            yukseklikler.insert(Xarray[i].h);
        else if(Xarray[i].mode == -1)
            yukseklikler.erase(yukseklikler.find(Xarray[i].h));

        long temp = *yukseklikler.rbegin();
        if (temp != max_h) {
            max_h = temp;
            theskyline.push_back(pair<long,long>(Xarray[i].x, max_h));
        }
    }


    //sort(theskyline.begin(),theskyline.end());
    long size = theskyline.size();   
    F = 0;
    for (long i=0; i<size-1; i++){
        F += (theskyline[i+1].first - theskyline[i].first) * theskyline[i].second; 
    }
    cout << F; 
    return 0;
}