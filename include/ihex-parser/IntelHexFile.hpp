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

#define INTEL_HEX_FILE_MAX_ENTRY_SIZE 524

class IntelHexFile {
 private:
  std::map<uint32_t, IntelHexFileEntry> addressToFileEntries;

 public:
  IntelHexFile(std::string filename);

  Program getProgram();

  std::vector<std::pair<uint32_t, std::vector<uint8_t>&>> getProgramData();

  friend std::ostream& operator<<(std::ostream& os, const IntelHexFile& rhs);
};

#endif
