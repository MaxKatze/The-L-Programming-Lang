#pragma once
#include <vector>
#include <ll/machines/state_machine.h>
#include <ll/machines/token.hpp>

namespace ll {

class Lexer {
public:
    void init_machines();
    void set_input(std::string input);
    std::vector<TokenType> parse_input();

private:
    std::vector<std::unique_ptr<StateMachine>> m_machines;
    std::string m_input;
    char get_current_char();
    int position = 0;
    void advance();
    bool is_machine_running();
    TokenType parse_next_token();
};

}
