#include <assert.h>
#include <ihex-parser/IntelHexFile.hpp>
#include <iostream>
#include <string>

using namespace std;

void usage(string name);

#define PAGE_SIZE 255

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage(argv[0]);
    return 1;
  }

  /*
   * Parse file
   */
  IntelHexFile file(argv[1]);
  cout << "File: " << file << endl;

  // Get raw values

  for (const auto &e : file.getProgramData()) {
    cerr << "Start address: 0x" << hex << e.first << " data: ";
    for (int i = 0; i < e.second.size(); i++) {
      cerr << "0x" << hex << static_cast<uint32_t>(e.second[i]);
      if (i < e.second.size() - 1) {
        cerr << ", ";
      }
    }
    cout << '\n';
  }

  return 0;

  /*
   * Get the program
   */
  Program program = file.getProgram();
  cout << "Program: " << program << endl;

  /*
   * Get the program in a vector of pages
   */
  vector<ProgramPage> programPages = program.getPages(PAGE_SIZE);

  for (vector<ProgramPage>::iterator it = programPages.begin();
       it != programPages.end(); ++it) {
    ProgramPage page = (*it);
    cout << "Page: " << page << endl;
  }

  return 0;
}

void usage(string name) { cout << name << ": [*.hex]" << endl; }
