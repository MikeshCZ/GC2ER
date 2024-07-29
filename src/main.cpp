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
  int chunkSize = parser.getChunkSize ();

  // If no arguments, print help
  if (inputFile.empty ())
    {
      cout << "Arguments:" << endl;
      cout << "-i, --inputFile <file>      Input Gcode file (required)"
           << endl;
      cout << "-o, --inputFolder <folder>  Output folder for program files. Default is 'out'."
           << endl;
      cout << "-s, --chunkSize <intiger>  Size of the lines in one program file. Range 1 - 990. Default is '900'."
           << endl;
      return 1;
    }

  PostProcess postprocess (inputFile, outputFolder, chunkSize);
  postprocess.process ();

  // The End
  cout << endl;
  cout << "Program finished." << endl;
  return 0;
}