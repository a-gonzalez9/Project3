#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
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

class MergeSort {
    vector<Recipe> recipes;
    vector<string> preferences;
    int end_index;
public:
    MergeSort(vector<Recipe> recipes, vector<string> preferences, int recipes_size)
            : recipes(std::move(recipes)), preferences(std::move(preferences)), end_index(recipes_size - 1) {
    }

    Recipe comparison(Recipe left, Recipe right, string preference, int& leftptr, int& rightptr){
        if (preference == "calories"){
            if (left.calories < right.calories) {
                leftptr++;
                return left;
            }
            else{
                rightptr++;
                return right;
            }
        }
        else if (preference == "cook_time"){
            if (left.total_time < right.total_time) {
                leftptr++;
                return left;
            }
            else{
                rightptr++;
                return right;
            }
        }
        else{
            if (left.rating < right.rating) {
                leftptr++;
                return left;
            }
            else{
                rightptr++;
                return right;
            }
        }

    }

    void merge(vector<Recipe>& attribute, int start, int middle, int end, vector<string> preferences) {
        int leftSize = middle - start + 1;
        int rightSize = end - middle;
        string main_preference;
        int preference_count = 0;
        if (preferences.empty()){
            main_preference = "popularity";
        }
        else {
            main_preference = preferences[0];
            preference_count++;
        }
        //cout << "accessed" << endl;
        // Separate halves into two seperate sorted arrays
        vector<Recipe> sortedLeft;
        vector<Recipe> sortedRight;

        for(int i=0; i < leftSize; i++){
            sortedLeft.push_back(attribute[start + i]);
            //cout << "LEFT: " << sortedLeft[i].name << " ";
        }
        for(int i=0; i < rightSize; i++){
            sortedRight.push_back(attribute[middle + 1 + i]);
            //cout << "RIGHT: " << sortedRight[i].name << " ";
        }

        //cout << "#2" << endl;
        // Pointers for merging
        int leftPtr = 0, rightPtr = 0;
        int mergedPtr = start;

        if (main_preference == "calories"){
            // While both left and right have elements left
            while (leftPtr < leftSize && rightPtr < rightSize) {
                if (sortedLeft[leftPtr].calories < sortedRight[rightPtr].calories) {
                    attribute[mergedPtr++] = sortedLeft[leftPtr++];
                }
                else if (sortedLeft[leftPtr].calories == sortedRight[rightPtr].calories){
                    attribute[mergedPtr++] = comparison(sortedLeft[leftPtr], sortedRight[rightPtr], preferences[preference_count], leftPtr, rightPtr);
                }
                else {
                    attribute[mergedPtr++] = sortedRight[rightPtr++];
                }
            }

            //cout << "#3" << endl;

            while (leftPtr < leftSize) { // While left has elements left
                attribute[mergedPtr++] = sortedLeft[leftPtr++];
            }

            while (rightPtr < rightSize) { // While right has elements left
                attribute[mergedPtr++] = sortedRight[rightPtr++];
            }

            //cout << "#4" << endl;
        }
        else if (main_preference == "cook_time"){
            // While both left and right have elements left
            while (leftPtr < leftSize && rightPtr < rightSize) {
                if (sortedLeft[leftPtr].total_time < sortedRight[rightPtr].total_time) {
                    attribute[mergedPtr++] = sortedLeft[leftPtr++];
                }
                else if (sortedLeft[leftPtr].total_time == sortedRight[rightPtr].total_time){
                    attribute[mergedPtr++] = comparison(sortedLeft[leftPtr], sortedRight[rightPtr], preferences[preference_count], leftPtr, rightPtr);
                }
                else {
                    attribute[mergedPtr++] = sortedRight[rightPtr++];
                }
            }

            //cout << "#3" << endl;

            while (leftPtr < leftSize) { // While left has elements left
                attribute[mergedPtr++] = sortedLeft[leftPtr++];
            }

            while (rightPtr < rightSize) { // While right has elements left
                attribute[mergedPtr++] = sortedRight[rightPtr++];
            }

            //cout << "#4" << endl;
        }
        else{
            // While both left and right have elements left
            while (leftPtr < leftSize && rightPtr < rightSize) {
                if (sortedLeft[leftPtr].rating < sortedRight[rightPtr].rating) {
                    attribute[mergedPtr++] = sortedLeft[leftPtr++];
                }
                else if (sortedLeft[leftPtr].rating == sortedRight[rightPtr].rating){
                    attribute[mergedPtr++] = comparison(sortedLeft[leftPtr], sortedRight[rightPtr], preferences[preference_count], leftPtr, rightPtr);
                }
                else {
                    attribute[mergedPtr++] = sortedRight[rightPtr++];
                }
            }

            //cout << "#3" << endl;

            while (leftPtr < leftSize) { // While left has elements left
                attribute[mergedPtr++] = sortedLeft[leftPtr++];
            }

            while (rightPtr < rightSize) { // While right has elements left
                attribute[mergedPtr++] = sortedRight[rightPtr++];
            }

            //cout << "#4" << endl;
        }
    }

    void mergeSort(vector<Recipe>& attribute, int start, int end, vector<string> preferences) {
        vector<Recipe> update;
        int middle = (start + end) / 2;  //get the middle index
        if (start < end) { //basically if there is more than 1 element in the vector
            mergeSort(attribute, start, middle, preferences); //divide the first half until it is ones
            mergeSort(attribute, middle + 1, end, preferences); //then divide the second half
            merge(attribute, start, middle, end, preferences); //then conquer starting with the first element
        }
    }

