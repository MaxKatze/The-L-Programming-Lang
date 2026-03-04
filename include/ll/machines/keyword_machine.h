#include <ll/machines/token.hpp>
#include <ll/machines/state_machine.h>


namespace ll{
    class KeywordMachine final : public StateMachine {

        public:
            KeywordMachine(std::string keyword, TokenType token_type);    
            void init_state_table();
            TokenType get_token_type() const;
        private:
            std::string m_keyword;
            TokenType m_token_type;
    };
}