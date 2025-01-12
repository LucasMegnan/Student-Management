#include "include.h"

// Function to display the menu
void showMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add Student\n";
    std::cout << "2. View Student\n";
    std::cout << "3. Update Student\n";
    std::cout << "4. Remove Student\n";
    std::cout << "5. Sort Students by Enrollment Year\n";
    std::cout << "6. Exit\n";
}

// Function to add a student
void addStudent(BST& tree, const student& s) {
    tree.insert(s);
}

// Function to get a student by ID
student* getStudent(BST& tree, int studentID) {
    Node* result = tree.search(studentID);
    if (result != nullptr) {
        return &result->data;
    }
    return nullptr;
}

// Function to update a student's information
void updateStudent(BST& tree, int studentID, const student& updatedStudent) {
    Node* result = tree.search(studentID);
    if (result != nullptr) {
        result->data = updatedStudent;
    }
}

// Function to remove a student (this is a placeholder)
void removeStudent(BST& tree, int studentID) {
    // This requires implementing a deletion algorithm in the BST, which is a bit more complex.
    std::cout << "Remove student functionality is not yet implemented.\n";
}

// Main function with a simple menu
int main() {
    BST studentTree;
    int choice;
    do {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            // Adding a student
            student s;
            std::cout << "Enter student ID: ";
            std::cin >> s.student_id;
            std::cout << "Enter student's first name: ";
            std::cin >> s.student_name;
            std::cout << "Enter student's surname: ";
            std::cin >> s.student_surname;
            std::cout << "Enter student's age: ";
            std::cin >> s.student_age;

            int n_years;
            std::cout << "Enter the number of enrollment years: ";
            std::cin >> n_years;
            for (int i = 0; i < n_years; ++i) {
                int year;
                std::cout << "Enter enrollment year " << i + 1 << ": ";
                std::cin >> year;
                s.enrollment_year.push_back(year);
            }

            int n_warnings;
            std::cout << "Enter the number of warnings: ";
            std::cin >> n_warnings;
            for (int i = 0; i < n_warnings; ++i) {
                warning w;
                std::cout << "Enter warning reason: ";
                std::cin.ignore();
                std::getline(std::cin, w.reason);
                w.date = std::time(0);  // Set the warning date to the current time
                s.student_warning.push_back(w);
            }

            addStudent(studentTree, s);
            std::cout << "Student added successfully.\n";

        } else if (choice == 2) {
            // Viewing a student
            int studentID;
            std::cout << "Enter student ID to view: ";
            std::cin >> studentID;
            student* s = getStudent(studentTree, studentID);
            if (s != nullptr) {
                std::cout << "Student ID: " << s->student_id << "\n";
                std::cout << "Name: " << s->student_name << " " << s->student_surname << "\n";
                std::cout << "Age: " << s->student_age << "\n";
                std::cout << "Enrollment Years: ";
                for (const auto& year : s->enrollment_year) {
                    std::cout << year << " ";
                }
                std::cout << "\nWarnings: \n";
                for (const auto& warn : s->student_warning) {
                    std::cout << "Date: " << std::ctime(&warn.date) << " Reason: " << warn.reason << "\n";
                }
            } else {
                std::cout << "Student not found.\n";
            }

        } else if (choice == 3) {
            // Updating a student's information
            int studentID;
            std::cout << "Enter student ID to update: ";
            std::cin >> studentID;
            student* s = getStudent(studentTree, studentID);
            if (s != nullptr) {
                std::string name, surname;
                int age;
                std::cout << "Enter new name: ";
                std::cin >> name;
                std::cout << "Enter new surname: ";
                std::cin >> surname;
                std::cout << "Enter new age: ";
                std::cin >> age;

                s->student_name = name;
                s->student_surname = surname;
                s->student_age = age;

                std::cout << "Student updated successfully.\n";
            } else {
                std::cout << "Student not found.\n";
            }

        } else if (choice == 4) {
            // Removing a student (not yet implemented)
            int studentID;
            std::cout << "Enter student ID to remove: ";
            std::cin >> studentID;
            removeStudent(studentTree, studentID);

        } else if (choice == 5) {
            // Sorting the students by enrollment year
            studentTree.mergeSort();
            std::cout << "Students sorted by enrollment year.\n";

        } else if (choice == 6) {
            std::cout << "Exiting the program...\n";
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}