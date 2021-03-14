#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

ifstream fin("teste.txt");

const int base = 256

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

int ExpMax(vector<int> &v, int n){
    int maxim = 0;
    for(int i = 0; i < n; ++i){
        if(abs(v[i]) > maxim)
            maxim = abs(v[i]);
    }
    int exp = 0;
    while(maxim != 0){
        exp++;
        maxim = maxim>>1;
    }
    return exp;
}

void CountSort(vector<int> &v, int exp, int n){
    vector<int> sorted(n+1);
    int i, digit, cs[base+3] = {0};
    for(i = 0; i<n; ++i){
        digit = v[i]>>exp;
        cs[ digit % base]++;
    }
    for(i = 1; i<=base; ++i)
        cs[i] += cs[i-1];
    for(i = n-1; i>=0; --i){
        digit = v[i]>>exp;
        sorted[ cs[digit % base] - 1 ] = v[i];
        cs[digit % base]--;
    }
    for( i = 0; i<n; ++i)
        v[i] = sorted[i];
}

void RadixSort(vector<int> &v, int lf, int rg){
    int exp = ExpMax(v, rg+1);
    for(int i = 0; i<=exp; i += 8)
        CountSort(v, i, rg+1);
}

void RSort(vector<int> &v, int n){

    cout<<"-RadixSort-"<<"\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    RadixSort(v, 0, n-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    std::cout  << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s] |" << std::endl;
    cout<<"\n\n";
}

void PrintTimes(int n, int maxim){
    vector<int>aux;
    /// n random numbers: 1-maxim
    //cout<<"----------"<<n<<" numbers in range 1-"<<maxim<<"----------"<<"\n";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, maxim);
    for(int i = 0; i < n; ++i){
        aux.push_back(distr(gen));
    }
    ///radixsort
    RSort(aux, n);
}


int main()
{
    int n,x,t;
    cin>>t;
    cout<<"| Size of input / Base | RadixSort1024 |"<<"\n"<<"| --- | --- |";
    for(int i = 1; i<=t; ++i){
        cin>>n>>x;
        cout<<"\n|`"<<n<<" numbers range 1 - "<<x<<"`|";
        PrintTimes(n, x);
    }
    return 0;
}
