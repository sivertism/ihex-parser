#include <ihex-parser/IntelHexFile.hpp>
#include <iostream>

IntelHexFile::IntelHexFile(string filename) {
  ifstream file(filename.c_str());

  if (!file.is_open()) {
    stringstream o;
    o << "Cannot load file ";
    o << filename;
    throw ios_base::failure(o.str());
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
      stringstream o;
      o << "Unsupported record type: 0x";
      o << hex << (uint32_t)entry.getRecordType();
      throw ios_base::failure(o.str());

    } else if (entry.getRecordType() == 0x4) {
      baseAddress = ((entry.getData()[0] << 8) | entry.getData()[1]) << 16;
      cout << "New base address: 0x" << hex << baseAddress << std::endl;

    } else if (entry.getRecordType() == 0x5) {
      // Ignore
    } else if (entry.getRecordType() == 0x1) {
      // EOF -- ignore
    } else {
      entry.setAddress(entry.getAddress() + baseAddress);
      cout << "Adding entry type " << dec << entry.getRecordType()
           << " address: 0x" << hex << entry.getAddress() << "-0x"
           << entry.getEndAddress() << std::endl;
      addressToFileEntries.insert(
          pair<uint32_t, IntelHexFileEntry>(entry.getAddress(), entry));
    }
  }
}

Program IntelHexFile::getProgram() {
  return Program((const map<uint32_t, IntelHexFileEntry>)addressToFileEntries);
}

ostream& operator<<(ostream& os, const IntelHexFile& rhs) {
  size_t lAddress = (rhs.addressToFileEntries.begin())->first;
  size_t hAddress =
      ((rhs.addressToFileEntries.rbegin())->second).getEndAddress();
  size_t size = rhs.addressToFileEntries.size();

  os << "[Address Range: 0x" << hex << (size_t)lAddress << "-0x" << hex
     << (size_t)hAddress << ", Number of HexFileEntries: " << dec << size
     << "]\n";
  unsigned int i = 0;
  for (const auto& e : rhs.addressToFileEntries) {
    os << "Entry : " << dec << i++ << " Address range: 0x" << hex << e.first
       << "-0x" << e.second.getEndAddress() << "\n";
  }
  return os;
}
