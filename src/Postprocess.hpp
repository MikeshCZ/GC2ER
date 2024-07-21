#pragma once
#include <string>
#include <vector>

class Postprocess
{
public:
  Postprocess (const std::string &inputFile, const std::string &outputFolder);
  void process ();

private:
  const std::string inputFile;
  const std::string outputFolder;
  std::string inputFileContent;
  std::vector<std::string> inputLines;
  std::string line;
};