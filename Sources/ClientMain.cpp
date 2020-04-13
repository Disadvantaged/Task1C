//
// Created by dgolear on 4/13/20.
//

#include <iostream>
#include <string>

#include <asio.hpp>

#include "Client.h"

int main(int argc, char** argv) {
    if (argc != 3) {
      std::cerr << "Usage: Client <ServerAddress> <ServerPort>\n";
      return 1;
    }
    try {

      asio::io_context io_context;

      asio::ip::tcp::socket s(io_context);
      asio::ip::tcp::resolver resolver(io_context);
      asio::connect(s, resolver.resolve(argv[1], argv[2]));

      Client c(std::move(s));

      c.run();
    } catch(std::exception& e) {
      std::cout << e.what() << std::endl;
    }
    return 0;
  }
