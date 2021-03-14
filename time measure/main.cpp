#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>
#include <random>

using namespace std;

const int N = 10000001;

void test_sortare(vector<int> &v, int n){
    bool sorted = true;
    for (int i = 0; i < n-1; ++i){
        if (v[i] > v[i+1]){
            sorted = false;
            break;
        }
    }
    if (sorted == true)
        cout<<"Ok\n";
    else cout<<"Not ok\n";
}

namespace IntroSort{

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

    void MergeSort(vector<int> &v, int lf, int rg){
        if(rg - lf < 32){
            InsertionSort(v, lf ,rg);
            return;
        }
        int mid = rg - (rg - lf)/2;
        //int mid = (lf+rg)/2;
        MergeSort(v, lf, mid);
        MergeSort(v, mid+1, rg);
        Merge(v, lf, mid, rg);
    }

    void IntroSort(vector<int> &v, int lf, int rg, int dLimit){
        if (rg - lf < 16){
            InsertionSort(v, lf, rg);
            return ;
        }
        else{
        if(dLimit == 0){
            MergeSort(v, lf, rg);
            return;
        }
        dLimit--;
        int i = PickMedian(v, lf ,rg);

        swap(v[i], v[rg]);
        int p = Pivotare(v, lf, rg);
        IntroSort(v, lf ,p-1,dLimit);
        IntroSort(v, p+1, rg, dLimit);
        }
    }
}

namespace MergeSort{

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

    void InsertionSort(vector<int> &v, int lf, int rg){
        for(int i = lf; i <= rg; ++i)
            for(int j = i; j>lf; --j)
                if(v[j] < v[j-1])
                    swap(v[j], v[j-1]);
    }

    void MergeSort(vector<int> &v, int lf, int rg){
        if(rg - lf < 32){
            InsertionSort(v, lf ,rg);
            return;
        }
        int mid = rg - (rg - lf)/2;
        //int mid = (lf+rg)/2;
        MergeSort(v, lf, mid);
        MergeSort(v, mid+1, rg);
        Merge(v, lf, mid, rg);
    }

}

namespace QuickSort{
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
        if (rg - lf < 10){
            InsertionSort(v, lf, rg);
            return ;
        }
        int i = PickMedian(v, lf ,rg);

        swap(v[i], v[rg]);
        int p = Pivotare(v, lf, rg);
        QS(v, lf ,p-1);
        QS(v, p+1, rg);
    }

}

namespace RadixSort{

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
    int i, digit, cs[300] = {0};
    for(i = 0; i<n; ++i){
        digit = v[i]>>exp;
        cs[ digit % 256]++;
    }
    for(i = 1; i<=255; ++i)
        cs[i] += cs[i-1];
    for(i = n-1; i>=0; --i){
        digit = v[i]>>exp;
        sorted[ cs[digit % 256] - 1 ] = v[i];
        cs[digit % 256]--;
    }
    for( i = 0; i<n; ++i)
        v[i] = sorted[i];
}

void RadixSort(vector<int> &v, int lf, int rg){
    int exp = ExpMax(v, rg+1);
    for(int i = 0; i<=exp; i += 8)
        CountSort(v, i, rg+1);
}
}

namespace TimSort{

    const int segment = 64;

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
                int m = min(l+i-1,rg);
                int r = min( m+i, rg);
                Merge(v, l, m, r);
            }
        }
    }
}

void Copy(vector<int> &a, vector<int> &b){
    for(int i = 0; i<a.size(); ++i)
        b[i] = a[i];
}

void RSort(vector<int> &v, int n){

    cout<<"-RadixSort-"<<"\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    RadixSort::RadixSort(v, 0, n-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s]" << std::endl;
    cout<<"\n\n";
}
void TSort(vector<int> &v, int n){
    cout<<"-TimSort-"<<"\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    TimSort::TimSort(v, 0, n-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s]" << std::endl;
    cout<<"\n\n";
}
void QSort(vector<int> &v, int n){
    cout<<"-QuickSort-"<<"\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    QuickSort::QS(v, 0, n-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s]" << std::endl;
    cout<<"\n\n";
}
void MSort(vector<int> &v, int n){
    cout<<"-MergeSort-"<<"\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    MergeSort::MergeSort(v, 0, n-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s]" << std::endl;
    cout<<"\n\n";
}
void ISort(vector<int> &v, int n){
    cout<<"-IntroSort-"<<"\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int dLimit = 2 * (int)log(n);
    IntroSort::IntroSort(v, 0, n-1, dLimit);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s]" << std::endl;
    cout<<"\n\n";
}
void STLSort(vector<int> &v, int n){
    cout<<"-STLSort-"<<"\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    sort(v.begin(), v.end());
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    test_sortare(v, n);
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 << "[s]" << std::endl;
    cout<<"\n\n";
}

void PrintTimes(int n, int maxim){
    vector<int> v(n+1), aux;
    /// n random numbers: 1-maxim
    cout<<"----------"<<n<<" numbers in range 1-"<<maxim<<"----------"<<"\n";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, maxim);
    for(int i = 0; i < n; ++i){
        aux.push_back(distr(gen));
    }
    Copy(aux, v);
    STLSort(v, n);
    Copy(aux, v);
    /// introsort
    ISort(v, n);
    Copy(aux, v);

    ///mergesort
    MSort(v, n);
    Copy(aux, v);

    ///quicksort
    QSort(v, n);
    Copy(aux, v);

    ///TimSort
    TSort(v, n);
    Copy(aux, v);

    ///radixsort
    RSort(v, n);
    Copy(aux, v);
}

void PrintDecreasing(){
    vector<int> v(N), aux;
    int x;
    /// 10 million decreasing numbers
    cout<<"----------10^7 numbers in decreasing order----------"<<"\n";
    ifstream fin("decreasing.txt");
    for(int i = 0; i < N; ++i){
        fin>>x;
        aux.push_back(x);
    }
    Copy(aux, v);
    STLSort(v, N);
    Copy(aux, v);
    /// introsort
    ISort(v, N);
    Copy(aux, v);

    ///mergesort
    MSort(v, N);
    Copy(aux, v);

    ///quicksort
    QSort(v, N);
    Copy(aux, v);

    ///TimSort
    TSort(v, N);
    Copy(aux, v);

    ///radixsort
    RSort(v, N);
    Copy(aux, v);
}

void PrintOnes(){
    vector<int> v(N), aux;
    int x;
    /// 10 million 1s
    cout<<"----------10^7 1s----------"<<"\n";
    ifstream fin("only1s.txt");
    for(int i = 0; i < N; ++i){
        fin>>x;
        aux.push_back(x);
    }
    Copy(aux, v);
    STLSort(v, N);
    Copy(aux, v);
    /// introsort
    ISort(v, N);
    Copy(aux, v);

    ///mergesort
    MSort(v, N);
    Copy(aux, v);

    ///quicksort
    QSort(v, N);
    //cout<<"-QuickSort-\nCan't sort this!"<<"\n\n";
    Copy(aux, v);

    ///TimSort
    TSort(v, N);
    Copy(aux, v);

    ///radixsort
    RSort(v, N);
    Copy(aux, v);
}

int main() {
    int n,x,t;
    cin>>t;
    for(int i = 1; i<=t; ++i){
        cin>>n>>x;
        PrintTimes(n, x);
    }
    PrintDecreasing();
    return 0;
}
