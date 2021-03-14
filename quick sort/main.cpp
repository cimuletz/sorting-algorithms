#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

ifstream fin("teste.txt");

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

int Pivotare(vector<int> &v, int lf, int rg){
    int pivot = v[rg];
    int i = lf - 1;
    for(int j = lf; j <= rg - 1; ++j){
        if(v[j] <= pivot){
            ++i;
            swap(v[i], v[j]);
        }
    }
    swap(v[i+1], v[rg]);
    return i+1;
}

void InsertionSort(vector<int> &v, int lf, int rg){
    for(int i = lf; i <= rg; ++i)
        for(int j = i; j>lf; --j)
            if(v[j] < v[j-1])
                swap(v[j], v[j-1]);
}

int PickMedian(vector<int> &v, int lf, int rg){

    int i1 = lf;
    int i2 = rg - (rg-lf)/2;
    int i3 = rg;
    int i;

    int x = min(min(v[i1],v[i2]), v[i3]);
    int y = max(max(v[i1],v[i2]), v[i3]);
    if(v[i1] != x && v[i1] != y)
        i = i1;
    else if (v[i2] != x && v[i2] != y)
            i = i2;
         else i = i3;
    return i;
}

void QS(vector<int> &v, int lf, int rg){
    if (rg - lf < 0){
        InsertionSort(v, lf, rg);
        return ;
    }
    int i = PickMedian(v, lf ,rg);

    swap(v[i], v[rg]);
    int p = Pivotare(v, lf, rg);
    QS(v, lf ,p-1);
    QS(v, p+1, rg);
}

int main() {
    int n,x;
    vector<int> v;
    fin>>n;
    for(int i = 0; i<n; ++i){
        fin>>x;
        v.push_back(x);
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    QS(v, 0, n-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    cout<<"\n";
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s]" << std::endl;
    return 0;
}
