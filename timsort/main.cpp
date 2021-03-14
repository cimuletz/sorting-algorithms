#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

ifstream fin("teste.txt");

const int segment = 64;

void test_sortare(vector<int> &v, int n){
    bool sorted = true;
    for (int i = 0; i < n-1; ++i){
        if (v[i] > v[i+1]){
            sorted = false;
            break;
        }
    }
    if (sorted == true)
        cout<<"Ok";
    else cout<<"Not ok";
}

void InsertionSort(vector<int> &v, int lf, int rg){
    for(int i = lf; i <= rg; ++i)
        for(int j = i; j>lf; --j)
            if(v[j] < v[j-1])
                swap(v[j], v[j-1]);
}

int FloorSearch(vector<int> &v, int lf, int rg, int x){

    if( lf > rg )
        return 0;
    if(x >= v[rg])
        return rg+1;
    int mid = rg - (rg - lf)/2;
    if(mid > 0 && v[mid-1] < x && v[mid] >= x)
        return mid;
    if(x < v[mid])
        return FloorSearch(v, lf, mid-1, x);
    return FloorSearch(v, mid+1, rg, x);

}

void BinaryInsertionSort(vector<int> &v, int lf, int rg){
    vector<int> aux;
    aux.push_back(v[lf]);
    for(int i = lf + 1; i <= rg; ++i)
    {
        int poz = FloorSearch(aux, 0, aux.size() - 1, v[i]);
        if(poz >= aux.size())
            aux.push_back(v[i]);
        else{
            int n = aux.size();
            aux.push_back(aux[n-1]);
            for(int j = n-1; j > poz; --j)
                aux[j] = aux[j-1];
            aux[poz] = v[i];
        }
    }
    for(int i = lf, j = 0; i<=rg; ++i, ++j)
        v[i] = aux[j];
}

void Merge(vector<int> &v, int lf, int mid, int rg){
    vector<int> m;
    int i,j,k;
    k = 0;
    i = lf;
    j = mid+1;
    while( i <= mid && j <= rg ){
        if(v[i] < v[j])
            m.push_back(v[i++]);
        else m.push_back(v[j++]);
    }

    while(i <= mid)
        m.push_back(v[i++]);

    while(j <= rg)
        m.push_back(v[j++]);

    for(i = lf; i<=rg; ++i){
        v[i] = m[i-lf];
    }
}

void TimSort(vector<int> &v, int lf, int rg){

    ///sortam vectorul pe segmente de 32 de elemente cu BIS

    for(int i = 0; i <= rg; i+= segment){
        int l = i;
        int r = min(i+segment-1, rg);
        BinaryInsertionSort(v, l, r);
    }

    for(int i = segment; i <= rg; i += i){

        ///merge pe segmente de cate i elemente
        for(int j = 0; j<=rg; j += 2*i){
            int l = j;
            int m = l+i-1;
            int r = min( m+i, rg);
            Merge(v, l, m, r);
        }
    }
}

int main(){

    int n,x;
    vector<int> v;
    fin>>n;
    for(int i = 0; i < n; ++i){
        fin>>x;
        v.push_back(x);
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    TimSort(v, 0, n-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    cout<<"\n";
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s]" << std::endl;
    return 0;
}
