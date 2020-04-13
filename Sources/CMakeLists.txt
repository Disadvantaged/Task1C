set(CMAKE_CXX_STANDARD 11)

add_executable(Server Server.cpp main.cpp Connection.cpp ConnectionManager.cpp)
add_executable(Client Client.cpp ClientMain.cpp)

target_link_libraries(Server pthread)
target_link_libraries(Client pthread)
