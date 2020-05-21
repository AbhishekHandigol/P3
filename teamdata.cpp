/*
#include "teamdata.h"
#include "json.hpp"
#include <cmath>
using namespace std;
using json = nlohmann::json;
#include <fstream>


TeamData::TeamData(ifstream file, string filename, json &jsonObject) {
    file.open(filename);
    if (file.is_open()) {
        file >> jsonObject;
    }
    winPercentages_ = getWinPercentages(jsonObject);
}

vector <vector<double>> getWinPercentages (json &jsonObject) {
    vector<json> teams = jsonObject["teamStats"];
    vector <vector<double>> winPercentages_;
    for(int k : teams) {
        json temp = teams[k];
        double winPercentage = temp["winPercentage"];
        double abswinPercentage = abs(50 - winPercentage);
        winPercentages_[temp["playerOne"]][temp["playerTwo"]] = abswinPercentage;
    }
    return winPercentages_;
}


int numPlayers(int numPlayers_, json &jsonObject){
    numPlayers_ = jsonObject["metadata"]["numPlayers"];
    return numPlayers_;
}

*/
