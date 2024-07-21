#include "ArgumentParser.hpp"
#include <iostream>

void
ArgumentParser::parse (int argc, char *argv[])
{
  for (int i = 1; i < argc; ++i)
    {
      std::string arg = argv[i];
      if ((arg == "-i" || arg == "--inputFile") && i + 1 < argc)
        {
          inputFile = argv[++i];
        }
      else if ((arg == "-o" || arg == "--outputFolder") && i + 1 < argc)
        {
          outputFolder = argv[++i];
        }
      else
        {
          std::cerr << "Invalid argument: " << arg << std::endl;
        }
    }
}

std::string
ArgumentParser::getInputFile () const
{
  return inputFile;
}

std::string
ArgumentParser::getOutputFolder () const
{
  return outputFolder;
}