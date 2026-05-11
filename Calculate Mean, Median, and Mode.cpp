#include <iostream>
#include <algorithm> // Lib for the function sort()
using namespace std;

// Function declarations
double getMean(int a[], int n);
double getMedian(int a[], int n);
void getMode(int &mode, int &occurrence, int a[], int n);

int main() {
    // Array initialization
    int arr[] = {54, 36, 47, 48, 39, 20, 19, 18, 15, 5};
    
    // Calculating size of array
    int size = sizeof(arr) / sizeof(arr[0]); 
    
    // Initializing required variables
    int mode = 0;
    int occurrence = 0; 

    // Outputs the array
    cout << "Array is: ";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Calculate Mode
    getMode(mode, occurrence, arr, size); 

    // Outputs
    cout << "\nMean: " << getMean(arr, size); 
    cout << "\nMedian: " << getMedian(arr, size); 
    cout << "\nMode: " << mode << " appeared " << occurrence << " time(s)" << endl; 

    return 0;
}

// Function to calculate mean
double getMean(int a[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}

// Function to calculate median
double getMedian(int a[], int n) {
    sort(a, a + n);
    
    if (n % 2 != 0) {
        return a[n / 2];
    } else {
        return (a[(n - 1) / 2] + a[n / 2]) / 2.0;
    }
}

// Function to calculate mode
void getMode(int &mode, int &occurrence, int a[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (a[i] == a[j]) {
                count++; // Increment
            }
        }
        // Find the value which appears most
        if (count > occurrence) {
            occurrence = count;
            mode = a[i];
        }
    }
}
