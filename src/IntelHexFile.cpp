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

    std::stringstream o;
    switch (entry.getRecordType()) {
      case 0:  // Data
        entry.setAddress(entry.getAddress() + baseAddress);
        addressToFileEntries.insert(
            std::pair<uint32_t, IntelHexFileEntry>(entry.getAddress(), entry));
        break;
      case 1:  // End of File
               // Ignore
        break;
      case 2:  // Extended Segment Address
        baseAddress = ((entry.getData()[0] << 8) | entry.getData()[1]) * 16;
        break;
      case 3:  // Start Segment Address
        // Ignored (gives the start of execution address)
        break;
      case 4:  // Extended Linear Address
        baseAddress = ((entry.getData()[0] << 8) | entry.getData()[1]) << 16;
        break;
      case 5:  // Start Linear Address
        // Ignore (start of execution address?)
        break;
      default:
        std::stringstream o;
        o << "Invalid record type: ";
        o << std::hex << (uint32_t)entry.getRecordType();
        throw std::ios_base::failure(o.str());

        break;
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
