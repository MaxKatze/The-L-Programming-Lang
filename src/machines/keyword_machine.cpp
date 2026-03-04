#include <stdexcept>
#include "ll/machines/keyword_machine.h"

namespace ll {


    KeywordMachine::KeywordMachine(std::string keyword, TokenType token_type){
        this->m_keyword = keyword;
        this->m_token_type = token_type;
    }

    void KeywordMachine::init_state_table() {
        auto begin_state = std::make_unique<State>("begin_state");
        auto *it = begin_state.get();
        add_state(std::move(begin_state));
        
        
        for(char c : m_keyword){
            auto new_state = std::make_unique<State>("intermediate_state");
            it->add_transition(c, new_state.get());
            it = new_state.get();
            add_state(std::move(new_state));
        }
        it->set_is_final(true);
    }

    TokenType KeywordMachine::get_token_type() const {
        return m_token_type;
    }
}


