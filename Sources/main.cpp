//
// Created by dgolear on 4/13/20.
//

#include <fstream>
#include <iostream>

#include "Server.h"

// Usage: address, port, filename
int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "Usage: Server <address> <port> <FileName>\n";
    return 1;
  }
  std::ifstream file(argv[3]);
  std::vector<std::string> words;
  std::string word;
  while (file >> word) {
    words.emplace_back(std::move(word));
  }
  Server s(argv[1], argv[2], std::move(words));
  s.run();
  return 0;
}
