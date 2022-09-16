#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
using namespace std;

typedef struct Building{
    int l,h,r;
    Building(){}
    Building(int ll, int hh, int rr):l(ll),h(hh),r(rr){}
} Building;

typedef struct Phone{
    int x,y;
    Phone(){}
    Phone(int xx, int yy):x(xx),y(yy){}
} Phone;

bool lowerThan(Building& A, Building& B){
    return A.l < B.l;
}

typedef struct Xiterator{
    int x;
    int mode; // -1 for entry 1 for exit
    int id; // index of the building
    Xiterator(){}
    Xiterator(int xx, int yy, int zz):x(xx),mode(yy),id(zz){}
} Xiterator;

bool lowerThanX(Xiterator& A, Xiterator& B){
    if (A.x < B.x)
        return true;
    else if (A.x == B.x)
        return A.mode < B.mode;
    else
        return false;
}
bool modeX(Xiterator& A, Xiterator& B){
    return A.mode < B.mode;
}

int N,M,F;
Phone* phones;
Building* buildings;
Xiterator* Xarray;
multimap<int,int> Ytree;
vector<pair<int,int>> theskyline;
multiset<int> yukseklikler;
int main(){
    cin >> N;
    buildings = new Building[N];
    for(int i = 0; i < N; i++){
        cin >> buildings[i].l >> buildings[i].h >> buildings[i].r;
    }
    cin >> M;
    phones = new Phone[M];
    for(int i = 0; i < M; i++){
        cin >> phones[i].x >> phones[i].y;
    }

    Xarray = new Xiterator[2*N];
    for(int i=0; i<N; i++){
        //Xarray[2*i+1] = Xiterator(buildings[i].r, -1, i);
        //Xarray[2*i] = Xiterator(buildings[i].l, 1, i);
        Xarray[2*i+1].id = i;
        Xarray[2*i+1].mode = -1;
        Xarray[2*i+1].x = buildings[i].r;
        Xarray[2*i].id = i;
        Xarray[2*i].mode = 1;
        Xarray[2*i].x = buildings[i].l;
    }

    //sort(Xarray,Xarray+2*N, modeX);
    sort(Xarray,Xarray+2*N, lowerThanX);

    /*
    for(int i=0; i<2*N-1; i++){
        if (Xarray[i].x == Xarray[i+1].x){
            if (Xarray[i].mode == 1 && Xarray[i+1].mode == -1){
                Xiterator temp = Xarray[i+1];
                Xarray[i+1] = Xarray[i];
                Xarray[i] = temp;
                i--;
            }
        }
    }
    */
    for(int i=0; i<2*N-1; i++){
        //cerr << Xarray[i].x << " " << Xarray[i].mode << " " << Xarray[i].id << endl;
    }
    // here I need create the skyline
    int current_h = -1;
    for(int i=0; i<2*N; i++){
        // sinir alanlar icin edge case yazilmali !! 
        if ( Xarray[i].mode == 1 ) { // entry
            Ytree.insert(pair<int, int>(buildings[Xarray[i].id].h, Xarray[i].id));
            yukseklikler.emplace(buildings[Xarray[i].id].h);
            if (buildings[Xarray[i].id].h > current_h) {
                current_h = buildings[Xarray[i].id].h;
                theskyline.push_back(pair<int,int>(buildings[Xarray[i].id].l,current_h));
            }
        }
        else if(Xarray[i].mode == -1){ // exit
            // delete this node from Ytree
            int yid = Xarray[i].id;
            multiset<int>::iterator itr;
            itr = yukseklikler.find(buildings[yid].h);
            //if(itr == yukseklikler.end())
            //    cerr << "amk amk amk \n" << flush;
            //else
                yukseklikler.erase(itr);
            if (yukseklikler.empty()){
                current_h = 0;
                theskyline.push_back(pair<int,int>(buildings[Xarray[i].id].r,current_h));
            }
            else{
                itr = yukseklikler.end();
                itr--;
                current_h = *itr;
                theskyline.push_back(pair<int,int>(buildings[Xarray[i].id].r,current_h));
            }
            continue;
            /*
            cout << "\nCurrent Ytree: \n";
            for(auto i : Ytree){
                cout << i.first << " " << i.second << endl;
            }
            cout << "desired id: " << yid << endl;
            cout << "ytree end\n";
            */
            multimap<int,int>::iterator it;
            it = Ytree.find(buildings[yid].h);
            try{
                Ytree.erase(it);
                throw 31;
            }
            catch(int a){
                cerr << "yid: " << yid << endl;
            }
            // take max height from Ytree;
            if (Ytree.empty()){
                current_h = 0;
                theskyline.push_back(pair<int,int>(buildings[Xarray[i].id].r,current_h));
            }
            else{
                it = Ytree.end();
                it--;
                current_h = it->first;
                theskyline.push_back(pair<int,int>(buildings[Xarray[i].id].r,current_h));
            }
        }
        else{
            cerr << "Wait a minute!\n" << flush;
        }
    }

    int size = theskyline.size();
    for (int i=0; i<size-1; i++){
        if (theskyline[i].first == theskyline[i+1].first) {
            if (theskyline[i].second > theskyline[i+1].second)
                theskyline.erase(theskyline.begin()+i+1);
            else{
                theskyline.erase(theskyline.begin()+i);
            }
            i--;
            size--;
        }
    }

    /*
    size = theskyline.size();
    for (int i =0; i<size-1; i++){
        if (theskyline[i].second == theskyline[i+1].second){
            theskyline.erase(theskyline.begin()+i+1);
            i--;
            size--;

        }
    }
    */
    //for(auto i : theskyline){
        //cout << i.first << " " << i.second << endl;
    //}


    map<int,int> skylinemap;

    size = theskyline.size();
    for (int i =0; i<size; i++){
        skylinemap[theskyline[i].first] = theskyline[i].second; 
    }

    // now extracting the solution
    F = 0;
    map<int,int>::iterator mit;
    for(int p=0; p<M; p++){
        mit = skylinemap.lower_bound(phones[p].x);
        if (phones[p].x == mit->first && mit->second >= phones[p].y){
            continue;
        }
        mit--;
        if (mit->second < phones[p].y)
            F++;
    }
    cout << F;    
    return 0;
}