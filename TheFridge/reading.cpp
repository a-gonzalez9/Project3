#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
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

    Recipe(int id, string name, int total_time, string category, vector<string> ingredients, float rating,
           int review_count, float calories, string author)
            : id(id), name(name), total_time(total_time), category(category), ingredients(ingredients), rating(rating),
              review_count(review_count), calories(calories), author(author) {}
};

// Helper function to split a string based on a delimiter, respecting quoted fields

vector<string> splitStringWithQuotes(const string& str, char delim) {
    vector<string> result;
    stringstream ss(str);
    string the_string = "";
    string token;
    int curr_field_ind = 0;
    bool in_parentheses = false;

    while (getline(ss, token, delim)) {

        if (in_parentheses) {
            the_string += delim + token;
            if (!token.empty() && token[token.size() - 2] == ')') {
                //cout << "we in dih bih" << endl;
                in_parentheses = false;
                // Remove extra quotes inside c(...) block
                //cout << the_string << endl;
                result.push_back(the_string);
                the_string.clear();
            }
        }
        else {
            if (!token.empty() && token[1] == 'c' && token[2] == '(') {
                //cout << token << endl;
                //cout << "you got it: " << token.substr(1, 1) << endl;
                in_parentheses = true;
                the_string += token;
            }

            else {
                result.push_back(token);
            }
        }
        if (!in_parentheses) {
            curr_field_ind++;
        }
    }

    //cout << result[0] << endl;
    return result;
}

vector<Recipe> parseCSVLine(const string& filename, map<string, vector<int>> &the_map) {
    vector<Recipe> recipes;
    ifstream file(filename);
    int counter = 0;

    if (!file.is_open()) {
        cout << "Could not open file :(" << endl;
        return recipes;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line) && counter < 2200) {
        stringstream ss(line);
        //cout << line << endl;
        string idstr, name, authoridstr, author_name, cook_timestr,
                prep_timestr, total_timestr, date_published,
                category, keywords, ingredient_quantities, ingredients, ratingsstr, review_countstr,
                caloriesstr, fatcontentstr, saturatedfatstr, cholesterolstr, carbsstr, fiberstr,
                sugarstr, proteinstr, servingsstr, yeild;


        // Parsing the line into individual fields with custom split function to handle quoted fields
        vector<string> fields = splitStringWithQuotes(line, ',');

        idstr = fields[0];
        name = fields[1];
        authoridstr = fields[2];
        author_name = fields[3];
        cook_timestr = fields[4];
        prep_timestr = fields[5];
        total_timestr = fields[6];
        date_published = fields[7];
        category = fields[8];
        keywords = fields[9];
        ingredient_quantities = fields[10];
        ingredients = fields[11];
        ratingsstr = fields[12];
        review_countstr = fields[13];
        caloriesstr = fields[14];


        //cout << "anything" << endl;


        // Handle total cook time parsing

        if (total_timestr[0] == 'P') {
            total_timestr = total_timestr.substr(2);
        }
        int mins = 0;
        if (total_timestr.find('H') != string::npos) {
            int hour_ind = total_timestr.find('H');
            int hours;
            try {
                hours = stoi(total_timestr.substr(0, hour_ind));
            }
            catch (invalid_argument &e) {
                hours = 0;
            }
            mins += hours * 60;
            total_timestr = total_timestr.substr(hour_ind + 1);
        }
        try {
            mins += stoi(total_timestr.substr(0, total_timestr.length() - 1));
        }
        catch (invalid_argument &e) {
            mins = 0; // Default to 0 if conversion fails
        }

        // Handle ingredients and instructions
        vector<string> ingredientsvec = splitStringWithQuotes(ingredients.substr(3, ingredients.size() - 6), ',');

        // Convert rating, review count, and calories to numeric types
        float rating;
        int review_count;
        float calories;
        int id;
        try {
            id = stoi(idstr);
        }
        catch (invalid_argument &e) {
            id = 0;
        }
        try {
            rating = stof(ratingsstr);
        }
        catch (invalid_argument &e) {
            rating = 0;
        }

        try {
            review_count = stoi(review_countstr);
        }
        catch (invalid_argument &e) {
            review_count = 0;
        }

        try {
            calories = stof(caloriesstr);
        }
        catch (invalid_argument &e) {
            calories = 0;
        }
        for (int i = 0; i < ingredientsvec.size(); i++) {
            for (auto str : splitStringWithQuotes(ingredientsvec[i], ',')) {
                string new_stir;
                for (char c: str) {
                    if (c != '"') {
                        new_stir += c;
                    }
                }
                the_map[new_stir].push_back(id);
            }
        }

        // Create Recipe object and store it in the vector
        Recipe the_recipe = Recipe(id, name, mins, category, ingredientsvec, rating, review_count, calories, author_name);
        recipes.push_back(the_recipe);
        //cout << the_recipe.rating << endl;
        counter++;
    }

    return recipes;
}
vector<vector<string>> stringsss(vector<Recipe> recipe_objs) {
    vector<vector<string>> all_strings;
    for (int i = 0; i < recipe_objs.size(); i++) {
        vector<string> strings;

        string name = "Name: ";
        name += recipe_objs[i].name;
        strings.push_back(name);

        string calories = "Calorie count: ";
        calories += to_string(recipe_objs[i].calories);
        strings.push_back(calories);

        string cook_time = "Cook time: ";
        int mins = recipe_objs[i].total_time % 60;
        int hours = recipe_objs[i].total_time / 60;
        if (hours > 0) {
            cook_time += to_string(hours) + " hours ";
        }
        cook_time += to_string(mins) + " mins";
        strings.push_back(cook_time);

        string review_count = "Number of Reviews: ";
        review_count += to_string(recipe_objs[i].review_count);
        strings.push_back(review_count);

        string ingredients = "Ingredients: ";
        for (int j = 0; j < recipe_objs[i].ingredients.size(); j++) {
            if (j + 1 == recipe_objs[i].ingredients.size()) {
                ingredients += recipe_objs[i].ingredients[j];
            }
            else {
                ingredients += recipe_objs[i].ingredients[j] + ", ";
            }
            strings.push_back(ingredients);
        }
        all_strings.push_back(strings);

    }
    return all_strings;
}


