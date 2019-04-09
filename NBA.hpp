#ifndef NBA_H
#define NBA_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
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

    /*
    * Setters
    * calls setStat(contextualURL, contextualID);
    */
    void setTeamPointsPerGame();
    void setTeamShootingPercentage();
    void setTeamReboundingPercentage();
    void setTeamDefensiveReboundingPercentage();
    void setTeamBlockPercentage();
    void setTeamStealsPerDefensivePlay();
    void setTeamTurnoversPerPossession();
    void setTeamOpponentShootingPercentage();
    void setTeamOpponentReboundPercentage();
    void setOpponentTurnoversPerPossessionPercentage();
    void setTeamOpponentPointsPerGame();

    //prints all the team names in the hashTable
    void printAllTeams();

  private:
    /* member functions */
    unsigned int getHash(std::string word);
    team* searchTable(std::string word);

    /* instance variables */
    team** teamHashTable;
    int hashTableSize;
    int numItems;
    int numCollisions;
};

#endif
