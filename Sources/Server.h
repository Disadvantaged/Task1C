//
// Created by dgolear on 4/13/20.
//

#pragma once

#include <asio.hpp>
#include <ctime>
#include <string>
#include <vector>

#include "Connection.h"
#include "ConnectionManager.h"

class Server {
public:
  Server(const Server &) = delete;
  Server &operator=(const Server &) = delete;

  explicit Server(const std::string &address, const std::string &port,
                  std::vector<std::string> words);

  /// Run the server's io_context loop.
  void run();

private:
  size_t GetNumTries(size_t word_len);

  /// Perform an asynchronous accept operation.
  void do_accept();

  /// Wait for a request to stop the server.
  void do_await_stop();

  /// The io_context used to perform asynchronous operations.
  asio::io_context io_context_;

  /// The signal_set is used to register for process termination notifications.
  asio::signal_set signals_;

  /// Acceptor used to listen for incoming connections.
  asio::ip::tcp::acceptor acceptor_;

  /// The connection manager which owns all live connections.
  ConnectionManager connection_manager_;

  std::vector<std::string> available_words_;
};
