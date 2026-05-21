//Each system must allow for storing, recalling, and searching data using a unique key
// provided by the ESP32.

#include <cstdio>
#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;
bool found = false;
// Asa searching is only enabled using the Unique key we would use the student id as the unique key
bool verifyHardwareKey() {
    // Establish connection handle to the physical target port
    // Ensure this matches your verified hardware configuration
    HANDLE hSerial = CreateFileA("\\\\.\\COM6", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        return false; // Physical hardware dongle unmapped or disconnected
    }

    // Configure standard parameters to match runtime controller parameters
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    // Transmit polling challenge byte down the TX line
    DWORD bytesWritten;
    char request = 'R';
    WriteFile(hSerial, &request, 1, &bytesWritten, NULL);

    // Buffer window allowing device execution loops to process and return strings
    Sleep(200);

    // Capture incoming hardware responses from the RX register
    char szBuff[11] = { 0 }; 
    DWORD bytesRead;
    bool isAuthorized = false;

    if (ReadFile(hSerial, szBuff, 10, &bytesRead, NULL)) {
        string receivedKey(szBuff);
        // Verify key integrity against baseline controller string
        if (receivedKey == "ACCESS_123") {
            isAuthorized = true;
        }
    }

    CloseHandle(hSerial); // Terminate interface allocations cleanly
    return isAuthorized;
}

void initializeDatabase(){
    if (ifstream("data.csv")) {
    cout << "Exists"<<endl;
}
else{
    ofstream file("data.csv", ios::app);
    
    if(!file.is_open()){
        cout << "The file could not be Created \n Program is Exiting ....";
        exit(-1);
    }
    file << "ID,Name,Marks\n";
    file.close();
}
}

bool isUnique(string id){
    ifstream file("data.csv");
    if(!file.is_open()){
        cout << "The file could not be Initialozed \n Program is Exiting ....";
        exit(-1);
    }

    string line;
    while (getline(file, line)){
       string current_id = line.substr(0, line.find(','));
        
        if(current_id == id){
            file.close();
            return false;
        }
        
    }
    file.close();
    return true;
}

void appendRecord(){
    string name, marks, id;
    cout << "Enter new Student ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Marks: "; cin >> marks;
    string record = id + "," + name + "," + marks;
    
    if(isUnique(id) == false){
        cout << "This ID already exists"<<endl;
    }
    else{
    ofstream file("data.csv", ios::app);
    
    if(!file.is_open()){
        cout << "The file could not be Created \n Program is Exiting ....";
        exit(-1);
    }
    file << record<<"\n";
    file.close();
    }
}
void searchBy_ID(){
    string search_id;
    cout << "Enter the ID you want to search for ";
    cin >> search_id;
    ifstream file("data.csv");
    
    if(!file.is_open()){
        cout << "The file could not be Created \n Program is Exiting ....";
        exit(-1);
    }
    string line;
    bool found = false;

    while(getline(file,line)){
        string current_id = line.substr(0,line.find(','));

        if(current_id == search_id){
            cout << "------------------------"<<endl;
            cout << "Data: " << line << endl;
            cout << "------------------------"<<endl;
            found  = true;
            break;
        }
        
    }
    if(found == false) { 
            cout << "No student with id : " << search_id << " found in the data base"<< endl;

        }
        file.close();

}

void updateRecord(){
    string StudentID;
    cout <<"Enter the Student ID to change or delete: ";
    cin >> StudentID;
    if(isUnique(StudentID)==false){
        ifstream file ("data.csv");
        ofstream tempfile("temp.csv");

        if(!file.is_open() || !tempfile.is_open()){
            cout << "Error oppening the files";
            exit(-1);
        }
        string line;
        bool found = false;
        cout << "Press 1 to update and 0 to delete";
        int choice;
        cin >> choice;
        cin.ignore();

        string newName, newMarks, newRecord;
        if(choice == 1){
            cout << "Enter New name";
            getline(cin,newName);
            cout << "Enter New marks";
            cin >> newMarks;
            
            newRecord = StudentID + "," + newName + "," + newMarks;
        }
        while(getline(file,line)){
            string current_id = line.substr(0,line.find(','));
            if(StudentID == current_id){
                if (choice == 1){
                    tempfile<<newRecord<<'\n';
                }
            }
            else{
                tempfile<<line<<"\n";
            }
        }
        file.close();
        tempfile.close();
        remove("data.csv");
        rename("temp.csv","data.csv");

        if(choice ==1)
        cout << "The record was sucsessfully Updatetd" << endl;
        else
        cout << "The record has been deleted"<<endl;
    }

} 
int main(){
    cout << "==================================================\n";
    cout << "        STUDENT GRADE BOOK SECURE TERMINAL\n";
    cout << "==================================================\n";
    cout << "Interrogating physical COM channels for hardware verification key...\n";

    // Gatekeeper enforcement validation
    if (!verifyHardwareKey()) {
        cout << "\n[ACCESS DENIED]\n";
        cout << "Ledger processing locked.\n";
        cout << "Insert certified ESP32\n";
        return -1; 
    }

    cout << "\n>> INTERLOCK VALIDATED. Ledger operations activated.\n";
initializeDatabase();
while(true){
    
    int choice;
    cout <<"===== Main Menu =====" << endl;
    cout <<"0. For Exiting"<< endl;
    cout <<"1. For New Entry"<< endl;
    cout <<"2. For Searching by idea"<< endl;
    cout <<"3. For Updating or Delting a record" << endl;
    cout << "=========================="<< endl;
    
    cin >> choice;
    if(choice ==1){
        appendRecord();
    }
    else if(choice == 2){
        searchBy_ID();
    }
    else if(choice == 3){
        updateRecord();
    }
    else if(choice == 0){
        break;
    }
}
    
}