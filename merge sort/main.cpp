#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

ifstream fin("teste.txt");

void test_sortare(vector<long long> &v, int n){
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

void Merge(vector<long long> &v, int lf, int mid, int rg, int maxim){
    vector<int> m;
    int i,j,k;
    k = lf;
    i = lf;
    j = mid+1;
    while( i <= mid && j <= rg ){
        if(v[i] % maxim <= v[j] % maxim)
        {
            v[k] = v[k] + (v[i] % maxim) * maxim;
            ++k;
            ++i;
        }
        else {
             v[k] = v[k] + (v[j] % maxim) * maxim;
             ++k;
             ++j;
        }
    }

    while(i <= mid){
         v[k] = v[k] + (v[i] % maxim) * maxim;
         ++k;
         ++i;
    }

    while(j <= rg){
         v[k] = v[k] + (v[j] % maxim) * maxim;
         ++k;
         ++j;
    }

    for(i = lf; i<=rg; ++i){
        v[i] = v[i] / maxim;
    }
}

void InsertionSort(vector<long long> &v, int lf, int rg){
    for(int i = lf; i <= rg; ++i)
        for(int j = i; j>lf; --j)
            if(v[j] < v[j-1])
                swap(v[j], v[j-1]);
}

void MergeSort(vector<long long> &v, int lf, int rg, int maxim){
    if(rg - lf < 32){
        InsertionSort(v, lf ,rg);
        return;
    }
    int mid = rg - (rg - lf)/2;
    //int mid = (lf+rg)/2;
    MergeSort(v, lf, mid, maxim);
    MergeSort(v, mid+1, rg, maxim);
    Merge(v, lf, mid, rg, maxim);
}

int main()
{
    int maxim = 0;
    int n,x;
    vector<long long> v;
    fin>>n;
    for(int i = 0; i < n; ++i){
        fin>>x;
        if(x < 0)
            cout<<x<<" ";
        if(x > maxim)
            maxim = x;
        v.push_back(x);
    }
    maxim++;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    MergeSort(v, 0, n-1, maxim);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    cout<<"\n";
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s]" << std::endl;
    return 0;
}
