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

class IntelHexFileEntry {
 private:
  uint32_t address;
  uint8_t recordType;
  std::vector<uint8_t> data;
  uint8_t checksum;

  uint64_t asciiHexTo64(std::string s);

 public:
  IntelHexFileEntry(std::string entry);

  uint8_t getByteCount() const;
  uint32_t getAddress() const;
  void setAddress(const uint32_t address);
  uint32_t getEndAddress() const;
  uint8_t getRecordType() const;
  std::vector<uint8_t> &getData();
  uint8_t getChecksum() const;
};

#endif
