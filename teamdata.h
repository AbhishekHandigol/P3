/*
#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_

#include "json.hpp"
#include <string>
#include <vector>
using namespace std;
using json = nlohmann::json;

class TeamData {
 public:
    TeamData(ifstream file, string filename, json &jsonObject);
 	int numPlayers() const;
    vector <vector<double>> getWinPercentages (json &jsonObject);
 	double winPercentages(int i, int j) const {return winPercentages_[i][j];}

 private:
	// TODO: decide the type of this variable.
	vector <vector<double>> winPercentages_;
	int numPlayers_;
    string filename;
};  // class TeamData

#endif  // _TEAMDATA_H_
*/
