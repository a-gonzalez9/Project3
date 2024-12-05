#include <iostream>
#include <vector>
#include <chrono>
#include "testing.cpp"

using namespace std;

class QuickSort{
    vector<Recipe> recipes;
    vector<string> preferences;
    int end_index;
public:
    QuickSort(vector<Recipe> recipes, vector<string> preferences, int recipes_size){
        this->recipes = recipes;
        this->preferences = preferences;
        this->end_index = recipes_size - 1;
    }

    Recipe comparison(Recipe left, Recipe right, string preference, int& leftptr, int& rightptr){

    }

    int quickPartition(vector<Recipe> &attribute, int low, int high, vector<string> preferences) {
        string main_preference;
        int preference_count;

        if (preferences.size() == 0){
            main_preference = "popularity";
        }
        else {
            main_preference = preferences[0];
            preference_count = 1;
        }

        Recipe pivot = attribute[low];
        Recipe up = attribute[low];
        Recipe down = attribute[high];

        int pivot_point = low;
        int up_ptr = low;
        int down_ptr = high;

        if (main_preference == "calories"){
            while (up_ptr < down_ptr) {
                for (int j = up_ptr; j < high; j++) {
                    if (attribute[up_ptr].calories > pivot.calories) {
                        break;
                    }
                    if (attribute[up_ptr].rating == pivot.rating){
                        if (preferences[preference_count] == "cook_time"){
                            bool val = attribute[up_ptr].total_time > pivot.total_time;
                            if (val){
                                break;
                            }
                        }
                        else{
                            bool val = attribute[up_ptr].rating > pivot.rating;
                            if (val){
                                break;
                            }
                        }
                    }
                    up_ptr++;
                }
                for (int i = high; i > low; i--) {
                    if (attribute[down_ptr].calories < pivot.calories) {
                        break;
                    }
                    if (attribute[down_ptr].rating == pivot.rating){
                        if (preferences[preference_count] == "cook_time"){
                            bool val = attribute[down_ptr].total_time < pivot.total_time;
                            if (val){
                                break;
                            }
                        }
                        else{
                            bool val = attribute[down_ptr].rating < pivot.rating;
                            if (val){
                                break;
                            }
                        }
                    }
                    down_ptr--;
                }
                if (up_ptr < down_ptr) {
                    swap(attribute[up_ptr], attribute[down_ptr]);
                }
            }
        }
        else if (main_preference == "cook_time"){
            while (up_ptr < down_ptr) {
                for (int j = up_ptr; j < high; j++) {
                    if (attribute[up_ptr].total_time > pivot.total_time) {
                        break;
                    }
                    if (attribute[up_ptr].total_time == pivot.total_time){
                        if (preferences[preference_count] == "calories"){
                            bool val = attribute[up_ptr].calories > pivot.calories;
                            if (val){
                                break;
                            }
                        }
                        else{
                            bool val = attribute[up_ptr].rating > pivot.rating;
                            if (val){
                                break;
                            }
                        }
                    }
                    up_ptr++;
                }
                for (int i = high; i > low; i--) {
                    if (attribute[down_ptr].total_time < pivot.total_time) {
                        break;
                    }
                    down_ptr--;
                }
                if (up_ptr < down_ptr) {
                    swap(attribute[up_ptr], attribute[down_ptr]);
                }
            }
        }
        else{
            while (up_ptr < down_ptr) {
                for (int j = up_ptr; j < high; j++) {
                    if (attribute[up_ptr].rating > pivot.rating) {
                        break;
                    }
                    if (attribute[up_ptr].rating == pivot.rating){
                        if (preferences[preference_count] == "cook_time"){
                            bool val = attribute[up_ptr].total_time > pivot.total_time;
                            if (val){
                                break;
                            }
                        }
                        else{
                            bool val = attribute[up_ptr].calories > pivot.calories;
                            if (val){
                                break;
                            }
                        }
                    }
                    up_ptr++;
                }
                for (int i = high; i > low; i--) {
                    if (attribute[down_ptr].rating < pivot.rating) {
                        break;
                    }
                    if (attribute[down_ptr].rating == pivot.rating){
                        if (preferences[preference_count] == "cook_time"){
                            bool val = attribute[down_ptr].total_time < pivot.total_time;
                            if (val){
                                break;
                            }
                        }
                        else{
                            bool val = attribute[down_ptr].calories < pivot.calories;
                            if (val){
                                break;
                            }
                        }
                    }
                    down_ptr--;
                }
                if (up_ptr < down_ptr) {
                    swap(attribute[up_ptr], attribute[down_ptr]);
                }
            }
        }

        swap(attribute[low], attribute[down_ptr]);
        pivot_point = down_ptr;
        return pivot_point;
    }

    void quicksort(vector<Recipe>& attribute, int low, int high, vector<string> preferences) {
        if (low < high) {
            int pivot = quickPartition(attribute, low, high, preferences);
            quicksort(attribute, low, pivot - 1, preferences);
            quicksort(attribute, pivot + 1, high, preferences);
        }
    }

    void quickFunction(){
        quicksort(recipes, 0, end_index, preferences);
        for (Recipe recipe : recipes){
            cout << recipe.name << " => ";
        }
    }
};

//int main(){
//    vector<int> vals = {2,5,69,420,33,46,1,7};
//    QuickSort test;
//    chrono::time_point<chrono::system_clock> start, end;
//
//    start = chrono::system_clock::now();
//    test.quicksort(vals, 0, 7);
//    end = chrono::system_clock::now();
//
//    chrono::duration<double> time = end - start;
//
//    for (int val : vals){
//        cout << val << " ";
//    }
//    cout << "\nelapsed time: " << time.count() << "s\n";

//    chrono::time_point<chrono::system_clock> start, end;
//
//    Recipe pie = Recipe(1, "pie", 240, 4, 145.2);
//    Recipe cookie = Recipe(2, "cookie", 60, 5, 62.4);
//    Recipe sandwich = Recipe(3, "sandwich", 75, 3, 145.2);
//    Recipe muffin = Recipe(4, "muffin", 30, 2, 25.4);
//
//    vector<Recipe> recipes;
//    recipes.push_back(pie);
//    recipes.push_back(cookie);
//    recipes.push_back(sandwich);
//    recipes.push_back(muffin);
//
//    vector<string> preferences = {"calories", "cook_time"};
//
//    QuickSort test = QuickSort(recipes, preferences, recipes.size());
//    start = chrono::system_clock::now();
//    test.quickFunction();
//    end = chrono::system_clock::now();
//
//    chrono::duration<double> time = end - start;
//    cout << "\nelapsed time: " << time.count() << "s\n";
//
//    return 0;
//}