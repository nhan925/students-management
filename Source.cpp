#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>
using namespace std;

fstream ioput;
int NumOfStudent = 0;
const int MAX = 100;

struct Student {
    int id = 0, age = 0;
    string name = "", genre = "", title = "";
    double maths = 0, physics = 0, chemistry = 0, average = 0;

    void ImportFile() {
        ioput >> id >> name >> genre >> age >> maths >> physics >> chemistry >> average >> title;
    }

    void Cal() {
        average = (maths + physics + chemistry) / 3.0;
        if (average >= 8) title = "Excellent";
        else if (average >= 6.5) title = "Good";
        else if (average >= 5) title = "Average";
        else title = "Weak";
    }

    void ExportFile() {
        ioput << setprecision(1) << fixed << setw(5) << internal << id << setw(14) << internal << name;
        ioput << setprecision(1) << fixed << setw(14) << internal << genre << setw(14) << internal << age << setw(14) << internal;
        ioput << setprecision(1) << fixed << maths << setw(14) << internal << physics << setw(14) << internal << chemistry << setw(14) << internal;
        ioput << setprecision(1) << fixed << average << setw(14) << internal << title << endl;
    }

    void Display() {
        cout << setprecision(1) << fixed << setw(5) << internal << id << setw(14) << internal << name;
        cout << setprecision(1) << fixed << setw(14) << internal << genre << setw(14) << internal << age << setw(14) << internal;
        cout << setprecision(1) << fixed << maths << setw(14) << internal << physics << setw(14) << internal << chemistry << setw(14) << internal;
        cout << setprecision(1) << fixed << average << setw(14) << internal << title << endl;
    }
};

void CreateFile();
void Input(Student st[]);
int IDMax(Student st[]);
void Add(Student st[]);
void Update(Student st[]);
void Delete(Student st[]);
void FindName(Student st[]);
void Display(Student st[]);
void SortGPA(Student st[]);
void SortName(Student st[]);
void Output(Student st[]);
void Menu();


int main() {
    CreateFile();
    system("color 0a");
    Student st[MAX];
    Input(st);
    int select = 0;
    while (1) {
        Menu();
        cout << "Input a selection: ";
        cin >> select;
        if (select == 0) return 0;
        else if (select == 1) {
            Add(st);
            system("pause");
            system("cls");
        }
        else if (select == 2) {
            Update(st);
            system("pause");
            system("cls");
        }
        else if (select == 3) {
            Delete(st);
            system("pause");
            system("cls");
        }
        else if (select == 4) {
            FindName(st);
            system("pause");
            system("cls");
        }
        else if (select == 5) {
            SortGPA(st);
            system("pause");
            system("cls");
        }
        else if (select == 6) {
            SortName(st);
            system("pause");
            system("cls");
        }
        else if (select == 7) {
            Display(st);
            system("pause");
            system("cls");
        }
        else if (select == 8) {
            cout << "Are you sure to save changes? (Y/N): ";
            char sure;
            cin >> sure;
            if (sure == 'Y') {
                Output(st);
                system("pause");
                system("cls");
            }
            else system("cls");
        }

    }
}

void CreateFile() {
    ioput.open("student.txt", ios::app);
    ioput.close();
}

void Input(Student st[]) {
    ioput.open("student.txt", ios::in);
    while (!ioput.eof())
        st[NumOfStudent++].ImportFile();
    ioput.close();
    NumOfStudent--;
}

int IDMax(Student st[]) {
    int max = st[0].id;
    for (int i = 1; i < NumOfStudent; i++)
        if (st[i].id > max)
            max = st[i].id;
    return max;
}

void Add(Student st[]) {
    st[NumOfStudent].id = IDMax(st) + 1;
    cout << "Name: "; cin >> st[NumOfStudent].name;
    cout << "Genre: "; cin >> st[NumOfStudent].genre;
    cout << "Age: "; cin >> st[NumOfStudent].age;
    cout << "Maths Grade: "; cin >> st[NumOfStudent].maths;
    cout << "Physics Grade: "; cin >> st[NumOfStudent].physics;
    cout << "Chemistry Grade: "; cin >> st[NumOfStudent].chemistry;
    st[NumOfStudent].Cal();
    NumOfStudent++;
    cout << "Successful!\n";
}

