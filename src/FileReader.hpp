#pragma once
#include <string>

// Reads the content of the inserted file and reads it into the string
class FileReader
{
public:
  explicit FileReader (const std::string &filename);

  // Read the file given during constructor of the class and return it as the
  // string value
  std::string read () const;

private:
  const std::string filename;
};