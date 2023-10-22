#include<iostream>
#include <vector>
using namespace std;
class TreeNode {
public:
    string carNumber;
    vector<string> violations;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string number, string violation) {
        carNumber = number;
        violations.push_back(violation);
        left = right = nullptr;
    }
};

class DAIDatabase {
private:
    TreeNode* root;

public:
    DAIDatabase() {
        root = nullptr;
    }

    void insert(string carNumber, string violation) {
        root = insertRec(root, carNumber, violation);
    }

    TreeNode* insertRec(TreeNode* node, string carNumber, string violation) {
        if (node == nullptr) {
            return new TreeNode(carNumber, violation);
        }

        if (carNumber < node->carNumber) {
            node->left = insertRec(node->left, carNumber, violation);
        }
        else if (carNumber > node->carNumber) {
            node->right = insertRec(node->right, carNumber, violation);
        }
        else {
            node->violations.push_back(violation);
        }

        return node;
    }

    void printAll() {
        printInOrder(root);
    }

    void printInOrder(TreeNode* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << "Car Number: " << node->carNumber << endl;
            cout << "Violations:" << endl;
            for (const string& violation : node->violations) {
                cout << "  - " << violation << endl;
            }
            printInOrder(node->right);
        }
    }

    void printByCarNumber(string carNumber) {
        printViolationsByNumber(root, carNumber);
    }

    void printViolationsByNumber(TreeNode* node, string carNumber) {
        if (node == nullptr) {
            cout << "Car Number " << carNumber << " not found." << endl;
            return;
        }

        if (carNumber < node->carNumber) {
            printViolationsByNumber(node->left, carNumber);
        }
        else if (carNumber > node->carNumber) {
            printViolationsByNumber(node->right, carNumber);
        }
        else {
            cout << "Car Number: " << node->carNumber << endl;
            cout << "Violations:" << endl;
            for (const string& violation : node->violations) {
                cout << "  - " << violation << endl;
            }
        }
    }
};

int main() {
    DAIDatabase database;

    database.insert("ABC123", "Speeding");
    database.insert("XYZ789", "Parking violation");
    database.insert("DEF456", "Running red light");
    database.insert("ABC123", "Parking violation");

    cout << "Print all data:" << endl;
    database.printAll();

    cout << "Print data for car ABC123:" << endl;
    database.printByCarNumber("ABC123");

    cout << "Print data for car XYZ789:" << endl;
    database.printByCarNumber("XYZ789");

    cout << "Print data for car UVW123:" << endl;
    database.printByCarNumber("UVW123");

    return 0;
}

