#ifndef NBA_H
#define NBA_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include "curlIN/curl.h"
using namespace std;

//struct that represents a player
struct player
{
  string position;
  int age;
  int height; //total height in inches
  int weight; //weight in lbs
};

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


/* class HashTable for storing words.
 *   You will create two hash tables in your driver:
 *      - one for storing stop words
 *      - one for storing unique non-stop words
 *   Why? We can load all the stopwords into the first table.
 *   Then, we can quickly check that first hash table to see if
 *   a word is a stopword before adding it to the second.
 */
class NBA {
  public:
    NBA(int hashTableSize);
    ~NBA();

    void addTeam(string team); //create a new team struct with name "name" and add it to the hashTable
    bool isInTable(string team);
    void incrementCount(string team);
    void printTopN(int n);
    int getNumCollisions();
    int getNumItems();
    int getTotalNumWords();
    void printTeam(string name);
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

    //prints all team names
    void printNames();

    //prints all the team names in the hashTable
    void printAllTeams();

    //put in a team name and get the corrseponding team struct. Return nullptr if it does not exist
    team* searchTable(string team);

    //returns a poiter to the team struct with the highest score
    team* getBestTeam();

    //compare two teams, the difference between team1 and team2's scores
    //a high positive number --> team1 is much better
    //low positive score --> team1 is slightly better
    //high negative --> team2 much better
    //low negative --> team2 slightly better
    int compareTeams(string team1, string team2);

  private:
    /* member functions */
    unsigned int getHash(std::string word);


    /* instance variables */
    team** teamHashTable;
    int hashTableSize;
    int numItems;
    int numCollisions;
};

#endif
