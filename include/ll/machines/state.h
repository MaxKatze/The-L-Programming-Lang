#pragma once
#include <string>
#include <map>

namespace ll {

class State {
public:
    State(std::string name, bool is_final = false);
    void add_transition(char input, State* target_state);
    void add_transition_range(char input_start, char input_end, State* target_state);
    State* get_transition(char input) const;
    std::string get_name() const;
    bool get_is_final() const;
    void set_is_final(bool is_final);

private:
    std::string m_name;
    bool m_is_final;
    std::map<char, State*> m_transitions;
};

}