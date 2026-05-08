#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void print(vector<int>& a) {
    for (int i: a) {
        cout << i << " ";
    }
    cout << endl;
}

void seq_b(vector<int> &a) {
    for (int i = 0; i < a.size()-1; i++) {
        for (int j = 0; j < a.size()-i-1; j++) {
            if (a[j] > a[j+1]) {
                swap(a[j], a[j+1]);
            }
        }
    }
}

void pb(vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        #pragma omp parallel for
        for (int j = 0; j < a.size()-1; j+=2) {
            if (a[j] > a[j+1]) {
                swap(a[j], a[j+1]);
            }
        }

        #pragma omp parallel for
        for (int j = 1; j < a.size()-1; j+=2) {
            if (a[j] > a[j+1]) {
                swap(a[j], a[j+1]);
            }
        }
    }
}

void mergee(vector<int> &a, int l, int m1, int r) {
    vector<int>t;
    int i = l, j = m1+1;

    while (i <= m1 && j <= r) {
        if (a[i] <= a[j]) {
            t.push_back(a[i++]);
        }
        else {
            t.push_back(a[j++]);
        }
    }
    
    while(i <= m1) t.push_back(a[i++]);
    while(j <= r) t.push_back(a[j++]);

    for (int k = 0; k < t.size(); k++) {
        a[l+k] = t[k];
    }
}

void m(vector<int> &a, int l, int r) {
    if (l < r) {
        int m1 = (l+r)/2;
        m(a, l, m1);
        m(a, m1+1, r);

        mergee(a, l, m1, r);
    }
}

void pm(vector<int> &a, int l, int r) {
    if (l < r) {
        int m1 = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            pm(a, l, m1);

            #pragma omp section
            pm(a, m1+1, r);
        }

        mergee(a, l, m1, r);
    }
}


int main() {
    int n;
    cout << "Enter the number of elements: "; 
    cin >> n;

    vector<int> arr,a,b,c,d;

    for (int i = 0; i < n; i++) {
        int x;
        cout << "Enter Elemnt number " << i+1 << " : ";
        cin >> x;
        arr.push_back(x);
    }

    a=b=c=d = arr;

    double t;
    cout << "Array-> \n";
    print(a);
    cout << "Started Seq. Bubble :\n";
    t = omp_get_wtime();
    seq_b(a);
    cout << "Completed in " << omp_get_wtime() - t << " \n";

    cout << "Parallel Bubble sort\n";
    t = omp_get_wtime();
    pb(b);
    cout << "Completed in " << omp_get_wtime() - t << " \n";
    print(b);

    cout << "Merge Seq: ";
    t = omp_get_wtime();
    m(c, 0, n-1);
    cout << "Completed in " << omp_get_wtime() - t << " \n";
    print(c);

    cout << "Merge partllel: ";
    t = omp_get_wtime();
    pm(d, 0, n-1);
    cout << "Completed in " << omp_get_wtime() - t << " \n";
    print(d);

    return 0;
}