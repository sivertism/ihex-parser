/*
 * IntelHexFile.h
 * Created by Brent Strysko
 *
 * A IntelHexFile represents the
 * *.hex file provided to the library.
 */

#ifndef _INTEL_HEX_PARSER_INTEL_HEX_FILE_H_
#define _INTEL_HEX_PARSER_INTEL_HEX_FILE_H_

#include <stdint.h>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "IntelHexFileEntry.hpp"
#include "Program.hpp"

using namespace std;

#define INTEL_HEX_FILE_MAX_ENTRY_SIZE 524

class IntelHexFile {
 private:
  map<uint32_t, IntelHexFileEntry> addressToFileEntries;

 public:
  IntelHexFile(string filename);

  Program getProgram();

  vector<pair<uint32_t, vector<uint8_t>&>> getProgramData();

  friend ostream& operator<<(ostream& os, const IntelHexFile& rhs);
};

#endif
