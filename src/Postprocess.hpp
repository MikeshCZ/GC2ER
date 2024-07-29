#pragma once
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "GcodeProcess.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Post process GCODE to Estun Robotics
class PostProcess
{
public:
  PostProcess (const string &inputFile, const string &outputFolder,
               const int &chunkSize);

  // Processing the input gcode file
  void process ();

private:
  // Splitting the input string vector into output vectors divided into
  // subvectors according to chunkSize
  void splitIntoChunks (vector<string> &inputLines,
                        vector<vector<string> > &outputLines,
                        size_t chunkSize);
  string getFileNameWithoutExtension (const string &path);
  const string inputFile;
  const string outputFolder;
  const int chunkSize;
  string outputFileName;
};