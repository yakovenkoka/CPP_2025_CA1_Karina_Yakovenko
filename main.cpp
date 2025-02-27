#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

struct Phone {
    string brand;
    string model;
    int releaseYear;
    float price;
    float screenSize;
};

void displayPhone(const Phone& p) {
    cout << left
    << setw(15) << p.brand
    << setw(35) << p.model
    << setw(15) << p.releaseYear
    << setw(15) << fixed << setprecision(2) << p.price
    << setw(10) << fixed << setprecision(1) << p.screenSize
    << endl;
}

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

// Search for a phone by model
int searchPhoneByModel(const vector<Phone>& phones, const string& model) {
    for (int i = 0; i < phones.size(); i++) {
        if (phones[i].model == model) {
            return i;
        }
    }
    return -1;
}

// Function to count the number of phones of each brand
map<string, int> countPhonesByBrand(const vector<Phone>& phones) {
    map<string, int> count;
    for (const Phone& p : phones) {
        count[p.brand]++;
    }
    return count;
}

// Function to display phones of a particular brand
void displayPhonesByBrand(const vector<Phone>& phones, const string& brand) {
    bool found = false;
    cout << "Phones of brand: " << brand << endl;
    cout << left
    << setw(15) << "Brand"
    << setw(35) << "Model"
    << setw(15) << "Release Year"
    << setw(15) << "Price"
    << setw(10) << "Screen Size"
    << endl;

    for (const Phone& p : phones) {
        if (p.brand == brand) {
            displayPhone(p);
            found = true;
        }
    }
    if (!found) {
        cout << "No phones found for brand: " << brand << endl;
    }
}

int main() {
    vector<Phone> phones;
    loadPhones("MOCK_DATA.csv", phones);
    displayAllPhones(phones);

    // Search for a phone by model
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

    // Count the number of phones of each brand
    map<string, int> count = countPhonesByBrand(phones);
    cout << "\n----Count of phones by brand----" << endl;
    for (const auto& brandCount : count) {
        cout << brandCount.first << ": " << brandCount.second << endl;
    }

    // Display phones of a particular brand
    string filterBrand;
    cout << "\nEnter brand to filter: ";
    getline(cin, filterBrand);
    displayPhonesByBrand(phones, filterBrand);


    return 0;
}