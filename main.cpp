#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

struct Student {
    int id;
    string name;
    float score;
};

vector<Student> students;


bool login() {
    string user, pass;
    cout << CYAN << "\n=== LOGIN ===\n" << RESET;

    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user == "admin" && pass == "1234") {
        cout << GREEN << "✔ Login success!\n" << RESET;
        return true;
    }

    cout << RED << "✘ Wrong credentials!\n" << RESET;
    return false;
}


void saveToFile() {
    ofstream file("students.json");

    file << "[\n";
    for (int i = 0; i < students.size(); i++) {
        file << "  {\n";
        file << "    \"id\": " << students[i].id << ",\n";
        file << "    \"name\": \"" << students[i].name << "\",\n";
        file << "    \"score\": " << students[i].score << "\n";
        file << "  }";

        if (i != students.size() - 1) file << ",";
        file << "\n";
    }
    file << "]";

    file.close();
    cout << GREEN << "✔ Saved to students.json\n" << RESET;
}


void loadFromFile() {
    ifstream file("students.json");
    if (!file) return;

    students.clear();

    string line;
    Student s;

    while (getline(file, line)) {
        if (line.find("\"id\"") != string::npos) {
            s.id = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("\"name\"") != string::npos) {
            int start = line.find("\"", line.find(":")) + 1;
            int end = line.find("\"", start);
            s.name = line.substr(start, end - start);
        }
        else if (line.find("\"score\"") != string::npos) {
            s.score = stof(line.substr(line.find(":") + 1));
            students.push_back(s);
        }
    }

    file.close();
}


void header() {
    cout << CYAN;
    cout << "\n==============================\n";
    cout << "   SCHOOL MANAGER (V3)   \n";
    cout << "==============================\n";
    cout << RESET;
}


void addStudent() {
    Student s;
    cout << YELLOW << "\n[ Add Student ]\n" << RESET;

    cout << "ID: ";
    cin >> s.id;
    cout << "Name: ";
    cin >> s.name;
    cout << "Score: ";
    cin >> s.score;

    students.push_back(s);
    cout << GREEN << "✔ Student added!\n" << RESET;
}


void showStudents() {
    cout << YELLOW << "\n[ Student List ]\n" << RESET;

    if (students.empty()) {
        cout << RED << "No data!\n" << RESET;
        return;
    }

    cout << CYAN << "-----------------------------\n";
    cout << "ID\tName\tScore\n";
    cout << "-----------------------------\n" << RESET;

    for (auto s : students) {
        cout << s.id << "\t" << s.name << "\t" << s.score << endl;
    }
}


void searchStudent() {
    int id;
    cout << YELLOW << "\n[ Search ]\n" << RESET;

    cout << "Enter ID: ";
    cin >> id;

    for (auto s : students) {
        if (s.id == id) {
            cout << GREEN << "✔ Found: " << s.name 
                 << " (" << s.score << ")\n" << RESET;
            return;
        }
    }
    cout << RED << "Not found!\n" << RESET;
}

int main() {
    if (!login()) return 0;

    loadFromFile(); 

    int choice;
    while (true) {
        header();
        cout << "\n1. Add Student\n";
        cout << "2. Show Students\n";
        cout << "3. Search Student\n";
        cout << "4. Save\n";
        cout << "5. Exit\n";

        cout << CYAN << "\nChoose: " << RESET;
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: showStudents(); break;
            case 3: searchStudent(); break;
            case 4: saveToFile(); break;
            case 5:
                saveToFile();
                cout << GREEN << "Goodbye\n" << RESET;
                return 0;
            default:
                cout << RED << "Invalid!\n" << RESET;
        }
    }
}
