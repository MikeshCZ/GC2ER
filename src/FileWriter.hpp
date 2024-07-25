#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FileWriter
{
public:
  explicit FileWriter (const string &fileNamePrefix,
                       const string &outputFolder, const string &projectPath);
  void write (const string &fileType, vector<vector<string> > &content) const;

private:
  const string filenamePrefix;
  const string outputFolder;
  const string projectPath;
  vector<vector<string> > outputContent;
};