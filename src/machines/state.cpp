#include "ll/machines/state.h"
#include <stdexcept>

namespace ll {

    State::State(std::string name, bool is_final)
        : m_name(name),
        m_is_final(is_final){}
    
    void State::add_transition(char input, State* target_state){
        if (m_transitions.contains(input)){
            throw std::invalid_argument("No Non deterministic state machines supported.");
        }
        m_transitions.insert({input, target_state});
    }

    void State::add_transition_range(char input_start, char input_end, State* target_state){
        for(char it=input_start; it <= input_end; it++){
            if (m_transitions.contains(it)){
                throw std::invalid_argument("No Non deterministic state machines supported.");
            }
            m_transitions.insert({it, target_state});
        }
    }

    State* State::get_transition(char input) const{
        auto it = m_transitions.find(input);
        if(it == m_transitions.end()){
            return nullptr;
        }
        return it->second;
    }

    bool State::get_is_final() const {
        return m_is_final;
    }

    void State::set_is_final(bool is_final) {
        m_is_final = is_final;
    }

    std::string State::get_name() const{
        return m_name;
    }
}

