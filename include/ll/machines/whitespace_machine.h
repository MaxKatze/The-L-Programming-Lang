#include <ll/machines/token.hpp>
#include <ll/machines/state_machine.h>

namespace ll{
    class WhitespaceMachine final : public StateMachine {
        public:
            void init_state_table();
            TokenType get_token_type() const;
        private:
    };
}