#pragma once
#include <string>
#include <vector>

using namespace std;

class PostProcess
{
public:
  PostProcess (const string &inputFile, const string &outputFolder);
  void process ();
  void splitIntoChunks (vector<string> &inputLines,
                        vector<vector<string> > &outputLines,
                        size_t chunkSize);

private:
  const string inputFile;
  const string outputFolder;
  string inputFileContent;
  vector<string> inputLines;
  vector<string> tempLines;
  string line;
  vector<vector<string> > outputLines;
};