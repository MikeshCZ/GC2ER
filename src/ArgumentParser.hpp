#pragma once
#include <string>

// Parse arguments from exec file
// -i, --inputFile    Input Gcode file
// -o, --outputFolder   Output files folder
class ArgumentParser
{
public:
  // Parse arguments from exec file
  void parse (int argc, char *argv[]);

  // -i, --inputFile  Input Gcode file
  std::string getInputFile () const;

  // -o, --outputFolder   Output files prefix
  std::string getOutputFolder () const;

private:
  std::string inputFile;
  std::string outputFolder;
};