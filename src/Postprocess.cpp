#include "Postprocess.hpp"
#include "FileReader.hpp"
#include <iostream>
#include <sstream>

Postprocess::Postprocess (const std::string &inputFile,
                          const std::string &outputFolder)
    : inputFile (inputFile), outputFolder (outputFolder)
{
  std::cout << "Input file: " + inputFile << std::endl;
  std::cout << "Output folder: " + outputFolder << std::endl;
}

void
Postprocess::process ()
{
  FileReader reader (inputFile);
  inputFileContent = reader.read ();

  // stream input data
  std::istringstream stream (inputFileContent);

  // parse input data string to vector lines
  while (std::getline (stream, line))
    {
      inputLines.push_back (line);
    }

  std::cout << "Lines count: " + std::to_string (inputLines.size ())
            << std::endl;

  // evaluate every line
  for (const auto &line : inputLines)
    {
      // Process every single line from input line
      // std::cout << line << std::endl;
    }
}