#include "ArgumentParser.hpp"
#include "PostProcess.hpp"
#include <iostream>
#include <string>

using namespace std;

int
main (int argc, char *argv[])
{
  cout << "GC2ER - Gcode To Estun Robot" << endl;
  cout << endl;

  // Get input and output files
  ArgumentParser parser;
  parser.parse (argc, argv);

  string inputFile = parser.getInputFile ();
  string outputFolder = parser.getOutputFolder ();

  // If no arguments, print help
  if (inputFile.empty ())
    {
      cout << "Arguments:" << endl;
      cout << "-i, --inputFile <file>      Input Gcode file (required)"
                << endl;
      cout
          << "-o, --inputFolder <folder>  Output folder for program files"
          << endl;
      return 1;
    }

  PostProcess postprocess (inputFile, outputFolder);
  postprocess.process ();

  return 0;
}