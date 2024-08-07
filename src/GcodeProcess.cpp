#include "GcodeProcess.hpp"

using namespace std;

GcodeProcess::GcodeProcess () : cpos (0) {}

pair<string, string>
GcodeProcess::process (const string &inputLine)
{
  // No Gcode command -> SKIP
  if (inputLine[0] != 'G')
    {
      cout << "Input line skipped: " << inputLine << endl;
      return { "", "" };
    }

  // set up local variables
  stringstream erd;
  stringstream erp;
  unordered_map<char, double> values;
  stringstream ss (inputLine);
  string segment;

  // Pharse inputLine to unordered_map<char, double> values
  while (getline (ss, segment, ' '))
    {
      char key = segment[0];
      double value = std::stod (segment.substr (1));
      values[key] = value;
    }

  // Switch based on Gcode command
  switch (static_cast<int> (values['G']))
    {
    case 0: // G00: Rapid positioning
      // ERD data composition
      erd = erdProcess (values);

      // ERP program composition
      erp << "MovJ{P=t_l.CPOS";
      erp << cpos;
      erp << ", Coord = t_g.USERCOOR0}";

      cpos++;
      return { erd.str (), erp.str () };
      break;

    case 1: // G01: Linear interpolation (straight line)
      // ERD data composition
      erd = erdProcess (values);

      // ERP program composition
      erp << "MovL{P=t_l.CPOS";
      erp << cpos;
      erp << ", Coord = t_g.USERCOOR0}";

      cpos++;
      return { erd.str (), erp.str () };
      break;

    case 2: // G02: Circular interpolation, clockwise
      return { "", "" };
      break;

    case 3: // G02: Circular interpolation, clockwise
      return { "", "" };
      break;

    case 4: // G04: Dwell (pause for a specified time)
      return { "", "" };
      break;

    case 28: // G28: Return to home position
      return { "", "" };
      break;

    default: // unknown G code line -> skip
      cout << "Input line skipped (unknow Gcode command): " << inputLine << endl;
      return { "", "" };
      break;
    }
}

stringstream
GcodeProcess::erdProcess (unordered_map<char, double> &values) const
{
  stringstream erd;

  erd << "CPOS";
  erd << cpos;
  erd << "={_type=\"CPOS\",confdata={_type=\"POSCFG\",mode=0,cf1="
         "0,cf2=0,cf3=0,cf4=0,cf5=0,cf6=0},";
  erd << fixed << setprecision (6);
  erd << "x=" << values['X'] << ",";
  erd << "y=" << values['Y'] << ",";
  erd << "z=" << values['Z'] << ",";
  erd << "a=" << 180 << ",";
  erd << "b=" << 0 << ",";
  erd << "c=" << 0 << ",";
  erd << "a7=0.000000,a8=0.000000,a9=0.000000,a10=0.000000,a11=0."
         "000000,a12=0.000000,a13=0.000000,a14=0.000000,a15=0.000000,"
         "a16=0.000000}";

  return erd;
}