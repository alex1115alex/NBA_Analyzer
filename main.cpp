#include "NBA.hpp"


void displayMenu()
{
  cout << "\n===Main Menu===" << endl;
  cout << "1. Intialize database from the web" << endl;
  cout << "2. List all teams" << endl;
  cout << "3. Team lookup" << endl;
  cout << "4. Compare two teams" << endl;
  cout << "5. Determine current best team" << endl;
  cout << "6. Quit" << endl;
}

int main()
{
  NBA myNBA(30);

  cout << "=== NBA Analyzer ===" << endl;
  cout << "By Alex Israelov, Ryan Horn, and some kid Dan" << endl;
  cout << "All data is pulled from TeamRankings.com who wouldn't give us an API. Dicks.\n" << endl;

  string choice = "11";
  string line1 = "";
  string line2 = "";
  int compare = 0;
  while(stoi(choice) != 6)
  {
    displayMenu();
    getline(cin, choice);
    switch(stoi(choice))
    {
      case 1:
      //initializeRoster
      cout << "Downloading team stats. Please wait." << endl;
      myNBA.initializeRoster();
      cout << "Database successfully initialized!" << endl;
      break;
      case 2:
      //list all team names
      myNBA.printNames();
      break;
      case 3:
      //team lookup
      cout << "Enter a team name:" << endl;
      getline(cin, line1);
      cout << endl;
      myNBA.printTeam(line1);
      break;
      case 4:
      //compare two teams
      cout << "Enter the first team name:" << endl;
      getline(cin, line1);
      cout << "Enter the second team name:" << endl;
      getline(cin, line2);
      if(myNBA.isInTable(line1) && myNBA.isInTable(line2))
      {
        compare = myNBA.compareTeams(line1, line2);
        if(compare > 0)
        {
          cout << line1 << " is " << compare << " points better than " << line2 << endl;
        }
        else
        {
          cout << line2 << " is " << -1 * compare << " points better than " << line1 << endl;
        }
      }
      else
      {
        cout << "Team(s) are invalid" << endl;
      }
      break;
      case 5:
      //determine best team
      cout << myNBA.getBestTeam()->name << " is the best team with a score of " << myNBA.getBestTeam()->score << "." << endl;
      break;
      case 6:
      cout << "BYEBYE" << endl;
      break;
      default:
      cout << "Invalid option" << endl;
      //myNBA.printAllTeams();
      break;
    }
  }

  return 0;
}
