#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

// Structure to store employee details
struct Employee {
    int id;
    string name;
    string department;
    double basicSalary;
    int leavesTaken;
    double taxRate;
    double bonus;

    // Calculate Net Salary
    double calculateNetSalary() {
        double deductions = (basicSalary * taxRate / 100) + (leavesTaken * (basicSalary / 30));
        return basicSalary + bonus - deductions;
    }
};

// Function Prototypes
void addEmployee(vector<Employee>& employees);
void displayEmployees(const vector<Employee>& employees);
void generatePayslip(const vector<Employee>& employees);
void saveData(const vector<Employee>& employees);
void loadData(vector<Employee>& employees);

int main() {
    vector<Employee> employees;
    loadData(employees);

    int choice;
    do {
        cout << "\n=== Payroll Management System ===\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Generate Payslip\n";
        cout << "4. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(employees);
                break;
            case 2:
                displayEmployees(employees);
                break;
            case 3:
                generatePayslip(employees);
                break;
            case 4:
                saveData(employees);
                cout << "Data saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

// Add a new employee
void addEmployee(vector<Employee>& employees) {
    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.id;
    cin.ignore(); // Ignore newline
    cout << "Enter Name: ";
    getline(cin, emp.name);
    cout << "Enter Department: ";
    cin >> emp.department;
    cout << "Enter Basic Salary: ";
    cin >> emp.basicSalary;
    cout << "Enter Leaves Taken: ";
    cin >> emp.leavesTaken;
    cout << "Enter Tax Rate (%): ";
    cin >> emp.taxRate;
    cout << "Enter Bonus: ";
    cin >> emp.bonus;

    employees.push_back(emp);
    cout << "Employee added successfully!\n";
}

// Display all employees
void displayEmployees(const vector<Employee>& employees) {
    cout << "\n=== Employee List ===\n";
    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Department" 
         << setw(10) << "Salary" << "\n";
    for (const auto& emp : employees) {
        cout << setw(5) << emp.id << setw(15) << emp.name << setw(15) << emp.department 
             << setw(10) << fixed << setprecision(2) << emp.basicSalary << "\n";
    }
}

// Generate payslip for an employee
void generatePayslip(const vector<Employee>& employees) {
    int id;
    cout << "Enter Employee ID for Payslip: ";
    cin >> id;

    for (const auto& emp : employees) {
        if (emp.id == id) {
            cout << "\n=== Payslip ===\n";
            cout << "Employee ID: " << emp.id << "\n";
            cout << "Name: " << emp.name << "\n";
            cout << "Department: " << emp.department << "\n";
            cout << "Basic Salary: $" << fixed << setprecision(2) << emp.basicSalary << "\n";
            cout << "Leaves Taken: " << emp.leavesTaken << "\n";
            cout << "Bonus: $" << emp.bonus << "\n";
            cout << "Tax Rate: " << emp.taxRate << "%\n";
            cout << "Net Salary: $" << emp.calculateNetSalary() << "\n";
            return;
        }
    }
    cout << "Employee ID not found.\n";
}

// Save data to file
void saveData(const vector<Employee>& employees) {
    ofstream outFile("employees.txt");
    for (const auto& emp : employees) {
        outFile << emp.id << "|" << emp.name << "|" << emp.department << "|"
                << emp.basicSalary << "|" << emp.leavesTaken << "|"
                << emp.taxRate << "|" << emp.bonus << "\n";
    }
    outFile.close();
}

// Load data from file
void loadData(vector<Employee>& employees) {
    ifstream inFile("employees.txt");
    if (!inFile) {
        cout << "No previous data found.\n";
        return;
    }
    Employee emp;
    while (inFile >> emp.id) {
        inFile.ignore(); // Ignore delimiter
        getline(inFile, emp.name, '|');
        getline(inFile, emp.department, '|');
        inFile >> emp.basicSalary >> emp.leavesTaken >> emp.taxRate >> emp.bonus;
        employees.push_back(emp);
    }
    inFile.close();
}
