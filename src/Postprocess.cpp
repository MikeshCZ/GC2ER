#include "PostProcess.hpp"
#include "FileReader.hpp"
#include "GcodeProcess.hpp"
#include <iostream>
#include <sstream>

PostProcess::PostProcess (const string &inputFile, const string &outputFolder)
    : inputFile (inputFile), outputFolder (outputFolder)
{
  cout << "Input file: " + inputFile << endl;
  cout << "Output folder: " + outputFolder << endl;
}

void
PostProcess::process ()
{
  FileReader reader (inputFile);
  inputFileContent = reader.read ();

  // stream input data
  istringstream stream (inputFileContent);

  // parse input data string to vector lines
  while (getline (stream, line))
    {
      inputLines.push_back (line);
    }

  cout << "Lines count: " + to_string (inputLines.size ()) << endl;

  // evaluate every line with Gcode postprocessor
  GcodeProcess gcode;

  for (const auto &line : inputLines)
    {
      // Process every single line from input line
      tempLines.push_back (gcode.process (line));
      // cout << line << endl;
    }

  splitIntoChunks (tempLines, outputLines, 950);
}

void
PostProcess::splitIntoChunks (vector<string> &inputLines,
                              vector<vector<string> > &outputLines,
                              size_t chunkSize)
{
  size_t totalLines = inputLines.size ();

  // round up to the nearest integer
  size_t numChunks = (totalLines + chunkSize - 1) / chunkSize;

  // Reserve space for the outer vector to improve performance
  outputLines.reserve (numChunks);

  for (size_t i = 0; i < totalLines; i += chunkSize)
    {
      size_t end = min (i + chunkSize, totalLines);
      outputLines.emplace_back (inputLines.begin () + i,
                                inputLines.begin () + end);
    }
}