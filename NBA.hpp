#ifndef NBA_H
#define NBA_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <vector>
#include "curlIN/curl.h"
using namespace std;

//struct that represents a team
struct team
{
    string name; //name of this team
    int score; //score added up

    team* next; //next
    int count; //count

    //each stat has an ID that we use to get data with
    double pointsPerGame; //ID 0
    double shootingPercentage; //ID 1
    double reboundPercentage; //ID 2
    double defensiveReboundingPercentage;//ID 3
    double blockPercentage;//ID 4
    double stealsPerDefensivePlay;//ID 5
    double turnoversPerPossession;//ID 6
    double opponentShootingPercentage;//ID 7
    double opponentReboundPercentage;//ID 8
    double opponentTurnoversPerPossessionPercentage;//ID 9
    double opponentPointsPerGame;//ID 10
};

//struct that represents the comparison of two teams
struct teamComparison
{
  string t1; //name of team 1
  string t2;
  int spread;
  bool TBD;
  bool t1Wins; //holds true if team1 is the predicted winner
  string date;
};

class NBA
{
  public:

    NBA(int hashTableSize);

    ~NBA();

    void addTeam(string team); //create a new team struct with name "name" and add it to the hashTable

    //returns if the given team is in the table
    bool isInTable(string team);

    int getNumItems();

    //print a specific team's information
    void printTeam(string name);

    //returns the date as "Weekday Month Day"
    string getDay();

    string getMonth();
    /*
    * Name setter
    * For each name within file
    * addTeam(name);
    */
    void setTeamNames(); //parse all team names and add each with addTeam(name);

    //download the url and return the output filename
    /*
     * downloadURL(string url, string output)
     * Uses libcurl to download the HTML of a website at url
     * Save contents to output
     */
    string downloadURL(string url, string output);

    /*
     * setStat(string url, int statID);
     * call downloadURL to download the file
     * parse the file and locate the name and statistic
     * insert the statistic into the proper team struct
     */
    void setStat(string url, int statID);

    //calls setStat for each stat
    void initializeRoster();

    //for each team, set its score
    void initializeScores();

    //gets the upcoming games starting at the current date
    void initializeUpcomingGames(string url);

    void printSpreadAboveN(int n);

    //prints all team names
    void printNames();

    //helper function for getPPPP
    void ppppUtil(team arr[], team temp[], int start, int end, int index);

    //get all team comparisons and load them into the heap
    void getPPPP();

    //prints all the team names in the hashTable
    void printAllTeams();

    //put in a team name and get the corrseponding team struct. Return nullptr if it does not exist
    team* searchTable(string team);

    //returns a poiter to the team struct with the highest score
    team* getBestTeam();

    //returns true if an upcoming game with these teams already exists
    bool upcomingGameAlreadyExists(string team1, string team2);

    //compare two teams, the difference between team1 and team2's scores
    //a high positive number --> team1 is much better
    //low positive score --> team1 is slightly better
    //high negative --> team2 much better
    //low negative --> team2 slightly better
    int compareTeams(string team1, string team2);

    //prints the best n matchups
    void printTopNMatchups(int n);

    void printUpcomingGames(int n);

    void printTeamComparison(teamComparison tc);

    void printUpcomingGamesWithSpreadAboveN(int spreadThreshold);

    //cool wacky MaxHeap public shiznit
    void heapify(int index);
    void heapSort();
    void addToHeap(teamComparison comparison);
    teamComparison* peekTopComparison();
    bool isFull();
    bool isEmpty();

  private:
    //getHash
    unsigned int getHash(std::string word);

    //instance variables
    team** teamHashTable;
    int hashTableSize;
    int numItems;

    //vector to store the upcoming games
    vector<teamComparison> upcomingGames;

    //MaxHeap private stuff
    void repairUpward(int nodeIndex);
    void repairDownward(int nodeIndex);
    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);
    teamComparison* heapArr;//pointer to array
    int currentSize;
    int heapSize;
    int capacity;
};

#endif
