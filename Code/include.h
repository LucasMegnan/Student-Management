#include <iostream>
#include <string>
#include <vector>
#include <ctime>

// Define the Warning struct for student warnings
struct warning {
    std::time_t date;  // Time of the warning
    std::string reason;  // Reason for the warning
};

// Define the Student struct with the attributes you provided
struct student {
    int student_id;
    std::string student_name;
    std::string student_surname;
    int student_age;
    std::vector<int> enrollment_year;  // A list of years the student was enrolled
    std::vector<warning> student_warning;  // A list of warnings the student has received
};

// Define the Node struct for the Binary Search Tree (BST)
struct Node {
    student data;
    Node* left;
    Node* right;

    Node(student data) : data(data), left(nullptr), right(nullptr) {}
};

// Define the Binary Search Tree (BST) class
class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    // Function to insert a new student
    void insert(student s) {
        root = insertRec(root, s);
    }

    // Function to search for a student by ID
    Node* search(int studentID) {
        return searchRec(root, studentID);
    }

    // Merge Sort for sorting based on enrollment year
    void mergeSort() {
        std::vector<student> students;
        inorderTraversal(root, students);
        mergeSortHelper(students, 0, students.size() - 1);
        rebuildTreeFromSortedList(students);
    }

    // Inorder traversal to collect students in a vector
    void inorderTraversal(Node* node, std::vector<student>& students) {
        if (node != nullptr) {
            inorderTraversal(node->left, students);
            students.push_back(node->data);
            inorderTraversal(node->right, students);
        }
    }

private:
    // Function to insert recursively
    Node* insertRec(Node* node, student s) {
        if (node == nullptr) return new Node(s);
        if (s.student_id < node->data.student_id) {
            node->left = insertRec(node->left, s);
        } else {
            node->right = insertRec(node->right, s);
        }
        return node;
    }

    // Function to search recursively
    Node* searchRec(Node* node, int studentID) {
        if (node == nullptr || node->data.student_id == studentID)
            return node;
        if (studentID < node->data.student_id)
            return searchRec(node->left, studentID);
        return searchRec(node->right, studentID);
    }

    // Merge Sort helper to sort a vector of students by enrollment year (based on the first enrollment year)
    void mergeSortHelper(std::vector<student>& students, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortHelper(students, left, mid);
        mergeSortHelper(students, mid + 1, right);
        merge(students, left, mid, right);
    }

    // Merge function to combine two sorted halves
    void merge(std::vector<student>& students, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<student> leftHalf(n1);
        std::vector<student> rightHalf(n2);

        for (int i = 0; i < n1; i++) leftHalf[i] = students[left + i];
        for (int i = 0; i < n2; i++) rightHalf[i] = students[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftHalf[i].enrollment_year[0] <= rightHalf[j].enrollment_year[0]) {
                students[k] = leftHalf[i];
                i++;
            } else {
                students[k] = rightHalf[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            students[k] = leftHalf[i];
            i++;
            k++;
        }

        while (j < n2) {
            students[k] = rightHalf[j];
            j++;
            k++;
        }
    }

    // Rebuild the tree from the sorted list of students
    void rebuildTreeFromSortedList(const std::vector<student>& students) {
        root = nullptr;
        for (const auto& s : students) {
            insert(s);
        }
    }
};