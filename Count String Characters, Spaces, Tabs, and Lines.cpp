#include <iostream>
#include <string>
using namespace std;

// Function declaration
void countString(string text, int &space, int &tabs, int &lines);

int main() {
    string text;
    int space = 0;
    int tabs = 0;
    int lines = 1;

    // Taking input from the user
    cout << "Enter a String: ";
    getline(cin, text);

    // Function call
    countString(text, space, tabs, lines);

    // Displaying results
    cout << "\nTotal Characters: " << text.size();
    cout << "\nTotal Spaces: " << space;
    cout << "\nTotal Tabs: " << tabs;
    cout << "\nTotal Lines: " << lines << endl;

    return 0;
}

// Function definition
void countString(string text, int &space, int &tabs, int &lines) {
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') {
            space++;
        } 
        else if (text[i] == '\t') {
            tabs++;
        } 
        else if (text[i] == '\n') {
            lines++;
        }
    }
}
