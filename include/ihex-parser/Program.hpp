/*
 * Program.h
 * Created by Brent Strysko
 *
 * A Program represents the executable data
 * stored by a Intel Hex File.
 */

#ifndef _INTEL_HEX_PARSER_PROGRAM_H_
#define _INTEL_HEX_PARSER_PROGRAM_H_

#include <stdint.h>
#include <map>
#include <sstream>
#include <vector>
#include "IntelHexFileEntry.hpp"
#include "ProgramPage.hpp"

using namespace std;

class Program {
 private:
  vector<uint8_t> data;

 public:
  Program(const map<uint32_t, IntelHexFileEntry>& addressToFileEntries);

  vector<ProgramPage> getPages(size_t pageSize);

  friend ostream& operator<<(ostream& os, const Program& rhs);
};

#endif
