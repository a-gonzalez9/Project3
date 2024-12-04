#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Recipe class definition remains unchanged
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

// Helper to split strings
vector<string> splitString(string str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Remove surrounding "c(" and ")"
string cleanCSVField(string& field) {
    string cleaned = field;

    // Check if the string starts with "c(" and ends with ")"
    if (cleaned.size() >= 3 && cleaned.substr(0, 2) == "c(" && cleaned.substr(cleaned.size() - 1) == "\"") {
        cleaned = cleaned.substr(2, cleaned.size() - 2); // Remove "c(" at the beginning and "\"" at the end
    }

    return cleaned;
}

Recipe organizer (vector<string> recipe_attr){
    cout << recipe_attr[0] << endl;
    cout << recipe_attr[1] << endl;
    int id = stoi(recipe_attr[0]);
    cout << "passed!" << endl;

    //handle total_cooktime
    string total_timestr = recipe_attr[6].substr(2);
    cout << total_timestr << endl;
    int hour_ind = total_timestr.find('H');
    cout << hour_ind << endl;
    int mins = 0;
    if (hour_ind != string::npos) {
        int length_to_go = hour_ind - 1;
        if (hour_ind == 1){
            length_to_go = 1;
        }
        int hours = stoi(total_timestr.substr(0, length_to_go));
        mins += 60*hours;
        total_timestr = total_timestr.substr(hour_ind + 1);
    }
    if (total_timestr.size() != 0) {
        mins += stoi(total_timestr.substr(0, total_timestr.length() - 1));
    }
    cout << "double passed!!" << endl;

    string ingredients = cleanCSVField(recipe_attr[13]);
    string instructions = cleanCSVField(recipe_attr[27]);
    //handle ingredients
    vector<string> ingredientsvec = splitString(ingredients, ',');
    vector<string> instructionsvec = splitString(instructions, ',');

    float rating, calories;
    int review_count;
    if (recipe_attr[14] != "NA"){
        rating = stof(recipe_attr[14]);
    }
    else{
        rating = 0.0;
    }
    if (recipe_attr[15] != "NA"){
        review_count = stoi(recipe_attr[15]);
    }
    else{
        review_count = 0;
    }
    if (recipe_attr[16] != "NA"){
        calories = stof(recipe_attr[16]);
    }
    else{
        calories = 0.0;
    }


    //make recipe object
    Recipe the_recipe = Recipe(id, recipe_attr[1], mins, recipe_attr[10], ingredientsvec, rating, review_count,
                               calories, recipe_attr[3], instructionsvec, recipe_attr[8], recipe_attr[9]);

    return the_recipe;
}

// Function to parse CSV file into Recipe objects
vector<Recipe> parseCSVLine(const string& filename) {
    cout << "Parsing CSV..." << endl;
    vector<Recipe> recipes;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open file :(" << endl;
        return recipes;
    }

    string line;
    getline(file, line); // Read header
    string idstr, name, authoridstr, author_name, cook_timestr,
            prep_timestr, total_timestr, date_published, description, image,
            category, keywords, ingredient_quantities, ingredients, ratingsstr, review_countstr,
            caloriesstr, instructions;
    vector<string> attr;
    int total_amount = 0;
    int count = 0;

    while (getline(file, line, ',')) {
        string returned = line;
        cout << line << endl;
        if (line.substr(0, 2) == "\"c" || line.substr(0,2) == "c("){
            returned += ",";

            while (getline(file, line, ')')){
                returned += line;
                cout << returned << endl;
//                if (line[line.size()-1] == ')'){
//
//                    getline(file, line, ',');
//                    break;
//                }
//                if (line.substr(line.size() -2, line.size()) == "\"\""){
//
//                }
                if (line[line.size()-1] != '\"' ){
                    getline(file, line, ',');
                    cout << line << endl;
                    if (line[0] == '\"' && line.size() == 1){
                        //getline(file, line, ',');
                        break;
                    }
                    continue;
                }
                getline(file, line, ',');
                break;

            }
            //cout << line << endl;
            if (line != "\""){

                if (count > 26){
                    attr.push_back(returned);
                    Recipe the_recipe = organizer(attr);
                    recipes.push_back(the_recipe);
                    attr.clear();
                    count = 0;
                    total_amount++;
                }

                int pos = line.find('\n');
                line = line.substr(pos + 1, line.size() - 1);
                attr.push_back(line);
                //cout << count << ". " << line << endl;
                count++;
                continue;
            }
        }
        else if (line[0] == '"'){
            //cout << line << endl;
            getline(file, line, '"');
            cout << line << endl << endl;
            if (line.size() != 0 || returned.size() < line.size()){
                returned += ",";
                returned += line;
                getline(file, line, ',');
                //cout << line << endl;
            }
        }

        cout << count << ". " << returned << endl;
        attr.push_back(returned);
        count++;
    }

    return recipes;
}

int main() {
    vector<Recipe> recipes = parseCSVLine("C:\\Users\\angel\\Downloads\\archive (1)\\recipes.csv");
    for (const auto& recipe : recipes) {
        cout << "ID: " << recipe.id << ", Name: " << recipe.name << endl;
    }
    return 0;
}
