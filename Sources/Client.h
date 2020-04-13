//
// Created by dgolear on 4/13/20.
//

#pragma once

#include <asio.hpp>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Client {
public:
  explicit Client(asio::ip::tcp::socket s):
    socket_(std::move(s)), word_(128, '*') {
  }

  void run();
private:
  int Evaluate(const std::string& answer, char c);

  asio::ip::tcp::socket socket_;
  std::string word_;
  int num_tries_;
  std::unordered_set<char> symbols_guessed_;
  std::unordered_set<char> symbols_not_guessed_;
  size_t left_to_guess_;
};
