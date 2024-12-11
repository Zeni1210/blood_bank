#include <bits/stdc++.h>
using namespace std;

class BloodBank {
private:
    map<string, int> bloodGroups; // Map to store blood group stocks
    unordered_map<string, queue<time_t>> bloodExpirationTimes; // Track expiration of blood
    string password;              // Admin password
    string dataFileName;         // File to store the blood data

public:
    BloodBank() {
        // Initialize blood group stocks to 0
        bloodGroups["A+"] = 0;
        bloodGroups["O+"] = 0;
        bloodGroups["B+"] = 0;
        bloodGroups["AB+"] = 0;
        bloodGroups["A-"] = 0;
        bloodGroups["O-"] = 0;
        bloodGroups["B-"] = 0;
        bloodGroups["AB-"] = 0;

        password = "suraj"; // Set admin password
        dataFileName = "blood_data.txt"; // File to store the blood data
    }

    void showStock() {
        cout << "Blood Group Stock:\n";
        for (map<string, int>::iterator it = bloodGroups.begin(); it != bloodGroups.end(); ++it) {
            cout << it->first << " : " << it->second << " packets\n";
        }
    }

    void showExpiringBlood() {
        cout << "\nBlood Groups nearing expiration:\n";
        time_t currentTime = time(0);

        // Replacing range-based loop with traditional for loop
        unordered_map<string, queue<time_t>>::iterator it;
        for (it = bloodExpirationTimes.begin(); it != bloodExpirationTimes.end(); ++it) {
            string bloodGroup = it->first;
            queue<time_t>& expTimes = it->second;

            while (!expTimes.empty()) {
                time_t expirationTime = expTimes.front();
                if (difftime(currentTime, expirationTime) > 0) {
                    cout << bloodGroup << " - Expired\n";
                }
                expTimes.pop();
            }
        }
    }

    void adminPanel() {
        string inputPassword;
        int attempts = 3;
        
        while (attempts > 0) {
            cout << "Enter password: ";
            cin >> inputPassword;
            if (inputPassword == password) {
                cout << "Welcome, Admin!\n";
                showStock();
                return;
            } else {
                attempts--;
                cout << "Incorrect password! You have " << attempts << " attempt(s) left.\n";
            }
        }

        cout << "Too many incorrect attempts. Exiting.\n";
    }

    void donorPanel() {
        string name, sex, bloodGroup;
        int packets;
        cout << "Welcome Donor!\n";
        cout << "Please enter your name: ";
        cin >> name;
        cout << "Enter your sex (Male/Female): ";
        cin >> sex;
        cout << "Enter the blood group you are donating (e.g., A+, O-): ";
        cin >> bloodGroup;
        cout << "How many packets of blood are you donating: ";
        cin >> packets;

        if (bloodGroups.find(bloodGroup) != bloodGroups.end()) {
            bloodGroups[bloodGroup] += packets;
            cout << "Thank you for your donation, " << name << "!\n";
            
            // Track expiration times
            time_t expirationTime = time(0) + 60 * 60 * 24 * 30; // Expiration time set to 30 days from now
            bloodExpirationTimes[bloodGroup].push(expirationTime);
        } else {
            cout << "Invalid blood group entered.\n";
        }
    }

    void patientPanel() {
        string name, bloodGroup;
        cout << "Welcome Patient!\n";
        cout << "Please enter your name: ";
        cin >> name;
        cout << "Enter the blood group you are looking for (e.g., A+, O-): ";
        cin >> bloodGroup;

        if (bloodGroups.find(bloodGroup) != bloodGroups.end() && bloodGroups[bloodGroup] > 0) {
            bloodGroups[bloodGroup]--;
            cout << "You have been donated 1 packet of " << bloodGroup << " blood.\n";
        } else {
            cout << "Sorry, the requested blood group is unavailable.\n";
        }
    }

    void saveData() {
        ofstream outFile(dataFileName);
        if (outFile.is_open()) {
            for (map<string, int>::iterator it = bloodGroups.begin(); it != bloodGroups.end(); ++it) {
                outFile << it->first << " " << it->second << "\n";
            }
            outFile.close();
            cout << "Data saved to " << dataFileName << "\n";
        } else {
            cout << "Unable to save data.\n";
        }
    }

    void loadData() {
        ifstream inFile(dataFileName);
        string bloodGroup;
        int stock;

        if (inFile.is_open()) {
            while (inFile >> bloodGroup >> stock) {
                bloodGroups[bloodGroup] = stock;
            }
            inFile.close();
        } else {
            cout << "No saved data found. Initializing with default values.\n";
        }
    }
};

int main() {
    BloodBank bloodBank;
    bloodBank.loadData(); // Load saved data from file

    int choice;

    while (true) {
        // Display the menu with better formatting
        cout << "\n==================== Welcome to the Blood Bank ====================\n";
        cout << "1. Admin Panel\n";
        cout << "2. Donor Panel\n";
        cout << "3. Patient Panel\n";
        cout << "4. Exit\n";
        cout << "====================================================================\n";
        cout << "Please select an option (1-4): ";

        cin >> choice;

        // Process user choice
        switch (choice) {
        case 1:
            bloodBank.adminPanel(); // Admin panel
            break;
        case 2:
            bloodBank.donorPanel(); // Donor panel
            break;
        case 3:
            bloodBank.patientPanel(); // Patient panel
            break;
        case 4:
            // Show expiring blood and exit message before quitting
            bloodBank.showExpiringBlood();
            bloodBank.saveData(); // Save data before exit
            cout << "\nThank you for visiting the Blood Bank!\n";
            cout << "Goodbye!\n";
            return 0;  // Exit the program
        default:
            // Handle invalid choice
            cout << "Invalid choice! Please enter a number between 1 and 4.\n";
        }
    }
}