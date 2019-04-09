#include "NBA.hpp"

NBA::NBA(int hashTableSize)
{
  teamHashTable = new team*[hashTableSize];
  this->hashTableSize = hashTableSize;
  numItems = 0;
  numCollisions = 0;

  for(int i = 0; i < hashTableSize; i++)
  {
    teamHashTable[i] = nullptr; //nullptr all teams
  }
  cout << "successfully constructed" << endl;
}

NBA::~NBA()
{
  for(int i = 0; i < hashTableSize; i++)
  {
    team* p = teamHashTable[i];
    team* p2 = teamHashTable[i];
    while(p != nullptr)
    {
      p2 = p;
      p = p->next;
      delete p2;
    }
  }
}

//addWord(string word) -> adds word to the teamHashTable
void NBA::addTeam(string name)
{
  cout << "adding team: " << name << endl;
  if(searchTable(name) == nullptr) //word does not exist in the array
  {
    cout << name << " does not exist yet" << endl;
    team* p = teamHashTable[getHash(name)]; //create a pointer towards where the word should be
    if(p == nullptr) //the list at hashTable[getHash(word)] is empty
    {
      team* newTeam = new team; //create a new team
      newTeam->name = name; //initialize values
      newTeam->count = 1;
      newTeam->next = nullptr;
      teamHashTable[getHash(name)] = newTeam; //stick it in the array
    }
    else //there is a collision at hashTable[getHas(word)]
    {
      cout << name << " already exists" << endl;
      team* newTeam = new team; //create a new team
      newTeam->name = name; //initialize values
      newTeam->count = 1;
      newTeam->next = p; //set the team's next equal to the current team in its position
      teamHashTable[getHash(name)] = newTeam; //stick it in the array
      numCollisions++; //increment numCollisions
    }
    numItems++; //increment numItems
  }
}

bool NBA::isInTable(string name)
{
  return(searchTable(name) != nullptr);
}

void NBA::incrementCount(string name)
{
  team* p = searchTable(name); //create a pointer towards the word
  //TEAMS DO NOT HAVE A COUNT
  //p->count++; //increment the team's count
}

//helper function to sort the teams
int insertIntoSortedArray(team* teams[], int size, team* key, int capacity)
{
  if (size >= capacity)
  {
    return size;
  }
  int i;
  for (i = size - 1; (i >= 0  && teams[i]->count > key->count); i--)
  {
    teams[i + 1] = teams[i];
  }
  teams[i + 1] = key;
  return (size + 1);
}

void NBA::printTopN(int n)
{
  int index = 0;
  team* teams[numItems];
  for(int i = 0; i < hashTableSize; i++)
  {
    team* p = teamHashTable[i]; //create a pointer towards the current hashTable element
    while(p != nullptr)
    {
      index = insertIntoSortedArray(teams, index, p, numItems);
      p = p->next;
    }
  }

  for(int i = 0; i < n; i++)
  {
    cout << fixed << setprecision(4) << (float)teams[numItems - 1 - i]->count/getTotalNumWords() << " - " << teams[numItems - 1 - i]->name << endl; //print out
  }
}

int NBA::getNumCollisions()
{
  return numCollisions;
}

int NBA::getNumItems()
{
  return numItems;
}

int NBA::getTotalNumWords()
{
  int total = 0;
  for(int i = 0; i < hashTableSize; i++)
  {
    if(teamHashTable[i] != nullptr)
    {
      team* p = teamHashTable[i]; //create a pointer towards the current hashTable element
      while(p != nullptr)
      {
        total += p->count;
        p = p->next;
      }
    }
  }
  return total;
}

void NBA::printAllTeams()
{
  for(int i = 0; i < hashTableSize; i++)
  {
    if(teamHashTable[i] != nullptr)
    {
      team* p = teamHashTable[i]; //create a pointer towards the current hashTable element
      while(p != nullptr)
      {
        cout << "===" << p->name << "===" << endl;
        cout << "points per game: " << p->pointsPerGame << endl;
        cout << "shooting percentage: " << p->shootingPercentage << "%" << endl;
        cout << "rebound percentage: " << p->reboundPercentage << "%" << endl;
        cout << "defensive rebounding percentage: " << p->defensiveReboundingPercentage << "%" << endl;
        p = p->next;
      }
    }
  }
}

//Helper functions

//getHash -> returns the hash of a word. Radical, bro!
unsigned int NBA::getHash(string name)
{
  unsigned int hashValue = 5381;
  int length = name.length();
  for (int i = 0; i < length ;i++)
  {
    hashValue=((hashValue << 5) + hashValue) + name[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}

//returns a pointer to the team represented by word
team* NBA::searchTable(string name)
{
  team* p = teamHashTable[getHash(name)]; //create a pointer towards the word
  while(p != nullptr) //while the pointer isn't null
  {
    if(p->name == name) //if it's pointing to the correct word
    {
      return p; //return it
    }
    else
    {
      p = p->next; //move it to the next one in the linked list
    }
  }
  return p; //if p is nullptr or it's the correct team, return it
}

//helper function for downloadURL
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

string NBA::downloadURL(string urlString, string outputString)
{
  //first we convert the string parameters into arrays of chars
  //It's a stupid process
  char url[urlString.length() + 1];
  strcpy(url, urlString.c_str());

  char output[outputString.length() + 1];
  strcpy(output, outputString.c_str());

  //create CURL instance
  CURL *curl = curl_easy_init();
  char *fileName = output;
  FILE *file;
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    file = fopen(fileName, "wb");
    if(file)
    {
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, file); //write the data to the output file
      curl_easy_perform(curl); //do the stuff! Download it!
      fclose(file); //close the file now that we're done
    }
    curl_easy_cleanup(curl); //I'm not sure what this does but all the libcurl examples use it
  }
  return output;
}

