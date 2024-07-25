#pragma once
#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class GcodeProcess
{
public:
  GcodeProcess ();
  pair<string, string> process (const string &inputLine);

private:
  stringstream erdProcess (unordered_map<char, double> &values) const;
  int cpos;
};