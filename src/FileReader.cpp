#include "FileReader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

FileReader::FileReader (const std::string &filename) : filename (filename) {}

std::string
FileReader::read () const
{
  // create an input file stream object
  std::ifstream file (filename);

  try
    {
      // catch error if the file cannot be opened
      if (!file.is_open ())
        {
          throw std::runtime_error ("Could not open file: " + filename);
        }

      // read and return the contect of the file to the string
      std::stringstream buffer;
      buffer << file.rdbuf ();
      file.close ();
      std::cout << "File '" << filename << "' succesfully loaded."
                << std::endl;
      return buffer.str ();
    }
  catch (const std::exception &e)
    {
      file.close ();
      std::cerr << e.what () << '\n';
    }
}