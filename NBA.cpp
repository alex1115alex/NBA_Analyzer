#include "NBA.hpp"

NBA::NBA(int hashTableSize)
{
  teamHashTable = new team*[hashTableSize];
  this->hashTableSize = hashTableSize;
  numItems = 0;

  for(int i = 0; i < hashTableSize; i++)
  {
    teamHashTable[i] = nullptr; //nullptr all teams
  }

  //initalize heap
  currentSize = 0;
  //435 is the total number of possible team comparisons
  capacity = 435;
  heapArr = new teamComparison[435];
}

NBA::~NBA()
{
  delete[] heapArr;
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
  if(searchTable(name) == nullptr) //word does not exist in the array
  {
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
      team* newTeam = new team; //create a new team
      newTeam->name = name; //initialize values
      newTeam->count = 1;
      newTeam->next = p; //set the team's next equal to the head of Bucket LL
      teamHashTable[getHash(name)] = newTeam; //stick it in the array
    }
    numItems++; //increment numItems
  }
}

bool NBA::isInTable(string name)
{
  return(searchTable(name) != nullptr);
}

int NBA::getNumItems()
{
  return numItems;
}

void NBA::printTeam(string name)
{
  team *p = searchTable(name);

  if(p == nullptr)
  {
      cout << name << " is not a valid team name." << endl;
      return;
  }

  cout << "===" << p->name << "===" << endl;
  cout << "Points per game: " << p->pointsPerGame << endl;
  cout << "Shooting percentage: " << p->shootingPercentage << "%" << endl;
  cout << "Rebound percentage: " << p->reboundPercentage << "%" << endl;
  cout << "Defensive rebounding percentage: " << p->defensiveReboundingPercentage << "%" << endl;
  cout << "Block percentage: " << p->blockPercentage << "%" << endl;
  cout << "Steals per defensive play: " << p->stealsPerDefensivePlay << endl;
  cout << "Turnovers per possession: " << p->turnoversPerPossession << endl;
  cout << "Opponent shooting percentage: " << p->opponentShootingPercentage << endl;
  cout << "Opponent rebound percentage: " << p->opponentReboundPercentage << "%" << endl;
  cout << "Opponent turnovers per possession percentage: " << p->opponentTurnoversPerPossessionPercentage << "%" << endl;
  cout << "Opponent points per game: " << p->opponentPointsPerGame << endl;
  cout << "Overall score: " << p->score << endl;
}

