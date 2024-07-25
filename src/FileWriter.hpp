#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

// Write final files
class FileWriter
{
public:
  explicit FileWriter (const string &fileNamePrefix,
                       const string &outputFolder, const string &projectPath);
  void write (const string &fileType, vector<vector<string> > &content);
  void createEmptyFile (string filename);
  void createMainFiles ();

private:
  const string filenamePrefix;
  const string outputFolder;
  const string projectPath;
  string completePath;
  vector<vector<string> > outputContent;
  int numberOfFiles;
};