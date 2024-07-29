#include "ArgumentParser.hpp"
#include <iostream>

ArgumentParser::ArgumentParser ()
    : inputFolderProvided (false), outputFolderProvided (false)
{
}

void
ArgumentParser::parse (int argc, char *argv[])
{
  for (int i = 1; i < argc; ++i)
    {
      string arg = argv[i];
      if ((arg == "-i" || arg == "--inputFile") && i + 1 < argc)
        {
          inputFile = argv[++i];
          inputFolderProvided = true;
        }
      else if ((arg == "-o" || arg == "--outputFolder") && i + 1 < argc)
        {
          outputFolder = argv[++i];
          outputFolderProvided = true;
        }
      else if ((arg == "-s" || arg == "--chunkSize") && i + 1 < argc)
        {
          string temp = argv[++i];
          if (isValidNumber (temp))
            {
              chunkSize = stoi (temp);
              chunkSizeProvided = true;
            }
        }
      else
        {
          cerr << "Invalid argument: " << arg << std::endl;
        }
    }
}

string
ArgumentParser::getInputFile ()
{
  if (!inputFolderProvided)
    {
      cerr << "Input file is empty!" << std::endl;
    }

  return inputFile;
}

string
ArgumentParser::getOutputFolder ()
{
  if (outputFolderProvided)
    {
      // Check if it is not empty and the last character is '/', it will remove
      // it
      if (!outputFolder.empty () && outputFolder.back () == '/')
        {
          outputFolder.pop_back ();
        }

      return outputFolder;
    }
  else
    {
      // If the -o argument was not used, it returns the default value 'out'
      return "out";
    }
}

int
ArgumentParser::getChunkSize ()
{
  if (chunkSizeProvided)
    {
      return chunkSize;
    }
  else
    {
      return 500;
    }
}

bool
ArgumentParser::isValidNumber (const std::string &str)
{
  try
    {
      int num = std::stoi (str);
      if (num >= 1 && num <= 990)
        {
          return true;
        }
    }
  catch (const std::invalid_argument &e)
    {
      cerr << "The chunkSize value entered is not a valid number." << endl;
    }
  catch (const std::out_of_range &e)
    {
      cerr << "The chunkSize value is outside the range of 1-990." << endl;
    }
  return false;
}