#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Function to split a line into cells while respecting quoted fields
vector<string> parseCSVLine(const string& line) {
    vector<string> result;
    stringstream ss(line);
    string cell;
    bool insideQuotes = false;
    string temp;

    for (char ch : line) {
        if (ch == '"') {
            insideQuotes = !insideQuotes;
        } else if (ch == ',' && !insideQuotes) {
            result.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    result.push_back(temp); // Add the last cell
    return result;
}

int main() {
    std::ifstream file("C:\\Users\\angel\\Downloads\\archive (1)\\recipes.csv"); // Replace with your file path
    std::string line;
    std::vector<std::vector<std::string>> data;
    //int count = 0;

    if (file.is_open()) {
        cout << "yippie" << endl;

        // Read the header line
        if (std::getline(file, line)) {
            data.push_back(parseCSVLine(line));
        }

        // Read the rest of the lines
        while (std::getline(file, line, '{')) {
            data.push_back(parseCSVLine(line));
//            if (count > 100000){
//                break;
//            }
//            count++;
        }

        // Print the data
        for (int i = 1; i < 3; i++) {
            for (int j = 0; j < data[i].size(); j++) {
                cout << i << "count" << endl;
                cout << data[0][j] << ": " << data[i][j] << endl; // Use '|' as a separator for clarity
            }
            cout << endl;
        }
    } else {
        cout << "booo" << endl;
    }

    return 0;
}

