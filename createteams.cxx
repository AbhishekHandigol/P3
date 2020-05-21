//#include "teamdata.h"
#include "priorityqueue.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
using json = nlohmann::json;

void fillPQ (PriorityQueue &pq, json &jsonObject);
json makeTeams(PriorityQueue &pq, json &jsonObject);

int main(int argc, char** argv) {
    ifstream file;
    json jsonObject;
    file.open(argv[1]);
    if (file.is_open()) {
        file >> jsonObject;
    }
    //TeamData td (file, argv[1], jsonObject);
    int size = jsonObject["teamStats"].size();
    PriorityQueue pq(size);
    fillPQ(pq, jsonObject);
    cout << makeTeams(pq, jsonObject);
    file.close();
}

void fillPQ (PriorityQueue &pq, json &jsonObject) {
    vector<json> teams = jsonObject["teamStats"];
    for(int k = 0; k < teams.size(); k++) {
        json temp = teams[k];
        double winPercentage = temp["winPercentage"];
        double abswinPercentage = abs(50 - winPercentage);
        int p1 = temp["playerOne"];
        int p2 = temp["playerTwo"];
        Value p(p1,p2);
        KeyValuePair m (abswinPercentage, p);
        pq.insert(m);
    }
}

json makeTeams(PriorityQueue &pq, json &jsonObject) {
    int numattempts = 0;
    int numiterations = 0;
    int teamsfound = 0;
    int numPlayers = jsonObject["metadata"]["numPlayers"];
    pair<int,int> team; //temporary pair of teams
    vector<pair<int,int>> teams; //final list of team pairs
    vector<double> minimums; //sorted vector of keys
    vector<KeyValuePair> pqnodes = pq.getNodes();
    for(int i = 0; i < pqnodes.size(); ++i) {
        minimums.push_back(pqnodes[i].first);
    }
    sort(minimums.begin(), minimums.end());

    while (teamsfound != numPlayers / 2) {
        pqnodes = pq.getNodes();

        while (!pq.isEmpty()) {
            if (!numattempts) { //if it's the first attempt, just remove the minimum
                team = pq.min().second;
                pq.removeMin();
                if (!numiterations) {//first attempt at the minimum, remove from minimums
                    minimums.erase(minimums.begin());
                }
            } else { //if an attempt has already been made, remove the new minimum
                double newmin = minimums.front();
                for (int i = 0; i < pqnodes.size(); ++i) { //find next minimum in the nodes vector and erase that first
                    if (newmin == pqnodes[i].first) {
                        team = pqnodes[i].second;
                        pq.removeNode(i);
                    }
                }
            }

            teamsfound++;
            teams.push_back(team);
            if (teamsfound == numPlayers/2) {
                break;
            }
            for (int i = 1; i <= pq.size(); ++i) { //remove all nodes with the two teams already chosen
                pqnodes = pq.getNodes();
                if ((pqnodes[i].second.first == team.first) ||
                    (pqnodes[i].second.first == team.second) ||
                    (pqnodes[i].second.second == team.first) ||
                    (pqnodes[i].second.second == team.second)) {
                    pq.removeNode(i);
                    i = 0;
                }
            }

            numiterations++;
        }
        if (teamsfound == numPlayers/2) {
            break;
        }
        fillPQ(pq, jsonObject); //reset the priority queue
        teamsfound = 0;
        numiterations = 0;
        teams.clear(); //clear final vector of teams
        numattempts++; //increase num of attempts
    }
    json result;
    result["teams"] = teams;
    return result;
}

