#include "FileWriter.hpp"

FileWriter::FileWriter (const string &fileNamePrefix,
                        const string &outputFolder, const string &projectPath)
    : filenamePrefix (fileNamePrefix), outputFolder (outputFolder),
      projectPath (projectPath)
{
}

void
FileWriter::write (const string &fileType, vector<vector<string> > &content)
{
  numberOfFiles = 0;

  completePath
      = outputFolder + "/" + projectPath + "/" + filenamePrefix + ".er";

  // Create a directory if it does not exist
  filesystem::path dirPath = filesystem::path (completePath);
  if (!filesystem::exists (dirPath))
    {
      filesystem::create_directories (dirPath);
      cout << "Creating folders: " << completePath << endl;
    }

  // Writing procedure
  for (size_t i = 0; i < content.size (); ++i)
    {
      ofstream outFile (completePath + "/" + filenamePrefix + "_"
                        + to_string (i) + "." + fileType);

      // Add Start: if it is ERP file on the beginning of the file
      if (fileType == "erp")
        {
          outFile << "Start:" << endl;
        }

      // Add lines to the file
      for (const auto &line : content[i])
        {
          outFile << line << endl;
        }

      // Add End: if it is ERP file on the end of the file
      if (fileType == "erp")
        {
          outFile << "End;";
        }
      numberOfFiles++;
      outFile.close ();
    }

  cout << "Writing of the " << numberOfFiles << " " << fileType
       << " files completed to " << completePath << "." << endl;
}

void
FileWriter::createEmptyFile (string filename)
{
  // Create an output file stream object
  ofstream file (completePath + "/" + filename);

  // Check if the file was created successfully
  if (file.is_open ())
    {
      cout << "File '" << filename << "' created successfully." << std::endl;
      // Close the file
      file.close ();
    }
  else
    {
      cerr << "Error creating file '" << filename << "'." << std::endl;
    }
}

void
FileWriter::createMainFiles ()
{
  createEmptyFile ((filenamePrefix + ".erd"));
  ofstream outFile (completePath + "/" + filenamePrefix + ".erp");
  outFile << "Start:" << endl;
  for (size_t i = 0; i < numberOfFiles; ++i)
    {
      outFile << "CALL " << filenamePrefix << "_" << to_string (i) << endl;
    }
  outFile << "End;";
  outFile.close ();
}
