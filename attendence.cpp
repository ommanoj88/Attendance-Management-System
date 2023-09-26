#include <iostream>
#include <map>
#include <string>
using namespace std;

class Node {
public:
    string name;
    int roll_number;
    map<string, map<string, bool>> attendance;

    Node* prev;
    Node* next;

    Node(string name, int roll_number) {
        this->name = name;
        this->roll_number = roll_number;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void add_student(string name, int roll_number) {
        Node* new_node = new Node(name, roll_number);
        if (this->head == nullptr) {
            this->head = new_node;
            this->tail = new_node;
        } else {
            this->tail->next = new_node;
            new_node->prev = this->tail;
            this->tail = new_node;
        }
    }

    void take_attendance(string subject) {
        Node* current_node = this->head;
        string date;
        cout << "Enter the date for which you want to take attendance (dd-mm-yyyy): ";
        cin >> date;

        while (current_node != nullptr) {
            string attendance_status;
            cout << "Is " << current_node->name << " present in " << subject << "? (Y/N)";
            cin >> attendance_status;

            if (attendance_status == "Y" || attendance_status == "y") {
                current_node->attendance[subject][date] = true;
            } else {
                current_node->attendance[subject][date] = false;
            }

            current_node = current_node->next;
        }
    }
    Node* get_student_details(int roll_number) {
    Node* current_node = this->head;
    while (current_node != nullptr) {
        if (current_node->roll_number == roll_number) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return nullptr;
}

void modify_attendance(int roll_number, string subject, string date) {
    Node* student = get_student_details(roll_number);
    if (student == nullptr) {
        cout << "Student not found." << endl;
    } else {
        if (student->attendance.find(subject) != student->attendance.end() && 
            student->attendance[subject].find(date) != student->attendance[subject].end()) {
            string attendance_status;
            cout << "Is " << student->name << " present in " << subject << " on " << date << "? (Y/N)";
            cin >> attendance_status;

            if (attendance_status == "Y" || attendance_status == "y") {
                student->attendance[subject][date] = true;
            } else {
                student->attendance[subject][date] = false;
            }
        } else {
            cout << "Attendance for the given subject and date is not available." <<endl;
        }
    }
}
void modify_student_attendance(int roll_number) {
    Node* student = get_student_details(roll_number);
    if (student == nullptr) {
        cout << "Student not found." << endl;
    } else {
        cout << "1. Modify attendance for all subjects" << endl;
        cout << "2. Modify attendance for a specific subject" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            for (auto const& subject : student->attendance) {
                string date;
                cout << "Enter the date for which you want to modify attendance (dd-mm-yyyy): ";
                cin >> date;

                if (student->attendance[subject.first].find(date) == student->attendance[subject.first].end()) {
                    cout << "Attendance for the given date is not available." << endl;
                } else {
                    modify_attendance(roll_number, subject.first, date);
                }
            }
        } else if (choice == 2) {
            string subject, date;
            cout << "Enter the subject for which you want to modify attendance: ";
            cin >> subject;
            cout << "Enter the date for which you want to modify attendance (dd-mm-yyyy): ";
            cin >> date;

            if (student->attendance.find(subject) == student->attendance.end()) {
                cout << "Attendance for the given subject is not available." << endl;
            } else if (student->attendance[subject].find(date) == student->attendance[subject].end()) {
                cout << "Attendance for the given date is not available." <<endl;
            } else {
                modify_attendance(roll_number, subject, date);
            }
        } else {
            cout << "Invalid choice." <<endl;
        }
    }
}
void get_attendance_percentage(int roll_number) {
    Node* student = get_student_details(roll_number);
    if (student == nullptr) {
        cout << "Student not found." <<endl;
        return;
    }

    int total_classes = 0;
    int present_classes = 0;

    for (auto const& subject : student->attendance) {
        for (auto const& date_status : subject.second) {
            total_classes += 1;
            if (date_status.second) {
                present_classes += 1;
            }
        }
    }

    if (total_classes == 0) {
        cout << "No attendance data available for the student." << endl;
    } else {
        double attendance_percentage = (double(present_classes) / total_classes) * 100;
        cout << student->name << "'s attendance percentage is: " << attendance_percentage << "%" <<endl;
    }
}
void print_attendance() {
    Node* current_node = this->head;
    while (current_node != nullptr) {
        int total_classes = 0;
        int present_classes = 0;

        for (auto const& subject : current_node->attendance) {
            for (auto const& date_status : subject.second) {
                total_classes += 1;
                if (date_status.second) {
                    present_classes += 1;
                }
            }
        }

        if (total_classes == 0) {
            cout << current_node->name << ": No attendance data available for the student." << endl;
        } else {
            double attendance_percentage = (double(present_classes) / total_classes) * 100;
            cout << current_node->name << "'s attendance percentage is: " << attendance_percentage << "%" << endl;
        }

        current_node = current_node->next;
    }
}
void delete_student(int roll_number) {
    Node* current_node = this->head;
    while (current_node != nullptr) {
        if (current_node->roll_number == roll_number) {

            if (current_node == this->head) {
                this->head = current_node->next;
            }

            if (current_node->next != nullptr) {
                current_node->next->prev = current_node->prev;
            }

            if (current_node->prev != nullptr) {
                current_node->prev->next = current_node->next;
            }
            delete current_node;
            cout << "Student with roll number " << roll_number << " has been deleted." <<endl;
            return;
        }
        current_node = current_node->next;
    }
    cout << "Student not found." << endl;
}


};


int main() {
    DoublyLinkedList dll;
    cout << "Welcome to the Attendance Management System!" << endl;
    while (true) {
        cout << "\nPlease select an option from the menu below:" << endl;
        cout << "1. Add a new student" << endl;
        cout << "2. Take attendance" << endl;
        cout << "3. Modify attendance for a student" << endl;
        cout << "4. Print the attendance of all the students" << endl;
        cout << "5. Print the attendance of a particular student" << endl;
        cout << "6. Delete a student." << endl;
        cout << "7. exit" << endl;


        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int roll_number;
            cout << "\nEnter the name of the student: ";
            cin >> name;
            cout << "Enter the roll number of the student: ";
            cin >> roll_number;

            dll.add_student(name, roll_number);
            cout << "\nStudent added successfully!" << std::endl;
        } else if (choice == 2) {
            string subject;
            cout << "\nEnter the subject for which you want to take attendance: ";
            cin >> subject;

            dll.take_attendance(subject);
            cout << "\nAttendance taken successfully!" << std::endl;
        } else if (choice == 3) {
            int roll_number;
            cout << "\nEnter the roll number of the student: ";
            cin >> roll_number;

            dll.modify_student_attendance(roll_number);
        } else if (choice == 4) {
            dll.print_attendance();
        } else if (choice == 5) {
            int roll_number;
            cout << "Enter the roll number of the student: ";
            cin >> roll_number;

            dll.get_attendance_percentage(roll_number);


            dll.get_student_details(roll_number);
        } else if (choice == 7) {
            cout << "\nThank you for using the Attendance Management System!" << endl;
            break;
        }
        else if (choice == 6) {
    int roll_number;
    std::cout << "Enter the roll number of the student: ";
    std::cin >> roll_number;

    dll.delete_student(roll_number);
}
         else {
            cout << "\nInvalid choice. Please try again." << endl;
        }
    }

    return 0;
}