void Update(Student st[]) {
    int ID = 0;
    cout << "ID of student to update: "; cin >> ID;
    int index = 0;
    for (int i = 0; i < NumOfStudent; i++)
        if (ID == st[i].id)
            index = i;
    int select = 0;
    cout << "Select what to update:\n";
    cout << "1. Name\n";
    cout << "2. Genre\n";
    cout << "3. Maths Grade\n";
    cout << "4. Physics Grade\n";
    cout << "5. Chemistry Grade\n";
    cout << "Input a selection: "; cin >> select;
    if (select == 1) {
        cout << "Enter new name: ";
        cin >> st[index].name;
    }
    else if (select == 2) {
        cout << "Enter new genre: ";
        cin >> st[index].genre;
    }
    else if (select == 3) {
        cout << "Enter new maths grade: ";
        cin >> st[index].maths;
    }
    else if (select == 4) {
        cout << "Enter new physics grade ";
        cin >> st[index].physics;
    }
    else if (select == 5) {
        cout << "Enter new chemistry grade: ";
        cin >> st[index].chemistry;
    }
    st[index].Cal();
    cout << "Successful!\n";
}

void Delete(Student st[]) {
    int ID = 0;
    cout << "ID of student to delete: "; cin >> ID;
    int index = 0;
    for (int i = 0; i < NumOfStudent; i++)
        if (ID == st[i].id)
            index = i;
    for (int i = index; i < NumOfStudent - 1; i++)
        st[i] = st[i + 1];
    NumOfStudent--;
    cout << "Successful!\n";
}

void FindName(Student st[]) {
    int index[MAX] = { 0 };
    int count = 0;
    string name;
    cout << "Enter name to find: ";
    cin >> name;
    for (int i = 0; i < NumOfStudent; i++)
        if (st[i].name == name)
            index[count++] = i;
    if (count == 0) cout << "No students found!\n";
    else {
        cout << "_______________________________________________________________________________________________________________________\n";
        cout << setw(5) << internal << "ID" << setw(14) << internal << "Name";
        cout << setw(14) << internal << "Genre" << setw(14) << internal << "Age" << setw(14) << internal;
        cout << "Maths" << setw(14) << internal << "Physics" << setw(14) << internal << "Chemistry" << setw(14) << internal;
        cout << "Average" << setw(14) << internal << "Title" << endl;
        for (int i = 0; i < count; i++)
            st[index[i]].Display();
        cout << "-----------------------------------------------------------------------------------------------------------------------\n";
    }
}

void Display(Student st[]) {
    cout << "_______________________________________________________________________________________________________________________\n";
    cout << setw(5) << internal << "ID" << setw(14) << internal << "Name";
    cout << setw(14) << internal << "Genre" << setw(14) << internal << "Age" << setw(14) << internal;
    cout << "Maths" << setw(14) << internal << "Physics" << setw(14) << internal << "Chemistry" << setw(14) << internal;
    cout << "Average" << setw(14) << internal << "Title" << endl;
    for (int i = 0; i < NumOfStudent; i++)
        st[i].Display();
    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
}

void SortGPA(Student st[]) {
    Student temp;
    for (int i = 0; i < NumOfStudent - 1; i++)
        for (int j = 0; j < NumOfStudent - 1 - i; j++)
            if (st[j].average > st[j + 1].average) {
                temp = st[j];
                st[j] = st[j + 1];
                st[j + 1] = temp;
            }
    Display(st);
}

void SortName(Student st[]) {
    Student temp;
    for (int i = 0; i < NumOfStudent - 1; i++)
        for (int j = 0; j < NumOfStudent - 1 - i; j++)
            if (st[j].name > st[j + 1].name) {
                temp = st[j];
                st[j] = st[j + 1];
                st[j + 1] = temp;
            }
    Display(st);
}

void Output(Student st[]) {
    ioput.open("student.txt", ios::out);
    for (int i = 0; i < NumOfStudent; i++)
        st[i].ExportFile();
    ioput.close();
    cout << "Changes have been saved!\n";
}

void Menu() {
    cout << "                 PROGRAM TO MANAGE STUDENTS C++                  \n";
    cout << "                          BY NHAN925                             \n";
    cout << " ________________________________________________________________\n";
    cout << "|  0. Exit                                                       |\n";
    cout << "|  1. Add a student                                              |\n";
    cout << "|  2. Update information of student by ID                        |\n";
    cout << "|  3. Delete a student by ID                                     |\n";
    cout << "|  4. Search students by name                                    |\n";
    cout << "|  5. Sort students by GPA                                       |\n";
    cout << "|  6. Sort students by name                                      |\n";
    cout << "|  7. Display the list of students                               |\n";
    cout << "|  8. Save changes                                               |\n";
    cout << " ----------------------------------------------------------------\n";
}
