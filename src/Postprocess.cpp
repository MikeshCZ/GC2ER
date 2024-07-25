#include "PostProcess.hpp"

PostProcess::PostProcess (const string &inputFile, const string &outputFolder)
    : inputFile (inputFile), outputFolder (outputFolder)
{

  outputFileName = getFileNameWithoutExtension (inputFile);

  cout << "Input file: " + inputFile << endl;
  cout << "Output file name: " + outputFileName << endl;
  cout << "Output folder: " + outputFolder << endl;
}

void
PostProcess::process ()
{
  // local variables
  vector<string> inputLines;
  string line;
  vector<string> tempERP;
  vector<string> tempERD;
  vector<vector<string> > outputERP;
  vector<vector<string> > outputERD;

  // read the input file
  FileReader reader (inputFile);
  string inputFileContent = reader.read ();

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
      auto [erd, erp] = gcode.process (line);

      // if there is the output from gcode process push to temp vector strings
      if (erd != "" or erp != "")
        {
          tempERD.push_back (erd);
          tempERP.push_back (erp);
        }

      // DEBUG ONLY
      // cout << "ERD:" << endl << erd << endl;
      // cout << "ERP:" << endl << erp << endl << endl;
    }

  // split into chunks
  splitIntoChunks (tempERP, outputERP, 950);
  splitIntoChunks (tempERD, outputERD, 950);

  // Write to the ouput files
  FileWriter writer (outputFileName, outputFolder, "GC2ER/Project");
  writer.write ("erp", outputERP);
  writer.write ("erd", outputERD);
  writer.createEmptyFile ("prjglobal.erd");
  writer.createMainFiles ();
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

string
PostProcess::getFileNameWithoutExtension (const string &path)
{
  // Získání jména souboru z cesty pomocí <filesystem>
  filesystem::path p = path;
  string filename = p.filename ().string ();

  // Najděte poslední tečku v jménu souboru
  size_t lastDot = filename.find_last_of ('.');
  if (lastDot == string::npos)
    {
      // Pokud tečka nebyla nalezena, soubor nemá příponu
      return filename;
    }
  // Vraťte část řetězce před poslední tečkou
  return filename.substr (0, lastDot);
}