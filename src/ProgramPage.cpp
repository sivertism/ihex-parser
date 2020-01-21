#include <ihex-parser/ProgramPage.hpp>

ProgramPage::ProgramPage(size_t address, size_t pageSize,
                         const std::vector<uint8_t>& pageData) {
  this->address = address;
  this->pageSize = pageSize;
  data.resize(pageData.size());

  size_t startAddress = address % pageSize;

  for (size_t i = startAddress; i < (startAddress + pageData.size()); i++) {
    data[i] = pageData[i - startAddress];
  }
}

size_t ProgramPage::getAddress() { return address; }

size_t ProgramPage::getSize() { return data.size(); }

size_t ProgramPage::getPageSize() { return pageSize; }

size_t ProgramPage::getEndAddress() { return address + data.size(); }

std::vector<uint8_t> ProgramPage::getData() { return data; }

std::ostream& operator<<(std::ostream& os, const ProgramPage& rhs) {
  os << "[Start Address: 0x" << std::hex << rhs.address;
  os << ", End Address: 0x" << std::hex << (rhs.address + rhs.data.size());
  os << ", Size: " << rhs.data.size();
  os << ", Page Size: " << std::dec << rhs.pageSize;
  os << ", Data: ";

  for (std::vector<uint8_t>::const_iterator it = rhs.data.begin();
       it != rhs.data.end(); ++it) {
    uint8_t v = *it;
    os << std::hex << (size_t)v;
  }

  os << std::dec << "]";
  return os;
}
