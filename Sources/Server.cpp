//
// Created by dgolear on 4/13/20.
//

#include "Server.h"

#include <utility>

Server::Server(const std::string &address, const std::string &port,
               std::vector<std::string> words)
    : io_context_(1), signals_(io_context_), acceptor_(io_context_),
      connection_manager_(), available_words_(std::move(words)) {
  srand(time(nullptr));

  signals_.add(SIGINT);
  signals_.add(SIGTERM);

  do_await_stop();

  asio::ip::tcp::resolver resolver(io_context_);
  asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();

  do_accept();
}
void Server::do_await_stop() {
  signals_.async_wait([this](std::error_code /*ec*/, int /*signo*/) {
    acceptor_.close();
    connection_manager_.stop_all();
  });
}

void Server::run() { io_context_.run(); }
void Server::do_accept() {
  acceptor_.async_accept([this](std::error_code ec,
                                asio::ip::tcp::socket socket) {
    // Check whether the server was stopped by a signal before this
    // completion handler had a chance to run.
    if (!acceptor_.is_open()) {
      return;
    }

    if (!ec) {
      std::string word = available_words_[rand() % available_words_.size()];
      connection_manager_.start(
          std::make_shared<Connection>(std::move(socket), connection_manager_,
                                       word, GetNumTries(word.size())));
    }

    do_accept();
  });
}
size_t Server::GetNumTries(size_t len) { return len; }
