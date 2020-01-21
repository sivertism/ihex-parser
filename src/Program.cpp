#include <ihex-parser/Program.hpp>

Program::Program(
    const std::map<uint32_t, IntelHexFileEntry>& addressToFileEntries) {
  size_t hAddress = ((addressToFileEntries.rbegin())->second).getEndAddress();
  data.resize(hAddress);

  for (std::map<uint32_t, IntelHexFileEntry>::const_iterator it =
           addressToFileEntries.begin();
       it != addressToFileEntries.end(); ++it) {
    size_t address = (size_t)it->first;
    IntelHexFileEntry entry = it->second;
    std::vector<uint8_t> entryData = entry.getData();

    for (size_t i = 0; i < entryData.size(); i++) {
      uint8_t v = entryData[i];
      data[address + i] = v;
    }
  }
}

std::vector<ProgramPage> Program::getPages(size_t pageSize) {
  std::vector<ProgramPage> pages;

  for (size_t i = 0; i < data.size(); i += pageSize) {
    size_t pageEndAddress = std::min(i + pageSize, data.size());

    std::vector<uint8_t> pageData(data.begin() + i,
                                  data.begin() + pageEndAddress);
    ProgramPage p(i, pageSize, pageData);
    pages.push_back(p);
  }

  return pages;
}

std::ostream& operator<<(std::ostream& os, const Program& rhs) {
  os << "[Num Bytes: " << rhs.data.size() << ", Data: ";

  for (std::vector<uint8_t>::const_iterator it = rhs.data.begin();
       it != rhs.data.end(); ++it) {
    uint8_t v = (*it);
    os << std::hex << (size_t)v;
  }

  os << std::dec << "]";
  return os;
}
