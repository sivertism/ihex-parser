/*
 * IntelHexFileEntry.h
 * Created by Brent Strysko
 *
 * A IntelHexFileEntry represents a
 * textually parsed entry in a Intel hex file.
 */

#ifndef _INTEL_HEX_PARSER_INTEL_HEX_FILE_ENTRY_H_
#define _INTEL_HEX_PARSER_INTEL_HEX_FILE_ENTRY_H_

#include <stdint.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class IntelHexFileEntry {
 private:
  uint32_t address;
  uint8_t recordType;
  vector<uint8_t> data;
  uint8_t checksum;

  uint64_t asciiHexTo64(string s);

 public:
  IntelHexFileEntry(string entry);

  uint8_t getByteCount();
  uint32_t getAddress();
  void setAddress(const uint32_t address);
  uint32_t getEndAddress() const;
  uint8_t getRecordType();
  vector<uint8_t> getData();
  uint8_t getChecksum();
};

#endif
