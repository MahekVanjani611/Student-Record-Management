#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define a class for Student Information
class StudentInformation {
private:
    string studentName;
    string rollNumber;

public:
    // Getter for student name
    string get_studentName() const {
        return studentName;
    }

    // Setter for student name
    void set_studentName(const string& name) {
        studentName = name;
    }

    // Getter for roll number
    string get_rollNumber() const {
        return rollNumber;
    }

    // Setter for roll number
    void set_rollNumber(const string& roll) {
        rollNumber = roll;
    }
};

// Define a class for Student Record, inheriting from Student Information
class StudentRecord : public StudentInformation {};

// Define a class for a Node
class Node {
private:
    Node* next;
    StudentRecord* element;

public:
    // Getter for the next node
    Node* get_next() const {
        return next;
    }

    // Getter for the element (Student Record)
    StudentRecord* get_element() const {
        return element;
    }

    // Setter for the next node
    void set_next(Node* value) {
        next = value;
    }

    // Setter for the element (Student Record)
    void set_element(StudentRecord* student) {
        element = student;
    }
};

// Define a class for Entity
class Entity {
private:
    string name;
    Node* iterator = nullptr;

public:
    // Getter for entity name
    string get_name() const {
        return name;
    }

    // Setter for entity name
    void set_name(const string& Name) {
        name = Name;
    }

    // Getter for the iterator node
    Node* get_iterator() const {
        return iterator;
    }

    // Setter for the iterator node
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};

// Define a vector to store Student Information
vector<StudentInformation> students;

// Define a class for Linked List, inheriting from Entity
class LinkedList : public Entity {
public:
    // Add a student to the linked list
    void add_student(const StudentInformation& student) {
        StudentRecord* stud = new StudentRecord();
        stud->set_studentName(student.get_studentName());
        stud->set_rollNumber(student.get_rollNumber());
        Node* newnode = new Node();
        newnode->set_element(stud);
        newnode->set_next(nullptr);
        if (get_iterator() == nullptr) {
            set_iterator(newnode);
        } else {
            newnode->set_next(get_iterator());
            set_iterator(newnode);
        }
    }

    // Delete a student from the linked list by name
    void delete_student(const string& name) {
        Node* current = get_iterator();
        while (current->get_next() != nullptr && current->get_next()->get_element()->get_studentName() != name) {
            current = current->get_next();
        }
        Node* del = current->get_next();
        current->set_next(del->get_next());
        delete del;
    }
};

// Define a vector to store Entity objects
vector<LinkedList> EntityArray;

// Function to remove square brackets from a string
string removeBrackets(const string& str) {
    string result = str;
    result.erase(remove(result.begin(), result.end(), '['), result.end());
    result.erase(remove(result.begin(), result.end(), ']'), result.end());
    return result;
}

// Function to read input from a file and populate data structures
void read_input_file(const string& file_path) {
    ifstream inputFile(file_path);
    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    string line;
    int k = 0;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string str;
        vector<string> arr;
        while (getline(ss, str, ',')) {
            arr.push_back(str);
        }
        for (string& value : arr) {
            value = removeBrackets(value);
        }

        StudentInformation student;
        student.set_studentName(arr[0]);
        student.set_rollNumber(arr[1]);
        students.push_back(student);

        for (size_t i = 2; i < arr.size(); i++) {
            bool found = false;
            for (size_t j = 0; j < EntityArray.size(); j++) {
                if (EntityArray[j].get_name() == arr[i]) {
                    EntityArray[j].add_student(students[k]);
                    found = true;
                    break;
                }
            }

            if (!found) {
                LinkedList newEntity;
                newEntity.set_name(arr[i]);
                EntityArray.push_back(newEntity);
                EntityArray.back().add_student(students[k]);
            }
        }
        k++;
    }

    inputFile.close();
}

