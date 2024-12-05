//merge sort
#include <iostream>
#include <vector>
#include <chrono>
#include "testing.cpp"
using namespace std;

class MergeSort {
    vector<Recipe> recipes;
    vector<string> preferences;
    int end_index;
public:
    MergeSort(vector<Recipe> recipes, vector<string> preferences, int recipes_size){
        this->recipes = recipes;
        this->preferences = preferences;
        this->end_index = recipes_size - 1;
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

    vector<Recipe> merge(vector<Recipe>& attribute, int start, int middle, int end, vector<string> preferences) {
        int leftSize = middle - start + 1;
        int rightSize = end - middle;
        string main_preference;
        int preference_count = 0;
        if (preferences.size() == 0){
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
            return attribute;
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
            return attribute;
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
            return attribute;
        }
    }

    void mergeSort(vector<Recipe>& attribute, int start, int end, vector<string> preferences) {
        vector<Recipe> update;
        int middle = (start + end) / 2;  //get the middle index
        if (start < end) { //basically if there is more than 1 element in the vector
            mergeSort(attribute, start, middle, preferences); //divide the first half until it is ones
            mergeSort(attribute, middle + 1, end, preferences); //then divide the second half
            update = merge(attribute, start, middle, end, preferences); //then conquer starting with the first element
        }
    }

    void mergeFunction(){
        mergeSort(recipes, 0, end_index, preferences);
        cout << "Merge Sort: ";
        for (Recipe val : recipes){
            cout << val.name << " ";
        }
        cout << endl;
    }
};

int main(){
////    vector<int> vals = {2,5,69,420,33,46,1,7};
////    MergeSort test;
////    chrono::time_point<chrono::system_clock> start, end;
////
////    start = chrono::system_clock::now();
////    test.mergeSort(vals, 0, 7);
////    end = chrono::system_clock::now();
////
////    chrono::duration<double> time = end - start;
////
////    for (int val : vals){
////        cout << val << " ";
////    }
////    cout << "\nelapsed time: " << time.count() << "s\n";
//
    chrono::time_point<chrono::system_clock> start, end;

    Recipe pie = Recipe(1, "pie", 240, 4, 145.2);
    Recipe cookie = Recipe(2, "cookie", 60, 5, 62.4);
    Recipe sandwich = Recipe(3, "sandwich", 75, 3, 145.2);
    Recipe muffin = Recipe(4, "muffin", 30, 2, 25.4);

    vector<Recipe> recipes;
    recipes.push_back(pie);
    recipes.push_back(cookie);
    recipes.push_back(sandwich);
    recipes.push_back(muffin);

    vector<string> preferences = {"calories", "cook_time"};

    MergeSort test = MergeSort(recipes, preferences, recipes.size());
    start = chrono::system_clock::now();
    test.mergeFunction();
    end = chrono::system_clock::now();

    chrono::duration<double> time = end - start;
    cout << "\nelapsed time: " << time.count() << "s\n";

    return 0;
}
