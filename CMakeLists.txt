cmake_minimum_required(VERSION 3.20)
project(LLanguage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ll
  src/main.cpp
  src/machines/state.cpp
  src/machines/state_machine.cpp
  src/machines/integer_machine.cpp
  src/machines/identifier_machine.cpp
  src/machines/keyword_machine.cpp
  src/machines/whitespace_machine.cpp
  src/lexer/lexer.cpp
)

target_include_directories(ll PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)