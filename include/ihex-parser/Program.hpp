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

class Program {
 private:
  std::vector<uint8_t> data;

 public:
  Program(const std::map<uint32_t, IntelHexFileEntry>& addressToFileEntries);

  std::vector<ProgramPage> getPages(size_t pageSize);

  friend std::ostream& operator<<(std::ostream& os, const Program& rhs);
};

#endif
