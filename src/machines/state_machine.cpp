#include "ll/machines/state_machine.h"
#include <string>

namespace ll {
    
    StateMachine::StateMachine(){
        auto error_state = std::make_unique<State>("ERROR", false);
        m_error_state = error_state.get();
        m_states.push_back(std::move(error_state));
        m_current_state = m_error_state;
        m_steps = 0;
    }
    
    void StateMachine::set_start_state(State* start_state){
        this->m_start_state = start_state;
    }

    void StateMachine::step(char input){
        if(m_current_state == nullptr || m_current_state == m_error_state){
            m_current_state = m_error_state;
            return;
        }
        auto next_state = m_current_state->get_transition(input);
        m_steps++;
        if(next_state == nullptr){
            m_current_state = m_error_state;
        }else{
            m_current_state = next_state;
        }
    }

    int StateMachine::get_steps() const{
        return m_steps;
    }

    void StateMachine::add_state(std::unique_ptr<State> state, bool is_new_start_state){
        if(m_states.size() == 1){
            m_current_state = state.get();
            m_start_state = state.get();
        }
        if(is_new_start_state){
            m_start_state = state.get();
        }
        m_states.push_back(std::move(state));
    }

    bool StateMachine::is_in_final() const{
        if(m_current_state == nullptr){
            return false;
        }
        return m_current_state->get_is_final();
    }

    State* StateMachine::get_current_state() const{
        return m_current_state;
    }

    void StateMachine::reset_machine(){
        m_steps = 0;
        m_current_state = m_start_state;
    }

    bool StateMachine::is_in_error() const{
        return m_current_state == m_error_state;
    }

    TokenType StateMachine::get_token_type() const{
        return m_token_type;
    }

    void StateMachine::set_token_type(TokenType new_token){
        m_token_type = new_token;
    }
}

