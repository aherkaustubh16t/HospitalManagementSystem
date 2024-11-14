#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TreeNode {
public:
    string name;
    string type;
    vector<TreeNode *> children;
    string data;

    TreeNode(string n, string t, string d = "") : name(n), type(t), data(d) {}

    void addChild(TreeNode *child) {
        children.push_back(child);
    }

    void display(int level = 0) {
        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        cout << name << " (" << type << ")" << endl;

        if (!data.empty()) {
            for (int i = 0; i < level + 1; i++) {
                cout << "  ";
            }
            cout << "Details: " << data << endl;
        }

        for (auto child : children) {
            child->display(level + 1);
        }
    }
};

class HospitalTree {
public:
    TreeNode *root;

    HospitalTree() {
        root = new TreeNode("Hospital", "root");
    }

    TreeNode *addDepartment(string departmentName) {
        TreeNode *department = new TreeNode(departmentName, "department");
        root->addChild(department);
        return department;
    }

    TreeNode *addDoctor(TreeNode *departmentNode, string doctorName, string specialization) {
        TreeNode *doctor = new TreeNode(doctorName, "doctor", specialization);
        departmentNode->addChild(doctor);
        return doctor;
    }

    void addPatient(TreeNode *doctorNode, string patientName, string patientData) {
        TreeNode *patient = new TreeNode(patientName, "patient", patientData);
        doctorNode->addChild(patient);
    }

    void display() {
        root->display();
    }
};

void showMenu() {
    cout << "\n===== Hospital Management System =====\n";
    cout << "1. Add Department\n";
    cout << "2. Add Doctor to Department\n";
    cout << "3. Add Patient to Doctor\n";
    cout << "4. Display Hospital Structure\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void addDepartment(HospitalTree &hospital) {
    string departmentName;
    cout << "Enter department name: ";
    cin.ignore();
    getline(cin, departmentName);
    hospital.addDepartment(departmentName);
    cout << "Department '" << departmentName << "' added successfully.\n";
}

void addDoctor(HospitalTree &hospital) {
    string departmentName, doctorName, specialization;
    cout << "Enter department name: ";
    cin.ignore();
    getline(cin, departmentName);

    TreeNode *department = nullptr;
    for (auto dep : hospital.root->children) {
        if (dep->name == departmentName && dep->type == "department") {
            department = dep;
            break;
        }
    }

    if (department == nullptr) {
        cout << "Department not found.\n";
        return;
    }

    cout << "Enter doctor's name: ";
    getline(cin, doctorName);
    cout << "Enter doctor's specialization: ";
    getline(cin, specialization);

    hospital.addDoctor(department, doctorName, specialization);
    cout << "Doctor '" << doctorName << "' added to department '" << departmentName << "' successfully.\n";
}

void addPatient(HospitalTree &hospital) {
    string doctorName, patientName, patientData;
    cout << "Enter doctor's name: ";
    cin.ignore();
    getline(cin, doctorName);

    TreeNode *doctor = nullptr;
    for (auto dep : hospital.root->children) {
        for (auto doc : dep->children) {
            if (doc->name == doctorName && doc->type == "doctor") {
                doctor = doc;
                break;
            }
        }
    }

    if (doctor == nullptr) {
        cout << "Doctor not found.\n";
        return;
    }

    cout << "Enter patient's name: ";
    getline(cin, patientName);
    cout << "Enter patient details (e.g., diagnosis, age, treatment): ";
    getline(cin, patientData);

    hospital.addPatient(doctor, patientName, patientData);
    cout << "Patient '" << patientName << "' added to Dr. '" << doctorName << "' successfully.\n";
}

int main() {
    HospitalTree hospital;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addDepartment(hospital);
            break;
        case 2:
            addDoctor(hospital);
            break;
        case 3:
            addPatient(hospital);
            break;
        case 4:
            hospital.display();
            break;
        case 5:
            cout << "Exiting the program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
