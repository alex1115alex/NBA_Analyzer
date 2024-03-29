#include "NBA.hpp"


void displayMenu()
{
  cout << "\n===Main Menu===" << endl;
  cout << "1. Rebuild database from the web" << endl;
  cout << "2. List all teams" << endl;
  cout << "3. Team lookup" << endl;
  cout << "4. Compare two teams" << endl;
  cout << "5. Print current best team" << endl;
  cout << "6. Determine top N matchups" << endl;
  cout << "7. Print matchups with spread above threshold" << endl;
  cout << "8. Print upcoming games" << endl;
  cout << "9. Print upcoming games with spread above theshold" << endl;
  cout << "10. Quit" << endl;
}

int main()
{
  NBA myNBA(30);

  cout << "=== NBA Analyzer ===" << endl;
  cout << "By Alex Israelov, Ryan Horn, and Daniel Vignanker" << endl;
  cout << "All data is pulled from TeamRankings.com\n" << endl;
  cout << "Downloading data....." << endl;
  myNBA.initializeRoster();

  string choice = "11";
  string line1 = "";
  string line2 = "";
  int compare = 0;
  while(stoi(choice) != 10)
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
      //myNBA.getPPPP();
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
        else if(compare < 0)
        {
          cout << line2 << " is " << -1 * compare << " points better than " << line1 << endl;
        }
        else
        {
          cout << line1 << " is approximately equal to " << line2 << endl;
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
      cout << "How many top matchups to print?" << endl;
      getline(cin, line1);
      myNBA.heapSort();
      if(stoi(line1) > 420)
      {
        line1 = "420"; //dude weed lmao
      }
      myNBA.printTopNMatchups(stoi(line1));
      break;
      case 7:
      cout << "Enter spread threshold: " << endl;
      getline(cin, line1);
      myNBA.printSpreadAboveN(stoi(line1));
      break;
      case 8:
      cout << "Enter number of games to print: " << endl;
      getline(cin, line1);
      myNBA.printUpcomingGames(stoi(line1));
      break;
      case 9:
      cout << "Enter spread threshold: " << endl;
      getline(cin, line2);
      myNBA.printUpcomingGamesWithSpreadAboveN(stoi(line2));
      break;
      case 10:
      cout << "Goodbye" << endl;
      break;
      default:
      cout << "Invalid option" << endl;
      break;
    }
  }

  return 0;
}
