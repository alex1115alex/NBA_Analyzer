#ifndef NBA_H
#define NBA_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
using namespace std;

//struct that represents a team
struct team
{
    string name; //name of this team
    int score; //score added up

    team* next; //next
    int count; //count

    double pointsPerGame;
    double shootingPercentage;
    double reboundPercentage;
    double defensiveReboundingPercentage;
    double blockPercentage;
    double stealsPerDefensivePlay;
    double turnoversPerPossession;
    double opponentShootingPercentage;
    double opponentReboundPercentage;
    double opponentTurnoversPerPossessionPercentage;
    double opponentPointsPerGame;
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
    bool isInTable(string word);
    void incrementCount(string word);
    void printTopN(int n);
    int getNumCollisions();
    int getNumItems();
    int getTotalNumWords();

    void setTeamNames(); //parse all team names and add each with addTeam(name);

    /*
    * Setters
    * For each name within file also locate the corresponding statistic
    * teamHashTable[getHash(name)]->correspondingStat = correspondingData;
    */
    void setTeamPointsPerGame(string url);
    void setTeamShootingPercentage(string url);
    void setTeamReboundingPercentage(string url);
    void setTeamDefensiveReboundingPercentage(string url);
    void setTeamBlockPercentage(string url);
    void setTeamStealsPerDefensivePlay(string url);
    void setTeamTurnoversPerPossession(string url);
    void setTeamOpponentShootingPercentage(string url);
    void setTeamOpponentReboundPercentage(string url);
    void setOpponentTurnoversPerPossessionPercentage(string url);
    void setTeamOpponentPointsPerGame(string url);


    double opponentShootingPercentage;
    double opponentReboundPercentage;
    double opponentTurnoversPerPossessionPercentage;
    double opponentPointsPerGame;


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
