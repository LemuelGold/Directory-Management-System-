#include <iostream>
#include <string>
#include <direct.h>  
#include <io.h>      

using namespace std;

void list_files() {
    string path = "*";
    _finddata_t file;
    intptr_t handle = _findfirst(path.c_str(), &file);

    if (handle == -1) {
        cout << "No files found.\n";
        return;
    }

    do {
        if (!(file.attrib & _A_SUBDIR)) {
            cout << file.name << endl;
        }
    } while (_findnext(handle, &file) == 0);

    _findclose(handle);
}

void create_directory() {
    string dir_name;
    cout << "Enter directory name: ";
    getline(cin, dir_name);

    if (_mkdir(dir_name.c_str()) == 0) {
        cout << "Directory created.\n";
    } else {
        cout << "Directory already exists. Please try again.\n";
    }
}

void change_directory() {
    cout << "1. Go up one level\n2. Go to root directory\n3. Go to a specific directory\n";
    int choice;
    cout << "Enter your choice:  ";
    cin >> choice;
    cin.ignore();  

    switch (choice) {
        case 1: {
            char cwd[256];
            _getcwd(cwd, sizeof(cwd));
            string current_path(cwd);
            size_t pos = current_path.find_last_of("\\/");
            if (pos != string::npos) {
                current_path = current_path.substr(0, pos);
                _chdir(current_path.c_str());
                cout << "Moved up one level.\n";
            } else {
                cout << "Already at the root directory.\n";
            }
            break;
        }
        case 2:
            _chdir("C:\\");
            cout << "Moved to root directory.\n";
            break;
        case 3: {
            string new_dir;
            cout << "Enter path: ";
            getline(cin, new_dir);
            if (_chdir(new_dir.c_str()) == 0) {
                cout << "Changed to directory: " << new_dir << endl;
            } else {
                cout << "Directory does not exist.\n";
            }
            break;
        }
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

void showFileListMenu() {
    int fileChoice;

    do {
        cout << "\n";
        cout << " LIST FILE DETAILS\n"; 
        cout << "------------------\n";
        cout << "1. List All Files\n";
        cout << "2. List by Extension\n";
        cout << "3. List by Name\n"; 
        cout << "Enter the Number: ";
        cin >> fileChoice;

        switch (fileChoice) {
            case 1:
                list_files();
                break;
            
            default:
                cout << "Invalid choice.\n";
                break;
        }
    } while (fileChoice != 1);  
}

int main() {
    int choice;

    do {
        cout << "MAIN MENU\n";
        cout << "--------------------\n";
        cout << "1. Display List of Files\n";
        cout << "2. Create New Directory\n";
        cout << "3. Change the Working Directory\n";
        cout << "4. Exit\n";
        cout << "Enter the Number: ";
        cin >> choice;
        cin.ignore();  
        switch (choice) {
            case 1:
                showFileListMenu(); 
                break;
            case 2:
                create_directory();
                break;
            case 3:
                change_directory();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:	
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0; 
}
