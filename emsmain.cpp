#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>

class Employee {
public:
    int employeeID;
    std::string name;
    std::string position;
    double salary;

    Employee(int id, const std::string& n, const std::string& pos, double sal)
        : employeeID(id), name(n), position(pos), salary(sal) {}

    void display() const {
        std::cout << "Employee ID: " << employeeID << "\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Position: " << position << "\n";
        std::cout << "Salary: " << salary << "\n";
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "Employee ID: " << employeeID << "\n";
        ss << "Name: " << name << "\n";
        ss << "Position: " << position << "\n";
        ss << "Salary: " << salary << "\n";
        return ss.str();
    }
};

class EmployeeManagementSystem {
private:
    std::vector<Employee> employees;
    int nextEmployeeID = 1001; // Track the next available employee ID

public:
    void run() {
        int choice;
        while (true) {
            displayMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore(); // Consume newline character

            switch (choice) {
                case 1:
                    addEmployee();
                    break;
                case 2:
                    listEmployees();
                    break;
                case 3:
                    updateEmployee();
                    break;
                case 4:
                    deleteEmployee();
                    break;
                case 5:
                    viewEmployee();
                    break;
                case 6:
                    downloadEmployeeList();
                    break;
                case 7:
                    exit(0);
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

private:
    void displayMenu() {
        std::cout << "Employee Management System Menu:\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. List Employees\n";
        std::cout << "3. Update Employee\n";
        std::cout << "4. Delete Employee\n";
        std::cout << "5. View Employee\n";
        std::cout << "6. Download Employee List\n";
        std::cout << "7. Exit\n";
    }

    void addEmployee() {
        int id = nextEmployeeID++;
        std::string name, position;
        double salary;

        std::cin.ignore(); // Consume newline character
        std::cout << "Enter Name: ";
        std::getline(std::cin, name);

        std::cout << "Enter Position: ";
        std::getline(std::cin, position);

        std::cout << "Enter Salary: ";
        std::cin >> salary;

        employees.push_back(Employee(id, name, position, salary));
        std::cout << "Employee added successfully!\n";
    }

    void listEmployees() {
        std::cout << "Employee List:\n";
        for (const Employee& emp : employees) {
            std::cout << emp.toString() << "\n";
        }
    }

    void updateEmployee() {
        int id;
        std::cout << "Enter Employee ID to update: ";
        std::cin >> id;

        auto it = std::find_if(employees.begin(), employees.end(),
            [id](const Employee& emp) { return emp.employeeID == id; });

        if (it != employees.end()) {
            std::cin.ignore(); // Consume newline character
            std::string name, position;
            double salary;

            std::cout << "Enter New Name: ";
            std::getline(std::cin, name);

            std::cout << "Enter New Position: ";
            std::getline(std::cin, position);

            std::cout << "Enter New Salary: ";
            std::cin >> salary;

            it->name = name;
            it->position = position;
            it->salary = salary;

            std::cout << "Employee information updated successfully!\n";
        } else {
            std::cout << "Employee with ID " << id << " not found.\n";
        }
    }

    void deleteEmployee() {
        int id;
        std::cout << "Enter Employee ID to delete: ";
        std::cin >> id;

        auto it = std::remove_if(employees.begin(), employees.end(),
            [id](const Employee& emp) { return emp.employeeID == id; });

        if (it != employees.end()) {
            employees.erase(it, employees.end());
            std::cout << "Employee deleted successfully!\n";
        } else {
            std::cout << "Employee with ID " << id << " not found.\n";
        }
    }

    void viewEmployee() {
        int id;
        std::cout << "Enter Employee ID to view: ";
        std::cin >> id;

        auto it = std::find_if(employees.begin(), employees.end(),
            [id](const Employee& emp) { return emp.employeeID == id; });

        if (it != employees.end()) {
            std::cout << "Employee Details:\n";
            std::cout << it->toString() << "\n";
        } else {
            std::cout << "Employee with ID " << id << " not found.\n";
        }
    }

    void downloadEmployeeList() {
        std::ofstream outputFile("employee_list.txt");
        if (!outputFile) {
            std::cerr << "Error opening file for writing.\n";
            return;
        }

        outputFile << "Employee List:\n";
        for (const Employee& emp : employees) {
            outputFile << emp.toString() << "\n";
        }

        outputFile.close();
        std::cout << "Employee list downloaded to employee_list.txt\n";
    }
};

int main() {
    std::cout<<"EMPLOYEE ID STARTS WITH 1001\n";
    EmployeeManagementSystem ems;
    ems.run();
    return 0;
}
