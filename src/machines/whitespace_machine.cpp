#include <stdexcept>
#include "ll/machines/whitespace_machine.h"

namespace ll {


    void WhitespaceMachine::init_state_table() {
        auto begin_state = std::make_unique<State>("begin_state");
        auto final_state = std::make_unique<State>("final_state", true);

        begin_state->add_transition('\n', final_state.get());
        begin_state->add_transition('\r', final_state.get());
        begin_state->add_transition('\t', final_state.get());
        begin_state->add_transition(' ', final_state.get());

        final_state->add_transition('\n', final_state.get());
        final_state->add_transition('\r', final_state.get());
        final_state->add_transition('\t', final_state.get());
        final_state->add_transition(' ', final_state.get());

        add_state(std::move(begin_state));

        add_state(std::move(final_state), true);
    }

    TokenType WhitespaceMachine::get_token_type() const {
        return TokenType::Whitespace;
    }
}

