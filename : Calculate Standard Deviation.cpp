#include <iostream>
#include <cmath> 
using namespace std;

// Function declaration
double stdev(double arr[], int n);

int main() {
    // Array initialization
    double arr[] = {90, 67, 20, 5400}; 
    
    // Calculate the size of array
    int size = sizeof(arr) / sizeof(arr[0]); 

    cout << "Array elements are: ";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Standard Deviation is: " << stdev(arr, size) << endl;
    
    return 0;
}

// Function definition
double stdev(double arr[], int n) {
    double sum = 0, avg, sqsum = 0, diff;
    
    // Finding sum
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    // Finding average
    avg = sum / n;
    
    // Finding square sum
    for (int i = 0; i < n; i++) {
        diff = arr[i] - avg;
        sqsum += pow(diff, 2);
    }
    
    // Return standard deviation
    return sqrt(sqsum / (n - 1));
}
