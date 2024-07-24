#pragma once
#include "FileReader.hpp"
#include "GcodeProcess.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Post process GCODE to Estun Robotics
class PostProcess
{
public:
  PostProcess (const string &inputFile, const string &outputFolder);

  // Processing the input gcode file
  void process ();

private:
  // Splitting the input string vector into output vectors divided into
  // subvectors according to chunkSize
  void splitIntoChunks (vector<string> &inputLines,
                        vector<vector<string> > &outputLines,
                        size_t chunkSize);
  const string inputFile;
  const string outputFolder;
};