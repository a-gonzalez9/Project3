//
// Created by carmel on 11/28/2024.
//

#include "hashmap.h"
#include <iostream>
#include <list>
#include <vector>
using namespace std;

//VERY basic hashmap
class Hashmap {
    //list<string> elems;
    vector<list<string>> arr;
    int size;
    int num_elems;
    float load_factor;

    int hashFunc(string key) {
        return key.length() % size;
    }

public:
    Hashmap(int buckets) {
        size = buckets;
        arr.resize(buckets);
        num_elems = 0;
        load_factor = 0.75;
    }

    void insert(string key) {
        int index = hashFunc(key);
        arr[index].push_back(key);
        num_elems++;
        cout << (float)num_elems / (float)size << endl;
        if ((float)num_elems / (float)size >= load_factor) {
            resize();
        }
        //cout << "Yippee!" << endl;
    }

    void resize() {
        size *= 2;
        vector<list<string>> newArr(size);
        for (int i = 0; i < size / 2; i++) {
            for (auto& key: arr[i]) {
                int index = hashFunc(key);
                newArr[index].push_back(key);
            }
            arr[i].clear();
        }
        arr = move(newArr);
    }

    list<string> getElems(string key) {
        int index = hashFunc(key);
        return arr[index];
    }

    void display() {
        for (int i = 0; i < size - 1; i++) {
            cout << i << ": ";
            for (auto &key : arr[i]) {
                cout << key << ", ";
            }
        }
        cout << endl;
    }
};
