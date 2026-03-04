#include <stdexcept>
#include "ll/machines/identifier_machine.h"

namespace ll {

    void IdentifierMachine::init_state_table() {
        auto begin_state = std::make_unique<State>("begin_state");
        auto final_state = std::make_unique<State>("final_state", true);

        begin_state->add_transition_range('a', 'z', final_state.get());
        begin_state->add_transition_range('A', 'Z', final_state.get());
        final_state->add_transition_range('a', 'z', final_state.get());
        final_state->add_transition_range('A', 'Z', final_state.get());

        add_state(std::move(begin_state));
        add_state(std::move(final_state));
    }


    TokenType IdentifierMachine::get_token_type() const {
        return TokenType::Identifier;
    }
}


