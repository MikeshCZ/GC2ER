#include "FileReader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

FileReader::FileReader (const string &filename) : filename (filename) {}

string
FileReader::read () const
{
  // create an input file stream object
  ifstream file (filename);

  try
    {
      // catch error if the file cannot be opened
      if (!file.is_open ())
        {
          throw runtime_error ("Could not open file: " + filename);
        }

      // read and return the contect of the file to the string
      stringstream buffer;
      buffer << file.rdbuf ();
      file.close ();
      cout << "File '" << filename << "' succesfully loaded." << endl;
      return buffer.str ();
    }
  catch (const exception &e)
    {
      file.close ();
      cerr << e.what () << '\n';
    }
}