//
// Created by dgolear on 4/13/20.
//

#pragma once

#include <asio.hpp>
#include <memory>
#include <string>
#include <unordered_set>

class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection> {
public:
  Connection(const Connection &c) = delete;
  Connection &operator=(const Connection &c) = delete;

  Connection(asio::ip::tcp::socket sock, ConnectionManager &manager,
             size_t word_length, size_t num_tries)
      : socket_(std::move(sock)), manager_(manager), word_(word_length, '*'),
        num_tries_(num_tries) {
    symbols_left_.insert(word_.begin(), word_.end());
  }

private:
  const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  asio::ip::tcp::socket socket_;
  ConnectionManager &manager_;

  std::string word_;
  size_t num_tries_;
  std::unordered_set<char> symbols_left_;
  std::unordered_set<char> symbols_guessed_;
  std::unordered_set<char> symbols_not_guessed_;
};

typedef std::shared_ptr<Connection> connection_ptr;
