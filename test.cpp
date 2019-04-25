#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <vector>
#include "curlIN/curl.h"
using namespace std;

string getDay()
{
      time_t tt;
      struct tm * ti;
      time (&tt);
      ti = localtime(&tt);
      string date = asctime(ti);
      return date.substr(0, 10);
}

int main()
{
cout << getDay() << endl;
}
