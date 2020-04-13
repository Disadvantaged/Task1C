//
// Created by dgolear on 4/13/20.
//
#include "ConnectionManager.h"

void ConnectionManager::stop_all() {
  for (auto c: connections_)
    c->stop();
  connections_.clear();
}

void ConnectionManager::stop(connection_ptr c) {
  connections_.erase(c);
  c->stop();
}

void ConnectionManager::start(connection_ptr c) {
  connections_.insert(c);
  c->start();
}

ConnectionManager::ConnectionManager() {
}
