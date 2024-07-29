#pragma once
#include <string>

using namespace std;

// Parse arguments from exec file
// -i, --inputFile    Input Gcode file
// -o, --outputFolder   Output files folder
class ArgumentParser
{
public:
  ArgumentParser ();
  // Parse arguments from exec file
  void parse (int argc, char *argv[]);

  // -i, --inputFile  Input Gcode file
  string getInputFile ();

  // -o, --outputFolder   Output files prefix
  string getOutputFolder ();

  // -s, --chunkSize  number of lines in one file
  int getChunkSize ();

private:
  bool isValidNumber (const std::string &str);
  string inputFile;
  string outputFolder;
  int chunkSize;
  bool inputFolderProvided;
  bool outputFolderProvided;
  bool chunkSizeProvided;
};