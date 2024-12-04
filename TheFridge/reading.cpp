
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Recipe {
    int id;
    string name;
    int total_time;
    string category;
    vector<string> ingredients;
    float rating;
    int review_count;
    float calories;
    string author;
    vector<string> steps;
    string description;
    string image;



    Recipe(int id, string name, int total_time, string category, vector<string> ingredients, float rating,
           int review_count, float calories, string author, vector<string> steps, string description, string image) {
        this->id = id;
        this->name = name;
        this->total_time = total_time;
        this->category = category;
        this->ingredients = ingredients;
        this->rating = rating;
        this->review_count = review_count;
        this->calories = calories;
        this->author = author;
        this->steps = steps;
        this->description = description;
        this->image = image;
    }
};

vector<string> splitString(string str, char delim) {
    vector<string> tokens;
    string token;
    bool insideQuotes = false;

    for (size_t i = 0; i < str.size(); ++i) {
        char ch = str[i];

        if (ch == '"') {
            insideQuotes = !insideQuotes; // Toggle insideQuotes flag
            token += ch; // Include the quote mark in the token
        } else if (ch == delim && !insideQuotes) {
            tokens.push_back(token); // Only split on delimiter outside quotes
            token.clear(); // Clear token for next field
        } else {
            token += ch; // Append character to current token
        }
    }

    if (!token.empty()) {
        tokens.push_back(token); // Add the last token
    }

    return tokens;
}



// Function to split a line into cells while respecting quoted fields
vector<Recipe> parseCSVLine(const string& filename) {
    vector<Recipe> recipes;
    ifstream file(filename);

    //checks if the file even exists and can be opened
    if (!file.is_open()) {
        cout << "Could not open file :(" << endl;
        return recipes;
    }
    //reads the header
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string idstr, name, authoridstr, author_name, cook_timestr,
        prep_timestr, total_timestr, date_published, description, image,
        category, keywords, ingredient_quantities, ingredients, ratingsstr, review_countstr,
        caloriesstr, fatcontentstr, saturatedfatstr, cholesterolstr, carbsstr, fiberstr,
        sugarstr, proteinstr, servingsstr, yeild, instructions;

        try {
            getline(ss, idstr, ',');
            getline(ss, name, ',');
            getline(ss, authoridstr, ',');
            getline(ss, author_name, ',');
            getline(ss, cook_timestr, ',');
            getline(ss, prep_timestr, ',');
            getline(ss, total_timestr, ',');
            getline(ss, date_published, ',');
            getline(ss, description, ',');
            getline(ss, image, ','); //use split string to make vector
            getline(ss, category, ',');
            getline(ss, keywords, ','); // same here
            getline(ss, ingredient_quantities, ','); //and here
            getline(ss, ingredients, ',');
            getline(ss, ratingsstr, ',');
            getline(ss, review_countstr, ',');
            getline(ss, caloriesstr, ',');
            getline(ss, fatcontentstr, ',');
            getline(ss, saturatedfatstr, ',');
            getline(ss, cholesterolstr, ',');
            getline(ss, carbsstr, ',');
            getline(ss, fiberstr, ',');
            getline(ss, sugarstr, ',');
            getline(ss, proteinstr, ',');
            getline(ss, servingsstr, ',');
            getline(ss, yeild, ',');
            getline(ss, instructions);
        }
        catch (invalid_argument& e) {
            continue;
        }


        /*cout << idstr << " " << name << " " << authoridstr << " " << author_name << " " << endl;
        cout << cook_timestr << " " << prep_timestr << " " << total_timestr << " " << date_published << endl;
        cout << description << " " << image << " " << category << " " << keywords << " " << ingredient_quantities << endl;
        cout << ingredients << " " << ratingsstr << " " << review_countstr << " " << caloriesstr << " " << endl;
        cout << fatcontentstr << " " << saturatedfatstr << " " << cholesterolstr << " " << carbsstr << " " << fiberstr << endl;
        cout << sugarstr << " " << proteinstr << " " << servingsstr << " " << yeild << " " << instructions << endl;*/

        cout << idstr << endl;



        //handle total_cooktime
        if (total_timestr[0] == 'P') {
            total_timestr = total_timestr.substr(2);
        }
        int hour_ind = total_timestr.find('H');
        int mins = 0;
        if (hour_ind != string::npos) {
            int length_to_go = hour_ind - 1;
            int hours;
            try {
                hours = stoi(total_timestr.substr(0, 1));
            }
            catch (invalid_argument &e) {
                hours = 0;
            }
            mins += 60*hours;
            total_timestr = total_timestr.substr(hour_ind + 1);
        }
        try {
            mins += stoi(total_timestr.substr(0, total_timestr.length() - 1));
        }
        catch (invalid_argument &e) {
            //cout << "no" << endl;
            mins = 0;
        }
        catch (out_of_range &e) {
            //cout << "no" << endl;
            mins = 0;
        }


        //handle ingredients
        vector<string> ingredientsvec = splitString(ingredients, ',');
        vector<string> instructionsvec = splitString(instructions, ',');
        float rating;
        float calories;
        int review_count;
        int id;
        try {
            rating = stof(ratingsstr);
            calories = stof(caloriesstr);
            review_count = stoi(review_countstr);
            id = stoi(idstr);
        }
        catch (invalid_argument &e){
            rating = 0;
            calories = -1;
            review_count = 0;
        }
        catch (out_of_range &e) {
            rating = 0;
            calories = -1;
            review_count = 0;
        }


        //make recipe object
        Recipe the_recipe = Recipe(id, name, mins, category, ingredientsvec, rating, review_count,
                                   calories, author_name, instructionsvec, description, image);
        recipes.push_back(the_recipe);
    }
    return recipes;
}

int main() {
    vector<Recipe> csv_stuff = parseCSVLine("C:\\Users\\carme\\Downloads\\actuallyUpdated.csv");
    /*for (int i = 0; i < csv_stuff.size(); i++) {
        cout << csv_stuff[i].id << endl; // Print each recipe's ID for testing
    }*/
    return 0;
}
