/*
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "priorityqueue.h"
using namespace std;
using json = nlohmann::json;
json addPQ (PriorityQueue &pq, json &jsonObject);
int main(int argc, char** argv) {
    ifstream file;
    file.open(argv[1]);
    json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
    }

    unsigned num = jsonObject["metadata"]["maxHeapSize"];
    PriorityQueue pq(num);
    cout << addPQ(pq, jsonObject);
    file.close();
}

json addPQ (PriorityQueue &pq, json &jsonObject) {
    int numSamples = jsonObject["metadata"]["numOperations"];
    string operation;
    for (int m = 1; m <= numSamples; ++m) {
        if (m <= 9) {
            operation = "Op00" + to_string(m);
        } else if (m <= 99){
            operation = "Op0" + to_string(m);
        } else {
            operation = "Op" + to_string(m);
        }
        if (jsonObject[operation]["operation"] == "insert") { //need to switch to contains but not in the documentation
            double k = jsonObject[operation]["key"];
            pq.insert(k);
        } else {
            pq.removeMin();
        }
    }
    json result = pq.JSON();
    result["metadata"]["maxHeapSize"] = jsonObject["metadata"]["maxHeapSize"];
    result["metadata"]["numOperations"] = jsonObject["metadata"]["numOperations"];
    return result;
}

*/
