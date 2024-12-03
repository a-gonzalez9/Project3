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
           int review_count, float calories, string author, vector<string> steps, string descrption, string image) {
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
        this->description = descrption;
        this->image = image;
    }
};

vector<string> splitString(string str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delim)) {
        tokens.push_back(token);
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
        getline(ss, keywords, ',');
        getline(ss, ingredient_quantities, ',');
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

        int id = stoi(idstr);

        //handle total_cooktime
        total_timestr = total_timestr.substr(2);
        int hour_ind = total_timestr.find('H');
        int mins = 0;
        if (hour_ind != string::npos) {
            int length_to_go = hour_ind - 1;
            int hours = stoi(total_timestr.substr(0, length_to_go));
            mins += 60*hours;
            total_timestr = total_timestr.substr(hour_ind + 1);
        }
        mins += stoi(total_timestr.substr(0, total_timestr.length() - 1));

        //handle ingredients
        vector<string> ingredientsvec = splitString(ingredients, ',');
        vector<string> instructionsvec = splitString(instructions, ',');

        float rating = stof(ratingsstr);
        int review_count = stoi(review_countstr);
        float calories = stof(caloriesstr);

        //make recipe object
        Recipe the_recipe = Recipe(id, name, mins, category, ingredientsvec, rating, review_count,
                                   calories, author_name, instructionsvec, description, image);
        recipes.push_back(the_recipe);
    }
    return recipes;
}

int main() {
    vector<Recipe> csv_stuff = parseCSVLine("C:\\Users\\carme\\Downloads\\recipes.csv\\recipes.csv");
    for (int i = 0; i < csv_stuff.size(); i++) {
        cout << csv_stuff[i].id << endl;
    }

    return 0;
}


