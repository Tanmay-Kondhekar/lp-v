#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    int n;
    vector<int> arr;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter the Elements: ";
    for (int i = 0; i < n; i++) {
        int x;
        cout << "Enter element no. " << i+1 << " : ";
        cin >> x;
        arr.push_back(x);
    }
    int sum = 0, min=arr[0], max=arr[0];
    
    #pragma omp parallel for reduction(+:sum) reduction(min:min) reduction(max:max)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    int avg = (double)sum/n;

    cout << "\nSum = " << sum;
    cout << "\nMin = " << min;
    cout << "\nMax = " << max;
    cout << "\nAverage = " << avg;
    return 0;
}