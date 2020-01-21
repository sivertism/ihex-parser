#include <ihex-parser/IntelHexFileEntry.hpp>
#include <iostream>

IntelHexFileEntry::IntelHexFileEntry(std::string entry) {
  if (entry[0] != ':') {
    std::stringstream o;
    o << "Invalid hex entry: ";
    o << entry;
    throw std::ios_base::failure(o.str());
  }

  uint8_t count = 2 * asciiHexTo64(entry.substr(1, 2));
  uint8_t hAddress = asciiHexTo64(entry.substr(3, 2));
  uint8_t lAddress = asciiHexTo64(entry.substr(5, 2));
  address = (hAddress << 8) | lAddress;
  recordType = asciiHexTo64(entry.substr(7, 2));
  std::cout << std::dec << recordType << std::endl;

  uint8_t cChecksum = (count / 2) + lAddress + hAddress + recordType;

  if (count != entry.length() - (9 + 2 + 1)) {
    std::stringstream o;
    o << "length provided != length of data | ";
    o << (size_t)(count);
    o << " != ";
    o << (entry.length() - (9 + 2 + 1));

    throw std::ios_base::failure(o.str());
  }

  for (uint8_t i = 0; i < count; i += 2) {
    uint8_t v = asciiHexTo64(entry.substr(9 + i, 2));
    cChecksum += v;
    data.push_back(v);
  }

  uint8_t checksum = asciiHexTo64(entry.substr(entry.length() - 3, 2));

  if (((uint8_t)(cChecksum + checksum)) != ((uint8_t)0)) {
    std::cout << std::hex << (size_t)address << std::endl;
    std::cout << std::dec;

    std::stringstream o;
    o << "(cChecksum + checksum) != 0 | 0x";
    o << std::hex;
    o << (size_t)(cChecksum + checksum);
    o << " != 0 | cChecksum = 0x";
    o << (size_t)cChecksum;
    o << ", checksum = 0x";
    o << (size_t)checksum;

    throw std::ios_base::failure(o.str());
  }
}

uint64_t IntelHexFileEntry::asciiHexTo64(std::string s) {
  std::stringstream o;
  o << std::hex << s;
  uint64_t v;
  o >> v;
  return v;
}

uint8_t IntelHexFileEntry::getByteCount() const { return data.size(); }

uint32_t IntelHexFileEntry::getAddress() const { return address; }

uint32_t IntelHexFileEntry::getEndAddress() const {
  return address + data.size();
}

uint8_t IntelHexFileEntry::getRecordType() const { return recordType; }

std::vector<uint8_t> &IntelHexFileEntry::getData() { return data; }

uint8_t IntelHexFileEntry::getChecksum() const { return checksum; }

void IntelHexFileEntry::setAddress(uint32_t newAddress) {
  address = newAddress;
}
