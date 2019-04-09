#include "NBA.hpp"




int main()
{

//EARLY PARSER
/*
  cout << "downloading via wget..." << endl;
  system("wget https://www.teamrankings.com/nba/ -q");
  rename("index.html", "teamrankingspage1");
  cout << "download complete!" << endl;

  ifstream myfilestream;
  myfilestream.open("teamrankingspage1"); //argv[1] is the second command line argument
  if (myfilestream.is_open()) //check if the stream is open
  {
      string line = "";
      while (getline(myfilestream, line)) //while there are more lines to be added
      {
          if(line.find("text-center") != -1 || line.find("text-right") != -1 || line.find("table-team-logo-text") != -1) //disregard empty lines, or those that are a stop word
          {
            cout << line << endl;
          }
      }
  }
  else //if it couldn't be opened, print this
  {
      cout << "Failed to open the file." << endl;
  }
  myfilestream.close(); //close the file stream
  */





  NBA myNBA(30);
  myNBA.setTeamNames(); //initialize all the teams into the array
  //myNBA.printAllTeams(); //print all teams in hashTable;
  cout << "initialize all stats" << endl;
  myNBA.initializeAllStats();
  myNBA.printAllTeams();

  return 0;
}
