// #include "llvm/IR/IRBuilder.h"
// #include "llvm/IR/LLVMContext.h"
// #include "llvm/IR/Module.h"
// #include "llvm/Support/raw_ostream.h"
#include "ll/machines/state_machine.h"
#include "ll/machines/state.h"
#include "iostream"
#include "ll/lexer/lexer.h"
#include <print>
#include <string>

int main() {

    ll::Lexer lex{};
    lex.init_machines();
    lex.set_input("let myvariable = 123");
    auto tokens = lex.parse_input();
    return 0;
}