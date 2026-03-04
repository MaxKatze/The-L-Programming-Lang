#include <stdexcept>
#include "ll/machines/integer_machine.h"

namespace ll {

    void IntegerMachine::init_state_table() {
        auto begin_state = std::make_unique<State>("begin_state");
        auto final_state = std::make_unique<State>("final_state", true);

        begin_state->add_transition_range('0', '9', final_state.get());
        final_state->add_transition_range('0', '9', final_state.get());

        add_state(std::move(begin_state));
        add_state(std::move(final_state));
    }


    TokenType IntegerMachine::get_token_type() const {
        return TokenType::Number;
    }
}