void NBA::printNames()
{
  for(int i = 0; i < hashTableSize; i++)
  {
    if(teamHashTable[i] != nullptr)
    {
      team* p = teamHashTable[i]; //create a pointer towards the current hashTable element
      while(p != nullptr)
      {
        cout << p->name << " - score: " << p->score << endl;
        p = p->next;
      }
    }
  }
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
        cout << "Points per game: " << p->pointsPerGame << endl;
        cout << "Shooting percentage: " << p->shootingPercentage << "%" << endl;
        cout << "Rebound percentage: " << p->reboundPercentage << "%" << endl;
        cout << "Defensive rebounding percentage: " << p->defensiveReboundingPercentage << "%" << endl;
        cout << "Block percentage: " << p->blockPercentage << "%" << endl;
        cout << "Steals per defensive play: " << p->stealsPerDefensivePlay << endl;
        cout << "Turnovers per possession: " << p->turnoversPerPossession << endl;
        cout << "Opponent shooting percentage: " << p->opponentShootingPercentage << endl;
        cout << "Opponent rebound percentage: " << p->opponentReboundPercentage << "%" << endl;
        cout << "Opponent turnovers per possession percentage: " << p->opponentTurnoversPerPossessionPercentage << "%" << endl;
        cout << "Opponent points per game: " << p->opponentPointsPerGame << endl;
        cout << "Overall score: " << p->score << endl;
        cout << endl;
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

//returns a poiter to the team struct with the highest score
team* NBA::getBestTeam()
{
  team* best = nullptr;
  for(int i = 0; i < hashTableSize; i++)
  {
    if(teamHashTable[i] != nullptr)
    {
      team* p = teamHashTable[i]; //create a pointer towards the current hashTable element
      while(p != nullptr)
      {
        if(best == nullptr || p->score >= best->score)
        {
          if(best != nullptr && p->score == best->score) //if they're equal, go by points per game
          {
            if(p->pointsPerGame > best->pointsPerGame)
            {
              best = p;
            }
          }
          else
          {
            best = p;
          }
        }

        p = p->next;
      }
    }
  }
  //cout << best->score << endl;
  return best;
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

            //because the "last 3" statistic is two lines down from the line with the team name,
            //we need to go two lines down by calling getline twice.
            getline(myfilestream,line);
            getline(myfilestream,line);

            //locate the statistic within the line
            int statisticIndex = line.find(">") + 1; //the index of the statistic within the line
            string statistic = line.substr(statisticIndex, line.find("<", statisticIndex) - statisticIndex);

            switch(statID)
            {
              case 0:
                searchTable(name)->pointsPerGame = stod(statistic);
              break;
              case 1:
                searchTable(name)->shootingPercentage = stod(statistic);
              break;
              case 2:
                searchTable(name)->reboundPercentage = stod(statistic);
              break;
              case 3:
                searchTable(name)->defensiveReboundingPercentage = stod(statistic);
              break;
              case 4:
                searchTable(name)->blockPercentage = stod(statistic);
              break;
              case 5:
                searchTable(name)->stealsPerDefensivePlay = stod(statistic);
              break;
              case 6:
                searchTable(name)->turnoversPerPossession = stod(statistic);
              break;
              case 7:
                searchTable(name)->opponentShootingPercentage = stod(statistic);
              break;
              case 8:
                searchTable(name)->opponentReboundPercentage = stod(statistic);
              break;
              case 9:
                searchTable(name)->opponentTurnoversPerPossessionPercentage = stod(statistic);
              break;
              case 10:
                searchTable(name)->opponentPointsPerGame = stod(statistic);
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

void NBA::initializeRoster()
{
  //wipe out the hashTable
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

  setTeamNames(); //initialize all teams

  setStat("https://www.teamrankings.com/nba/stat/points-per-game", 0);
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

  initializeScores();

  initializeUpcomingGames("https://www.teamrankings.com/nba/schedules/season/");

  remove("fileOPT"); //delete the download
  
  getPPPP();
}

//////////////////////////////////////////////////
///     INITIALIZE SCORES HELPER FUNCTIONS      //
//////////////////////////////////////////////////
int calcPointsPerGameScore(double n){//0
  int score = 0;
  if(n >= 123){
    score = 22;
  }else if(n >= 120 && n < 123){
    score = 20;
  }else if(n >= 117 && n < 120){
    score = 18;
  }else if(n >= 114 && n < 117){
    score = 16;
  }else if(n >= 111 && n < 114){
    score = 14;
  }else if(n >= 108 && n < 111){
    score = 12;
  }else if(n >= 105 && n < 108){
    score = 10;
  }else if(n >= 102 && n < 105){
    score = 8;
  }else if(n >= 99 && n < 102){
    score = 4;
  }else if(n >= 96 && n < 99){
    score = 2;
  }else if(n >= 93 && n < 96){
    score = 0;
  }
  return score;
}

int calcShootintPercentageScore(double n){//1
  int score = 0;
  if(n >= 50){
    score = 10;
  }else if(n >= 49 && n < 50){
    score = 9;
  }else if(n >= 48 && n < 49){
    score = 8;
  }else if(n >= 47 && n < 48){
    score = 7;
  }else if(n >= 46 && n < 47){
    score = 6;
  }else if(n >= 45 && n < 46){
    score = 5;
  }else if(n >= 44 && n < 45){
    score = 4;
  }else if(n >= 43 && n < 44){
    score = 3;
  }else if(n >= 42 && n < 43){
    score = 2;
  }else if(n >= 41 && n < 42){
    score = 1;
  }
  return score;
}

int calcOffensiveReboundingScore(double n){//2
  int score = 0;
  if(n >= 34){
    score = 20;
  }else if(n >= 32 && n < 34){
    score = 18;
  }else if(n >= 30 && n < 32){
    score = 16;
  }else if(n >= 28 && n < 30){
    score = 14;
  }else if(n >= 26 && n < 28){
    score = 12;
  }else if(n >= 24 && n < 26){
    score = 10;
  }else if(n >= 22 && n < 24){
    score = 8;
  }else if(n >= 20 && n < 22){
    score = 6;
  }else if(n >= 18 && n < 20){
    score = 4;
  }else if(n >= 16 && n < 18){
    score = 2;
  }
  return score;
}

int calcDefensiveReboundingScore(double n){//3
  int score = 0;
  if(n >= 86){
    score = 20;
  }else if(n >= 84 && n < 86){
    score = 18;
  }else if(n >= 82 && n < 84){
    score = 16;
  }else if(n >= 80 && n < 82){
    score = 14;
  }else if(n >= 78 && n < 80){
    score = 12;
  }else if(n >= 76 && n < 78){
    score = 10;
  }else if(n >= 74 && n < 76){
    score = 8;
  }else if(n >= 72 && n < 74){
    score = 6;
  }else if(n >= 70 && n < 72){
    score = 4;
  }else if(n >= 68 && n < 70){
    score = 2;
  }
  return score;
}

int calcBlockScore(double n){//4
  int score = 0;
  if(n >= 11){
    score = 10;
  }else if(n >= 10 && n < 11){
    score = 9;
  }else if(n >= 9 && n < 10){
    score = 8;
  }else if(n >= 8 && n < 9){
    score = 7;
  }else if(n >= 7 && n < 8){
    score = 6;
  }else if(n >= 6 && n < 7){
    score = 5;
  }else if(n >= 5 && n < 6){
    score = 4;
  }else if(n >= 4 && n < 5){
    score = 3;
  }else if(n >= 3 && n < 4){
    score = 2;
  }else if(n >= 2 && n < 3){
    score = 1;
  }
  return score;
}

int calcStealsScore(double n){//5
  int score = 0;
  if(n >= 12){
    score = 15;
  }else if(n >= 11 && n < 12){
    score = 14;
  }else if(n >= 10 && n < 11){
    score = 12;
  }else if(n >= 9 && n < 10){
    score = 10;
  }else if(n >= 8 && n < 9){
    score = 9;
  }else if(n >= 7 && n < 8){
    score = 8;
  }else if(n >= 6 && n < 7){
    score = 6;
  }else if(n >= 5 && n < 6){
    score = 5;
  }else if(n >= 4 && n < 5){
    score = 3;
  }else if(n >= 3 && n < 4){
    score = 2;
  }
  return score;
}

int calcTurnoverScore(double n){//6
  int score = 0;
  if(n >= 20){
    score = 1;
  }else if(n >= 19 && n < 20){
    score = 2;
  }else if(n >= 18 && n < 19){
    score = 3;
  }else if(n >= 17 && n < 18){
    score = 4;
  }else if(n >= 16 && n < 17){
    score = 5;
  }else if(n >= 15 && n < 16){
    score = 6;
  }else if(n >= 14 && n < 15){
    score = 7;
  }else if(n >= 13 && n < 14){
    score = 8;
  }else if(n >= 12 && n < 13){
    score = 9;
  }else if(n >= 11 && n < 12){
    score = 10;
  }else if(n >= 10 && n < 11){
    score = 11;
  }
  return score;
}

int calcOpponentShootingScore(double n){//7
  int score = 0;
  if(n >= 51){
    score = 1;
  }else if(n >= 50 && n < 51){
    score = 2;
  }else if(n >= 48 && n < 40){
    score = 3;
  }else if(n >= 47 && n < 48){
    score = 4;
  }else if(n >= 46 && n < 47){
    score = 5;
  }else if(n >= 45 && n < 46){
    score = 6;
  }else if(n >= 44 && n < 45){
    score = 7;
  }else if(n >= 43 && n < 44){
    score = 8;
  }else if(n >= 42 && n < 43){
    score = 9;
  }else if(n >= 41 && n < 42){
    score = 10;
  }
  return score;
}

int calcOpponentOffensiveReboundScore(double n){//8
  int score = 0;
  if(n >= 32 && n < 34){
    score = 2;
  }else if(n >= 30 && n < 32){
    score = 4;
  }else if(n >= 28 && n < 30){
    score = 6;
  }else if(n >= 26 && n < 28){
    score = 8;
  }else if(n >= 24 && n < 26){
    score = 10;
  }else if(n >= 22 && n < 24){
    score = 12;
  }else if(n >= 20 && n < 22){
    score = 14;
  }else if(n >= 18 && n < 20){
    score = 16;
  }else if(n >= 16 && n < 18){
    score = 18;
  }else if(n >= 14 && n < 16){
    score = 20;
  }else if(n >= 12 && n < 14){
    score = 22;
  }
  return score;
}

int calcOpponentTurnoverScore(double n){//9
  int score = 0;
  if(n >= 20){
     score = 11;
   }else if(n >= 19 && n < 20){
     score = 10;
   }else if(n >= 18 && n < 19){
     score = 9;
   }else if(n >= 17 && n < 18){
     score = 8;
   }else if(n >= 16 && n < 17){
     score = 7;
   }else if(n >= 15 && n < 16){
     score = 6;
   }else if(n >= 14 && n < 15){
     score = 5;
   }else if(n >= 13 && n < 14){
     score = 4;
   }else if(n >= 12 && n < 13){
     score = 3;
   }else if(n >= 11 && n < 12){
     score = 2;
   }else if(n >= 10 && n < 11){
     score = 1;
   }
  return score;
}

int calcOpponentPointsPerGame(int n){//10
  int score = 0;
   if(n >= 123){
    score = 2;
   }else if(n >= 120 && n < 123){
     score = 4;
   }else if(n >= 117 && n < 120){
     score = 6;
   }else if(n >= 114 && n < 117){
     score = 8;
   }else if(n >= 111 && n < 114){
     score = 10;
   }else if(n >= 108 && n < 111){
     score = 12;
   }else if(n >= 105 && n < 108){
     score = 14;
   }else if(n >= 102 && n < 105){
     score = 16;
   }else if(n >= 99 && n < 102){
     score = 18;
   }else if(n >= 96 && n < 99){
     score = 20;
   }else if(n >= 93 && n < 96){
     score = 22;
  }
  return score;
}

void NBA::initializeScores()
{
  for(int i = 0; i < hashTableSize; i++)
  {
    if(teamHashTable[i] != nullptr)
    {
      team* p = teamHashTable[i]; //create a pointer towards the current hashTable element
      while(p != nullptr)
      { //For each team -> decide score
        int sum = 0;
        sum += calcPointsPerGameScore(p->pointsPerGame);
        sum += calcShootintPercentageScore(p->shootingPercentage);
        sum += calcOffensiveReboundingScore(p->reboundPercentage);
        sum += calcDefensiveReboundingScore(p->defensiveReboundingPercentage);
        sum += calcBlockScore(p->blockPercentage);
        sum += calcStealsScore(p->stealsPerDefensivePlay);
        sum += calcTurnoverScore(p->turnoversPerPossession);
        sum += calcOpponentShootingScore(p->opponentShootingPercentage);
        sum += calcOpponentOffensiveReboundScore(p->opponentReboundPercentage);
        sum += calcOpponentTurnoverScore(p->opponentTurnoversPerPossessionPercentage);
        sum += calcOpponentPointsPerGame(p->opponentPointsPerGame);
        p->score = sum;
        //each stat has an ID that we use to get data with
        // double pointsPerGame; //ID 0
        // double shootingPercentage; //ID 1
        // double reboundPercentage; //ID 2
        // double defensiveReboundingPercentage;//ID 3
        // double blockPercentage;//ID 4
        // double stealsPerDefensivePlay;//ID 5
        // double turnoversPerPossession;//ID 6
        // double opponentShootingPercentage;//ID 7
        // double opponentReboundPercentage;//ID 8
        // double opponentTurnoversPerPossessionPercentage;//ID 9
        // double opponentPointsPerGame;//ID 10
        p = p->next;
      }
    }
  }
}

int NBA::compareTeams(string team1, string team2)
{
  if(isInTable(team1) && isInTable(team2))
  {
    return(searchTable(team1)->score - searchTable(team2)->score);
  }

  return 9999999;
}

//THESE FUNCTIONS USED TO FIND ALL COMBOS OF TEAMS

/* arr[] ---> Input Array
data[] ---> Temporary array to
store current combination
start & end ---> Staring and
Ending indexes in arr[]
index ---> Current index in temp[]
r ---> Size of a combination to be printed */
void NBA::ppppUtil(team arr[], team temp[], int start, int end, int index)
{
  //int r = 2;
  // Current combination is ready
  // to be printed, print it
  if (index == 2)
  {
    teamComparison t;
    t.t1 = temp[0].name;
    t.t2 = temp[1].name;
    t.spread = compareTeams(t.t1, t.t2);
    if(t.spread >= 0)
    {
      t.t1Wins = true;
    }
    else
    {
      t.t1Wins = false;
      t.spread = -1 * t.spread;
    }
    addToHeap(t);
    return;
  }

  // replace index with all possible
  // elements. The condition "end-i+1 >= 2-index"
  // makes sure that including one element
  // at index will make a combination with
  // remaining elements at remaining positions
  for (int i = start; i <= end && end - i + 1 >= 2 - index; i++)
  {
    temp[index] = arr[i];
    ppppUtil(arr, temp, i + 1, end, index + 1);
  }
}

// The main function that prints
// all combinations of size r
// in arr[] of size n. This function
// mainly uses combinationUtil()
void NBA::getPPPP()
{
  //make a new array and copy all the teams into it
  team arr[numItems];
  int index = 0;
  for(int i = 0; i < hashTableSize; i++)
  {
    if(teamHashTable[i] != nullptr)
    {
      team* p = teamHashTable[i]; //create a pointer towards the current hashTable element
      while(p != nullptr)
      {
        arr[index] = *p;
        index++;
        p = p->next;
      }
    }
  }

  // A temporary array to store
  // all combination one by one
  team temp[2];

  // Print all combination using
  // temprary array 'temp[]'
  ppppUtil(arr, temp, 0, numItems - 1, 0);
}

///////////////////////////
/////  max heap stuff /////
///////////////////////////
/*
Swaps two team Comparisons
*/

void swap(teamComparison *a, teamComparison *b)
{
  teamComparison temp = *a;
  *a = *b;
  *b = temp;
}

void NBA::heapify(int i)
{
  // 'i' is the index to heapify @
  int l = leftChild(i);  // left child index
  int r = rightChild(i); // right child index
  int largest = i;

  if (l < currentSize && heapArr[l].spread > heapArr[i].spread){
    largest = l;
  }
  if (r < currentSize && heapArr[r].spread > heapArr[largest].spread){
    largest = r;
  }
  if (largest != i){
    swap (&heapArr[i], &heapArr[largest]);
    heapify(largest);
  }
}

void NBA::heapSort()
{
  for(int i = capacity / 2 - 1; i >= 0; i--)
  {
    heapify(i);
  }

  for(int i = capacity - 1; i >= 0; i--)
  {
    swap(heapArr[0], heapArr[i]);
    currentSize = i;
    heapify(0);
  }
}

void NBA::addToHeap(teamComparison comparison){
  if(currentSize == capacity)
  {
    cout << "Maximum heap size reached. Cannot insert anymore." <<endl;
    return;
  }

  currentSize = currentSize + 1;
  int index = currentSize - 1;
  heapArr[index] = comparison;

  while (index != 0 && heapArr[parent(index)].spread < heapArr[index].spread)
  {
   swap(&heapArr[index], &heapArr[parent(index)]);
   index = parent(index);
  }

  repairUpward(index);
}

teamComparison* NBA::peekTopComparison(){
  return &heapArr[0];
}

bool NBA::isFull(){
  return currentSize == heapSize;
}

bool NBA::isEmpty(){
  return currentSize == 0;
}

int NBA::parent(int nodeIndex){
  return (nodeIndex / 2 + 1);
}

int NBA::leftChild(int nodeIndex){
  return ((2*nodeIndex) + 1);
}

int NBA::rightChild(int nodeIndex){
  return ((2*nodeIndex) + 2);
}

void NBA::repairUpward(int nodeIndex){
  int p = parent(nodeIndex);
  int largest = nodeIndex;

  if(heapArr[p].spread < heapArr[nodeIndex].spread){
    swap (&heapArr[nodeIndex], &heapArr[p]);
    repairUpward(p);
  }
}

void NBA::repairDownward(int nodeIndex){
  // 'nodeIndex' is the index to heapify @
  int l = leftChild(nodeIndex);  // left child index
  int r = rightChild(nodeIndex); // right child index
  int largest = nodeIndex;

  if (l < currentSize && heapArr[l].spread > heapArr[nodeIndex].spread){
    largest = l;
  }
  if (r < currentSize && heapArr[r].spread > heapArr[largest].spread){
    largest = r;
  }
  if (largest != nodeIndex){
    swap (&heapArr[nodeIndex], &heapArr[largest]);
    repairDownward(largest);
  }
}

void NBA::printTopNMatchups(int n)
{
  int counter = 0;
  for(int i = capacity - 1; i >= 435 - n; i--)
  {
    counter++;
    cout << "#" << counter << ":" << endl;
    cout << heapArr[i].t1 << " vs " << heapArr[i].t2 << endl;
    if(heapArr[i].t1Wins)
    {
      cout << "Predicted Winner: " << heapArr[i].t1 << endl;
      cout << "Predicted Loser: " << heapArr[i].t2 << endl;
    }
    else
    {
      cout << "Predicted Winner: " << heapArr[i].t2 << endl;
      cout << "Predicted Loser: " << heapArr[i].t1 << endl;
    }
    cout << "Spread: " << heapArr[i].spread << endl;
    cout << "Game Evaluation: ";
    if(heapArr[i].spread > 0 && heapArr[i].spread <= 15){
      cout << "Close Game | No Bet" << endl;
    }else if(heapArr[i].spread > 15 && heapArr[i].spread <= 30){
      cout << "Good Game | Maybe Bet" << endl;
    }else if(heapArr[i].spread > 30 && heapArr[i].spread <= 60){
      cout << "Great Game | Could Bet" << endl;
    }else if(heapArr[i].spread > 60){
      cout << "Awesome Game | Should Bet" << endl;
    }
    cout << endl;
  }
}

void NBA::printSpreadAboveN(int n)
{
  int counter = 0;
  for(int i = capacity - 1; i >= 0; i--)
  {
    if(heapArr[i].spread >= n)
    {
      counter++;
      cout << "#" << counter << ":" << endl;
      cout << heapArr[i].t1 << " vs " << heapArr[i].t2 << endl;
      if(heapArr[i].t1Wins)
      {
        cout << "Predicted Winner: " << heapArr[i].t1 << endl;
        cout << "Predicted Loser: " << heapArr[i].t2 << endl;
      }
      else
      {
        cout << "Predicted Winner: " << heapArr[i].t2 << endl;
        cout << "Predicted Loser: " << heapArr[i].t1 << endl;
      }
      cout << "Spread: " << heapArr[i].spread << endl;
      cout << "Game Evaluation: ";
      if(heapArr[i].spread > 0 && heapArr[i].spread <= 15){
        cout << "Close Game | No Bet" << endl;
      }else if(heapArr[i].spread > 15 && heapArr[i].spread <= 30){
        cout << "Good Game | Maybe Bet" << endl;
      }else if(heapArr[i].spread > 30 && heapArr[i].spread <= 60){
        cout << "Great Game | Could Bet" << endl;
      }else if(heapArr[i].spread > 60){
        cout << "Awesome Game | Should Bet" << endl;
      }
      cout << endl;
      }
  }
}

string NBA::getMonth()
{
      time_t tt;
      struct tm * ti;
      time (&tt);
      ti = localtime(&tt);
      string date = asctime(ti);
      //cout << date.substr(8, 2) << endl;
      return date.substr(4, 3);
}

string NBA::getDay()
{
      time_t tt;
      struct tm * ti;
      time (&tt);
      ti = localtime(&tt);
      string date = asctime(ti);
      return date.substr(8, 2);
      //return date.substr(4, 3);
}

bool NBA::upcomingGameAlreadyExists(string team1, string team2)
{
  for(int i = 0; i < upcomingGames.size(); i++)
  {
    if((upcomingGames[i].t1 == team1 && upcomingGames[i].t2 == team2) ||
    (upcomingGames[i].t1 == team2 && upcomingGames[i].t2 == team1))
    { //if the team combo already exists
      return true;
    }
  }
  return false;
}

void NBA::initializeUpcomingGames(string url)
{ // url = "https://www.teamrankings.com/nba/schedules/season/";

  bool passedDate = false;
  ifstream myfilestream;
  myfilestream.open(downloadURL(url, "fileOPT"));
  if (myfilestream.is_open()) //check if the stream is open
  {
    string line = "";
    while (getline(myfilestream, line)) //while there are more lines to be added
    {
      string date;
      string team1;
      string team2;

      if(!passedDate && line.find(getMonth()) != -1 && stoi(line.substr(line.find("40%") + 14, 2)) >= stoi(getDay())) //if the line contains today's date
      {
        passedDate = true; //set passedDate to true
      }

      if(passedDate && line.find("text-left nowrap sort-asc-first\"") != -1 &&
      line.find("Location") == -1) //we're at or passed today's date, so pull in games!
      { //We have found a line that contains the date

        date = line.substr(line.find("40%") + 6, 10);

        for(int i = 0; i < 7; i++)
        {
          getline(myfilestream, line);
        }

        //now we're on the line containing name
        //int aIndex = line.find("a href");
        int name1index = line.find(">", line.find("a href")) + 1;
        int name1end = line.find("@") - name1index - 2;
        team1 = line.substr(name1index, name1end);

        int team2end = line.find("<", line.find("@")) - line.find("@") - 3;
        team2 = line.substr(line.find("@") + 3, team2end);

        teamComparison newGame;
        newGame.t1 = team1;
        newGame.t2 = team2;

        newGame.spread = compareTeams(team1, team2);

        if(upcomingGameAlreadyExists(team1, team2))
        {
          newGame.TBD = true;
        }
        else
        {
          newGame.TBD = false;
        }

        if(newGame.spread >= 0)
        {
          newGame.t1Wins = true;
        }
        else
        {
          newGame.t1Wins = false;
          newGame.spread = -1 * newGame.spread;
        }
        newGame.date = date;

        upcomingGames.push_back(newGame);
      }
    }
  }
  else //if it couldn't be opened, print this
  {
      cout << "Failed to open the file." << endl;
  }
  myfilestream.close(); //close the file stream
}

void NBA::printUpcomingGames(int n)
{
  for(int i = 0; i < upcomingGames.size() && i < n; i++)
  {
    printTeamComparison(upcomingGames[i]);
  }
}

void NBA::printUpcomingGamesWithSpreadAboveN(int spreadThreshold)
{
  for(int i = 0; i < upcomingGames.size(); i++)
  {
    if( upcomingGames[i].spread >= spreadThreshold)
    {
      printTeamComparison(upcomingGames[i]);
    }
  }
}

void NBA::printTeamComparison(teamComparison tc)
{
  cout << "===" << tc.date << "===" << endl;
  cout << tc.t1 << " vs " << tc.t2 << endl;
  cout << "Predicted winner: ";

  if(tc.t1Wins)
  {
    cout << tc.t1 << endl;
  }
  else
  {
    cout << tc.t2 << endl;
  }

  if(tc.TBD)
  {
    cout << "Spread: TBD -> predicted: " << tc.spread << endl;
  }
  else
  {
    cout << "Spread: " << tc.spread << endl;
  }

  cout << "Game Evaluation: ";

  if (tc.spread > 0 && tc.spread <= 15)
  {
    cout << "Bad Bet" << endl;
  }
  else if (tc.spread > 10 && tc.spread <= 30)
  {
    cout << "Iffy Bet" << endl;
  }
  else if (tc.spread > 30 && tc.spread <= 55)
  {
    cout << "Good Bet" << endl;
  }
  else if(tc.spread > 55)
  {
    cout << "GREAT Bet" << endl;
  }

  cout << endl;
}

/*void NBA::printNextNGames(int n)
{

}*/
