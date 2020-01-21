#include <ihex-parser/IntelHexFile.hpp>
#include <iostream>

IntelHexFile::IntelHexFile(std::string filename) {
  std::ifstream file(filename.c_str());

  if (!file.is_open()) {
    std::stringstream o;
    o << "Cannot load file ";
    o << filename;
    throw std::ios_base::failure(o.str());
  }

  char buffer[INTEL_HEX_FILE_MAX_ENTRY_SIZE];

  uint32_t baseAddress = 0;
  while (true) {
    file.getline(buffer, INTEL_HEX_FILE_MAX_ENTRY_SIZE);

    /*
     * End of file
     */
    if (!file) {
      break;
    }

    IntelHexFileEntry entry(buffer);

    if ((entry.getRecordType() != 0x0) && (entry.getRecordType() != 0x1) &&
        (entry.getRecordType() != 0x4) && (entry.getRecordType() != 0x5)) {
      std::stringstream o;
      o << "Unsupported record type: 0x";
      o << std::hex << (uint32_t)entry.getRecordType();
      throw std::ios_base::failure(o.str());

    } else if (entry.getRecordType() == 0x4) {
      baseAddress = ((entry.getData()[0] << 8) | entry.getData()[1]) << 16;

    } else if (entry.getRecordType() == 0x5) {
      // Ignore
    } else if (entry.getRecordType() == 0x1) {
      // EOF -- ignore
    } else {
      entry.setAddress(entry.getAddress() + baseAddress);
      addressToFileEntries.insert(
          std::pair<uint32_t, IntelHexFileEntry>(entry.getAddress(), entry));
    }
  }
}

Program IntelHexFile::getProgram() {
  return Program(
      (const std::map<uint32_t, IntelHexFileEntry>)addressToFileEntries);
}

std::vector<std::pair<uint32_t, std::vector<uint8_t>&>>
IntelHexFile::getProgramData() {
  std::vector<std::pair<uint32_t, std::vector<uint8_t>&>> retval;

  for (auto& e : addressToFileEntries) {
    retval.push_back(std::pair<uint32_t, std::vector<uint8_t>&>(
        e.first, e.second.getData()));
  }

  return retval;
}

std::ostream& operator<<(std::ostream& os, const IntelHexFile& rhs) {
  size_t lAddress = (rhs.addressToFileEntries.begin())->first;
  size_t hAddress =
      ((rhs.addressToFileEntries.rbegin())->second).getEndAddress();
  size_t size = rhs.addressToFileEntries.size();

  os << "[Address Range: 0x" << std::hex << (size_t)lAddress << "-0x"
     << std::hex << (size_t)hAddress
     << ", Number of HexFileEntries: " << std::dec << size << "]\n";
  unsigned int i = 0;
  for (const auto& e : rhs.addressToFileEntries) {
    os << "Entry : " << std::dec << i++ << " Address range: 0x" << std::hex
       << e.first << "-0x" << e.second.getEndAddress() << "\n";
  }
  return os;
}
