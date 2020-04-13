//
// Created by dgolear on 4/13/20.
//
#include "Connection.h"
#include "ConnectionManager.h"

void Connection::start() {
  auto self = shared_from_this();
  asio::async_write(
      socket_,
      asio::buffer(word_for_client_),
      [this, self](std::error_code ec, std::size_t) {
        if (!ec) {
          asio::write(socket_, asio::buffer(&num_tries_, 4));
          do_read();
        }
  });
}

void Connection::stop() {
  socket_.close();
}

void Connection::do_write() {
  auto self(shared_from_this());
  asio::async_write(socket_, asio::buffer(word_for_client_), [this, self](std::error_code ec, size_t) {
    if (!ec) {
      if (end_) {
        manager_.stop(shared_from_this());
      } else {
        do_read();
      }
    } else if (ec != asio::error::operation_aborted) {
      manager_.stop(shared_from_this());
    }
  });
}

void Connection::do_read() {
  auto self(shared_from_this());
  socket_.async_read_some(asio::buffer(answer_),
      [this, self](std::error_code ec, std::size_t /**/) {
    if (!ec)
    {
      char c = answer_[0];
      if (symbols_left_.count(c)) {
        symbols_left_.erase(c);
        symbols_guessed_.insert(c);
        for (int i = 0; i < word_.size(); ++i) {
          if (word_[i] == c) {
            word_for_client_[i] = c;
          }
        }
        if (symbols_left_.empty()) {
          word_for_client_ = "Congratulations";
          end_ = true;
        }
      } else {
        if (symbols_not_guessed_.count(c) == 0) {
          symbols_not_guessed_.insert(c);
          num_tries_--;
          if (num_tries_ == 0) {
            end_ = true;
          }
        }
      }
      do_write();
    } else if (ec != asio::error::operation_aborted) {
      manager_.stop(shared_from_this());
    }
  });
}
