//
// Created by dgolear on 4/13/20.
//
#include "Client.h"

void Client::run() {
  int length = asio::read(socket_, asio::buffer(word_));
  word_.resize(length);
  std::string answer(word_);
  length = asio::read(socket_, asio::buffer(&num_tries_, 4));
  left_to_guess_ = word_.size();
  while (left_to_guess_ && num_tries_) {
    std::cout << "Enter letter: ";
    char c;
    std::cin >> c;
    asio::write(socket_, asio::buffer(&c, 1));
    length = asio::read(socket_, asio::buffer(answer));
    Evaluate(answer, c);
  }
  answer.resize(128);
  length = asio::read(socket_, asio::buffer(answer));
  std::cout << answer;
}

int Client::Evaluate(const std::string& answer, char c) {
  int diff = 0;
  for (int i = 0; i < word_.size(); ++i) {
    if (word_[i] != answer[i]) {
      symbols_guessed_.insert(c);
      diff++;
    }
  }
  if (!diff) {
    symbols_not_guessed_.insert(c);
    num_tries_--;
  }
  left_to_guess_ -= diff;
  return diff;
}
