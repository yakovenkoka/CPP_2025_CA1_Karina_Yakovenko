#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <limits.h>
#include <list>
#include <algorithm>

using namespace std;

// Structure to store phone data
struct Phone {
    string brand;
    string model;
    int releaseYear;
    float price;
    float screenSize;
};

// Function to display a single phon's data in a formatted way
void displayPhone(const Phone& p) {
    cout << left
    << setw(15) << p.brand
    << setw(35) << p.model
    << setw(15) << p.releaseYear
    << setw(15) << fixed << setprecision(2) << p.price
    << setw(10) << fixed << setprecision(2) << p.screenSize
    << endl;
}

// Function to parse a line of csv data and store it in a Phone object
void parsePhone(const string& line, Phone& p) {
    stringstream ss(line);
    string temp;

    getline(ss, p.brand, ',');
    getline(ss, p.model, ',');
    getline(ss, temp, ',');
    p.releaseYear = stoi(temp);
    getline(ss, temp, ',');
    p.price = stof(temp);
    getline(ss, temp, ',');
    p.screenSize = stof(temp);
}

// Function to load phone data from a csv file and store it in a vector of Phone objects
void loadPhones(const string &filename, vector<Phone>& phones) {
    ifstream fin(filename);
    if(fin){
        string line;
        while(getline(fin, line)) {
            Phone p;
            parsePhone(line, p);
            phones.push_back(p);
        }
        fin.close();
    }
    else {
        cout << "Error opening file" << endl;
    }
}

// Function to display all phones from the vector with a formatted header
void displayAllPhones(const vector<Phone>& phones) {
    cout << left
    << setw(15) << "Brand"
    << setw(35) << "Model"
    << setw(15) << "Release Year"
    << setw(15) << "Price"
    << setw(10) << "Screen Size"
    << endl;

    for (const Phone& p : phones) {
        displayPhone(p);
    }
}

// Function to search for a phone by model and return its index in the vector
// Returns -1 if not found 
int searchPhoneByModel(const vector<Phone>& phones, const string& model) {
    for (int i = 0; i < phones.size(); i++) {
        if (phones[i].model == model) {
            return i;
        }
    }
    return -1;
}

// Function to count the number of phones of each brand
// Returns a map with brand as key and the number of phones with that brand as value
map<string, int> countPhonesByBrand(const vector<Phone>& phones) {
    map<string, int> count;
    for (const Phone& p : phones) {
        count[p.brand]++;
    }
    return count;
}

// Function to display phones of a particular brand
void displayPhonesByBrand(const vector<Phone>& phones, const string& brand) {
    vector<Phone> filteredPhones;
    for (const Phone& p : phones) {
        if (p.brand == brand) {
            filteredPhones.push_back(p);
        }
    }

    if (filteredPhones.empty()) {
        cout << "No phones found for brand: " << brand << endl;
    } else {
        cout << "\n----Phones of brand " << brand << "----" << endl;
        cout << left
        << setw(15) << "Brand"
        << setw(35) << "Model"
        << setw(15) << "Release Year"
        << setw(15) << "Price"
        << setw(10) << "Screen Size"
        << endl;

        for (const Phone& p : filteredPhones) {
            displayPhone(p);
        }
    }
}

//Function to find the highest and lowest release year and to calculate the average release year
//returns the average release year as an integer
int findMaxMinAvgReleaseYear(const vector<Phone>& phones, Phone& max, Phone& min) {
    int sum = 0;
    int maxReleaseYear = INT_MIN;
    int minReleaseYear = INT_MAX;

    for (const Phone& p : phones) {
        sum += p.releaseYear;

        if (p.releaseYear > maxReleaseYear) {
            maxReleaseYear = p.releaseYear;
            max = p;
        }
        if (p.releaseYear < minReleaseYear) {
            minReleaseYear = p.releaseYear;
            min = p;
        }
    }
    return sum / phones.size();
}

//Function to search for phones where the model contains a partial text and return a list of matching phones 
list<Phone> searchPhoneByPartialText(const vector<Phone>& phones, const string& text) {
    list<Phone> matchingPhones;
    for(auto it = phones.begin(); it != phones.end(); it++) {
        //string::npos is returned if the text is not found in the model
        if (it->model.find(text) != string::npos) {
            matchingPhones.push_back(*it);
        }
    }
    return matchingPhones;
}

