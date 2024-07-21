#include "ArgumentParser.hpp"
#include "Postprocess.hpp"
#include <iostream>
#include <string>

int
main (int argc, char *argv[])
{
  std::cout << "GC2ER - Gcode To Estun Robot" << std::endl;
  std::cout << std::endl;

  // Get input and output files
  ArgumentParser parser;
  parser.parse (argc, argv);

  std::string inputFile = parser.getInputFile ();
  std::string outputFolder = parser.getOutputFolder ();

  // If no arguments, print help
  if (inputFile.empty ())
    {
      std::cout << "Arguments:" << std::endl;
      std::cout << "-i, --inputFile <file>      Input Gcode file (required)"
                << std::endl;
      std::cout
          << "-o, --inputFolder <folder>  Output folder for program files"
          << std::endl;
      return 1;
    }

  Postprocess postprocess (inputFile, outputFolder);
  postprocess.process ();

  return 0;
}