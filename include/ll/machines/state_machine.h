#pragma once
#include <string>
#include <map>
#include "state.h"
#include <memory>
#include <vector>
#include <ll/machines/token.hpp>

namespace ll {

class StateMachine {

public:

    StateMachine();
    virtual ~StateMachine() = default;
    void step(char input);
    void add_state(std::unique_ptr<State> state, bool is_new_start_state = false);
    bool is_in_final() const;
    bool is_in_error() const;
    void set_start_state(State* start_state);
    State* get_current_state() const;
    virtual void init_state_table() = 0;
    int get_steps() const;
    virtual TokenType get_token_type() const = 0;
    void set_token_type(TokenType new_token);
    void reset_machine();

private:
    State* m_current_state = nullptr;
    State* m_start_state = nullptr;
    State* m_error_state;
    std::vector<std::unique_ptr<State>> m_states;
    int m_steps;
    TokenType m_token_type;
};

}
