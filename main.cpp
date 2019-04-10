#include "NBA.hpp"


void displayMenu()
{
  cout << "===Main Menu===" << endl;
  cout << "1. Intialize database from the web" << endl;
  cout << "2. Team lookup" << endl;
  cout << "3. Compare two teams" << endl;
  cout << "4. Determine current best team" << endl;
  cout << "5. Quit" << endl;
}

int main()
{
  cout << "=== NBA Analyzer ===" << endl;
  cout << "By Alex Israelov, Ryan Horn, and some kid Dan" << endl;
  cout << "All data is pulled from TeamRankings.com who wouldn't give us an API. Dicks.\n" << endl;

  NBA myNBA(30);
  cout << "Downloading team stats. Please wait." << endl;
  myNBA.initializeRoster();
  myNBA.printAllTeams();

  return 0;
}
