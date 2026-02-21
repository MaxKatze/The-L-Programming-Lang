cmake_minimum_required(VERSION 3.20)

project(L-Language LANGUAGES CXX)

# ---- C++ settings ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json (great for VS Code / clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Try to locate LLVM automatically (macOS + Homebrew) ----
# If LLVM_DIR is not set, try to ask Homebrew for the LLVM prefix and add it to CMAKE_PREFIX_PATH.
if(APPLE AND NOT DEFINED LLVM_DIR)
  find_program(BREW_EXECUTABLE brew)
  if(BREW_EXECUTABLE)
    execute_process(
      COMMAND ${BREW_EXECUTABLE} --prefix llvm
      OUTPUT_VARIABLE HOMEBREW_LLVM_PREFIX
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET
      RESULT_VARIABLE BREW_LLVM_RESULT
    )

    if(BREW_LLVM_RESULT EQUAL 0 AND EXISTS "${HOMEBREW_LLVM_PREFIX}/lib/cmake/llvm/LLVMConfig.cmake")
      message(STATUS "Homebrew LLVM prefix: ${HOMEBREW_LLVM_PREFIX}")
      # This makes find_package(LLVM CONFIG) work without passing -DLLVM_DIR
      list(PREPEND CMAKE_PREFIX_PATH "${HOMEBREW_LLVM_PREFIX}")
      # Alternatively, you can set LLVM_DIR explicitly:
      # set(LLVM_DIR "${HOMEBREW_LLVM_PREFIX}/lib/cmake/llvm")
    endif()
  endif()
endif()

# ---- Find LLVM ----
# Use QUIET so we can print a friendlier error message ourselves.
find_package(LLVM CONFIG QUIET)

if(NOT LLVM_FOUND)
  message(FATAL_ERROR
    "LLVM not found.\n"
    "If installed via Homebrew, run:\n"
    "  brew install llvm\n\n"
    "Then configure with either:\n"
    "  cmake -S . -B build -DLLVM_DIR=/opt/homebrew/opt/llvm/lib/cmake/llvm   (Apple Silicon)\n"
    "or:\n"
    "  cmake -S . -B build -DLLVM_DIR=/usr/local/opt/llvm/lib/cmake/llvm      (Intel)\n"
  )
endif()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")

# ---- Target ----
add_executable(ll
  src/main.cpp
)

target_include_directories(ll PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(ll PRIVATE ${LLVM_DEFINITIONS})

# Pick the LLVM components you need.
# For your minimal IR-emitter test these are sufficient:
llvm_map_components_to_libnames(LLVM_LIBS
  Core
  Support
)

target_link_libraries(ll PRIVATE ${LLVM_LIBS})

# Helpful warnings (optional)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(ll PRIVATE -Wall -Wextra -Wpedantic)
endif()