    void mergeFunction(){
        mergeSort(recipes, 0, end_index, preferences);
        cout << "After sorting (MERGE):" << endl;
        for (Recipe recipe : recipes) {
            cout << recipe.name << " (" << recipe.calories << ", "
                 << recipe.total_time << ", " << recipe.rating << ") => ";
        }
        cout << endl;
    }

    vector<Recipe> top_five(){
        vector<Recipe> top;
        for (int i = 0; i < 5; i++){
            top.push_back(recipes[i]);
        }
        return top;
    }
};

class QuickSort {
    vector<Recipe> recipes;
    vector<string> preferences;
    int end_index;

public:
    QuickSort(vector<Recipe> recipes, vector<string> preferences, int recipes_size) {
        this->recipes = recipes;
        this->preferences = preferences;
        this->end_index = recipes_size - 1;
    }

    bool shouldSwap(Recipe a, Recipe b, vector<string> preferences) {
        for (string preference : preferences) {
            if (preference == "calories" && a.calories != b.calories)
                return a.calories > b.calories;
            if (preference == "cook_time" && a.total_time != b.total_time)
                return a.total_time > b.total_time;
            if (preference == "rating" && a.rating != b.rating)
                return a.rating < b.rating; // Higher rating is better
        }
        return false; // Equal according to preferences
    }

    int quickPartition(vector<Recipe>& attribute, int low, int high, vector<string> preferences) {
        Recipe pivot = attribute[low];
        int up_ptr = low + 1, down_ptr = high;

        while (up_ptr <= down_ptr) {
            while (up_ptr <= high && !shouldSwap(attribute[up_ptr], pivot, preferences))
                up_ptr++;
            while (down_ptr >= low && shouldSwap(attribute[down_ptr], pivot, preferences))
                down_ptr--;

            if (up_ptr < down_ptr) {
                swap(attribute[up_ptr], attribute[down_ptr]);
            }
        }
        swap(attribute[low], attribute[down_ptr]);
        return down_ptr;
    }

    void quicksort(vector<Recipe>& attribute, int low, int high, vector<string> preferences) {
        if (low < high) {
            int pivot = quickPartition(attribute, low, high, preferences);
            quicksort(attribute, low, pivot - 1, preferences);
            quicksort(attribute, pivot + 1, high, preferences);
        }
    }

    void quickFunction() {
        quicksort(recipes, 0, end_index, preferences);

        cout << "After sorting (QUICK):" << endl;
        for (Recipe recipe : recipes) {
            cout << recipe.name << " (" << recipe.calories << ", "
                 << recipe.total_time << ", " << recipe.rating << ") => ";
        }
        cout << endl;
    }

    vector<Recipe> top_five() {
        vector<Recipe> top;
        for (int i = 0; i < 5 && i < recipes.size(); i++) {
            top.push_back(recipes[i]);
        }
        return top;
    }
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
        } else {
            if (!token.empty() && token[1] == 'c' && token[2] == '(') {
                //cout << token << endl;
                //cout << "you got it: " << token.substr(1, 1) << endl;
                in_parentheses = true;
                the_string += token;
            } else {
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

    while (getline(file, line) && counter < 116) {
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

int main() {
    map<string, vector<int>> the_map;
    vector<Recipe> csv_stuff = parseCSVLine("C:\\Users\\angel\\Downloads\\actuallyUpdated\\actuallyUpdated.csv", the_map);
    for (auto it = the_map.begin(); it != the_map.end(); ++it) {
        cout << "Key: " << it->first << endl;
        for (int id : it->second) {
            cout << "Id: " << id << " ";
        }
        cout << endl;
    }

    vector<Recipe> sorting_vector;
    vector<int> ids;
    vector<string> wanted_ingredients = {" baking powder", " bay leaf"};
    vector<string> unwanted_ingredients = {" baking soda", " butter"};
    vector<string> preferences = {"calories", "cook_time", "popularity"};

    for(string ingredient : wanted_ingredients){
        if (the_map.find(ingredient) != the_map.end()){
            cout << the_map[ingredient][0] << endl;
            for (int id : the_map[ingredient]){
                if (find(ids.begin(), ids.end(),id) == ids.end()){
                    ids.push_back(id);
                }
            }

        }
    }

    cout << "\nWanted IDS:\n";
    for (int id : ids){
        cout << id << ", ";
    }

    cout << endl;
    for(string bad_ingredient : unwanted_ingredients){
        if (the_map.find(bad_ingredient) != the_map.end()){
            for (int id : the_map[bad_ingredient]){
                if (find(ids.begin(), ids.end(),id) != ids.end()){
                    ids.erase(find(ids.begin(), ids.end(), id));
                }
            }
        }
    }

    cout << "\nFinal:\n";
    for (int id : ids){
        cout << id << ", ";
    }

    for (int id : ids){
        for (auto recipe : csv_stuff){
            if (id == recipe.id){
                sorting_vector.push_back(recipe);
            }
        }
    }
    cout << endl;
    for (auto recipe : sorting_vector){
        cout << recipe.id << ": " << recipe.name << endl;
    }
    cout << endl;
    int size = sorting_vector.size();

    MergeSort merge_test = MergeSort(sorting_vector, preferences, size);
    QuickSort quick_test = QuickSort(sorting_vector, preferences, size);

    merge_test.mergeFunction();
    quick_test.quickFunction();

    return 0;
}
