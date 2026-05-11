#include <iostream>
#include <stdlib.h>
using namespace std;

// Function declaration
void findMinMax(float arr[], int size, float &min, float &max);

int main() {
    float max, min; // Variable initialization
    float arr[] = {1500, 1, 200, -1}; // Array definition
    
    // Calculating size of array
    int size = sizeof(arr) / sizeof(arr[0]); 

    cout << "Array is: ";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Function call
    findMinMax(arr, size, min, max);

    cout << "Maximum value is: " << max << endl;
    cout << "Minimum value is: " << min << endl;

    return 0;
}

// Function definition
void findMinMax(float arr[], int size, float &min, float &max) {
    min = arr[0];
    max = arr[0];
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
}
