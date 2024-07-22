#pragma once
#include <string>

using namespace std;

// Reads the content of the inserted file and reads it into the string
class FileReader
{
public:
  explicit FileReader (const string &filename);

  // Read the file given during constructor of the class and return it as the
  // string value
  string read () const;

private:
  const string filename;
};