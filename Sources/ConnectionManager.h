//
// Created by dgolear on 4/13/20.
//

#pragma once

#include <unordered_set>

#include "Connection.h"

class ConnectionManager {
public:
  ConnectionManager(const ConnectionManager &) = delete;
  ConnectionManager &operator=(const ConnectionManager &) = delete;

  /// Construct a connection manager.
  ConnectionManager();

  /// Add the specified connection to the manager and start it.
  void start(connection_ptr c);

  /// Stop the specified connection.
  void stop(connection_ptr c);

  /// Stop all connections.
  void stop_all();

private:
  /// The managed connections.
  std::unordered_set<connection_ptr> connections_;
};