void NBA::setStat(string url, int statID)
{
  ifstream myfilestream;
  myfilestream.open(downloadURL(url, "fileOPT"));
  if (myfilestream.is_open()) //check if the stream is open
  {
      string line = "";
      while (getline(myfilestream, line)) //while there are more lines to be added
      {
          if(line.find("td class=\"text-left nowrap\" data-sort=\"") != -1) //if the line contains a team name
          {
            //locate the name within the line
            int nameIndex = line.find("td class=\"text-left nowrap\" data-sort=\"") + 39; //the index of line at which the name starts
            string name = line.substr(nameIndex, line.find("\"><a") - nameIndex); //' "><a ' is the location at which the name ends
            cout << "Team name: " << name << endl;

            //because the "last 3" statistic is two lines down from the line with the team name,
            //we need to go two lines down by calling getline twice.
            getline(myfilestream,line);
            getline(myfilestream,line);

            //locate the statistic within the line
            int statisticIndex = line.find(">") + 1; //the index of the statistic within the line
            string statistic = line.substr(statisticIndex, line.find("<", statisticIndex) - statisticIndex);
            cout << statistic << endl;
            cout << stod(statistic) << endl;

            switch(statID)
            {
              case 0:
                teamHashTable[getHash(name)]->pointsPerGame = stod(statistic);
                cout << teamHashTable[getHash(name)]->pointsPerGame << endl;
              break;
              case 1:
                teamHashTable[getHash(name)]->shootingPercentage = stod(statistic);
              break;
              case 2:
                teamHashTable[getHash(name)]->reboundPercentage = stod(statistic);
              break;
              case 3:
                teamHashTable[getHash(name)]->defensiveReboundingPercentage = stod(statistic);
              break;
              case 4:
                teamHashTable[getHash(name)]->blockPercentage = stod(statistic);
              break;
              case 5:
                teamHashTable[getHash(name)]->stealsPerDefensivePlay = stod(statistic);
              break;
              case 6:
                teamHashTable[getHash(name)]->turnoversPerPossession = stod(statistic);
              break;
              case 7:
                teamHashTable[getHash(name)]->opponentShootingPercentage = stod(statistic);
              break;
              case 8:
                teamHashTable[getHash(name)]->opponentReboundPercentage = stod(statistic);
              break;
              case 9:
                teamHashTable[getHash(name)]->opponentTurnoversPerPossessionPercentage = stod(statistic);
              break;
              case 10:
                teamHashTable[getHash(name)]->opponentPointsPerGame = stod(statistic);
              break;
              default:
              cout << "What the fuck did you type in?" << endl;
              break;
            }
          }
      }
  }
  else //if it couldn't be opened, print this
  {
      cout << "Failed to open the file." << endl;
  }
  myfilestream.close(); //close the file stream
}

//use the url of https://www.teamrankings.com/nba/stat/points-per-game
//set all the teams names
void NBA::setTeamNames()
{
  string url = "https://www.teamrankings.com/nba/stat/points-per-game";

  ifstream myfilestream;
  myfilestream.open(downloadURL(url, "fileOPT"));
  if (myfilestream.is_open()) //check if the stream is open
  {
      string line = "";
      while (getline(myfilestream, line)) //while there are more lines to be added
      {
          if(line.find("td class=\"text-left nowrap\" data-sort=\"") != -1) //disregard empty lines, or those that are a stop word
          {
            //cout << line << endl;
            int nameIndex = line.find("td class=\"text-left nowrap\" data-sort=\"") + 39; //the index of line at which the name starts
            string name = line.substr(nameIndex, line.find("\"><a") - nameIndex); //' "><a ' is the location at which the name ends
            //cout << name << endl;
            addTeam(name); //add the team to the roster
          }
      }
  }
  else //if it couldn't be opened, print this
  {
      cout << "Failed to open the file." << endl;
  }
  myfilestream.close(); //close the file stream
}

void NBA::initializeAllStats()
{
  setStat("https://www.teamrankings.com/nba/stat/points-per-game", 0);
/*
  setStat("https://www.teamrankings.com/nba/stat/shooting-pct", 1);
  setStat("https://www.teamrankings.com/nba/stat/offensive-rebounding-pct", 2);

  setStat("https://www.teamrankings.com/nba/stat/defensive-rebounding-pct", 3);

  setStat("https://www.teamrankings.com/nba/stat/block-pct", 4);
  setStat("https://www.teamrankings.com/nba/stat/steal-pct", 5);
  setStat("https://www.teamrankings.com/nba/stat/turnovers-per-possession", 6);
  setStat("https://www.teamrankings.com/nba/stat/opponent-shooting-pct", 7);
  setStat("https://www.teamrankings.com/nba/stat/opponent-offensive-rebounding-pct", 8);
  setStat("https://www.teamrankings.com/nba/stat/opponent-turnovers-per-possession", 9);
  setStat("https://www.teamrankings.com/nba/stat/opponent-points-per-game", 10);
  */
}
