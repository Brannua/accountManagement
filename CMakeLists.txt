cmake_minimum_required(VERSION 3.0)

project(ACCOUNT_MANAGEMENT)

set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_BUILD_TYPE, Debug)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(account src/account.cpp src/date.cpp SavingsAccount.cpp)