//Function to display phones in descending order of price
void displayPhonesInDescendingOrder(const vector<Phone>& phones){
    vector<Phone> sortedPhones = phones;
    sort(sortedPhones.begin(), sortedPhones.end(), [](const Phone& p1, const Phone& p2) {
        return p1.price > p2.price;
    });

    cout << "\n----Phones in descending order of price----" << endl;
    cout << left
    << setw(15) << "Brand"
    << setw(35) << "Model"
    << setw(15) << "Release Year"
    << setw(15) << "Price"
    << setw(10) << "Screen Size"
    << endl;

    for (const Phone& p : sortedPhones) {
        displayPhone(p);
    }
}

// Function to display the menu
void displayMenu() {
    cout << "\n----Menu----" << endl;
    cout << "\n1. Display all phones" << endl;
    cout << "2. Search index of phone by model" << endl;
    cout << "3. Count the number of phones of each brand" << endl;
    cout << "4. Display phones of a particular brand" << endl;
    cout << "5. Find Highest, Lowest, and Average Release Year" << endl;
    cout << "6. Search Phones by Partial Text\n";
    cout << "7. Display Phones in Descending Order of Price\n";
    cout << "8. Exit" << endl;
}

int main() {
    vector<Phone> phones;
    loadPhones("MOCK_DATA.csv", phones);

    bool exit = false;
    while (!exit) {
        displayMenu();

        string input;
        int choice;
        cout << "\nEnter choice: ";
        getline(cin, input);
        
        try{
            //stoi converts string to integer and throws an exception if the string is not a valid integer
            choice = stoi(input);
        } catch (exception e) {
            cout << "Invalid choice" << endl;
            continue;
        }

        switch (choice) {
            // Display all phones
            case 1:
                displayAllPhones(phones);
                break;
            case 2: {
                // Search index of phone by model
                string model;
                cout << "\nEnter model to search: ";
                getline(cin, model);
                int index = searchPhoneByModel(phones, model);
                if (index != -1) {
                    cout << "Phone found for index: " << index << endl;
                    displayPhone(phones[index]);
                }
                else {
                    cout << "Phone not found" << endl;
                }
                break;
            }
            case 3: {
                // Count the number of phones of each brand
                map<string, int> count = countPhonesByBrand(phones);
                cout << "\n----Count of phones by brand----" << endl;
                for (const auto& brandCount : count) {
                    cout << brandCount.first << ": " << brandCount.second << endl;
                }
                break;
            }
            case 4: {
                // Display phones of a particular brand
                string filterBrand;
                cout << "\nEnter brand to filter: ";
                getline(cin, filterBrand);
                displayPhonesByBrand(phones, filterBrand);
                break;
            }
            case 5: {
                // Find Highest, Lowest, and Average Release Year
                Phone max, min;
                int avgReleaseYear = findMaxMinAvgReleaseYear(phones, max, min);
                cout << "\nAverage release year: " << avgReleaseYear << endl;
                cout << "Phone with highest release year: \t";
                displayPhone(max);
                cout << "Phone with lowest release year: \t";
                displayPhone(min);
                break;
            }
            case 6: {
                // Search Phones by Partial Text
                string text;
                cout << "\nEnter text to search in model: ";
                getline(cin, text);
                list<Phone> matchingPhones = searchPhoneByPartialText(phones, text);

                if(matchingPhones.empty()) {
                    cout << "No phones found" << endl;
                    break;
                }

                cout << "\n----Phones matching text----" << endl;
                cout << left
                << setw(15) << "Brand"
                << setw(35) << "Model"
                << setw(15) << "Release Year"
                << setw(15) << "Price"
                << setw(10) << "Screen Size"
                << endl;

                for (const Phone& p : matchingPhones) {
                    displayPhone(p);
                }
                break;
            }
            case 7: {
                // Display Phones in Descending Order of Price
                displayPhonesInDescendingOrder(phones);
                break;
            }
            case 8:
                exit = true;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    }

    return 0;
}