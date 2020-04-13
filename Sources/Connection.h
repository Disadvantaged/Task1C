//
// Created by dgolear on 4/13/20.
//

#pragma once

#include <asio.hpp>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection> {
public:
  Connection(const Connection &c) = delete;
  Connection &operator=(const Connection &c) = delete;

  Connection(asio::ip::tcp::socket sock, ConnectionManager &manager,
             std::string word, size_t num_tries)
      : socket_(std::move(sock)), manager_(manager), word_(std::move(word)),
        word_for_client_(word.size(), '*'),
        num_tries_(num_tries) {
    symbols_left_.insert(word_.begin(), word_.end());
  }

  void start();
  void stop();
  void do_read();
  void do_write();

private:
  const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  asio::ip::tcp::socket socket_;
  ConnectionManager &manager_;

  bool end_{false};
  std::string word_;
  std::string word_for_client_;
  std::array<char, 16> answer_;
  size_t num_tries_;
  std::unordered_set<char> symbols_left_;
  std::unordered_set<char> symbols_guessed_;
  std::unordered_set<char> symbols_not_guessed_;
};

typedef std::shared_ptr<Connection> connection_ptr;
