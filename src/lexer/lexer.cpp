#include "ll/lexer/lexer.h"
#include <stdexcept>
#include <ll/machines/identifier_machine.h>
#include <ll/machines/integer_machine.h>
#include <ll/machines/keyword_machine.h>
#include <ll/machines/whitespace_machine.h>


namespace ll {

    void Lexer::init_machines(){
        m_machines.clear();
        m_machines.reserve(40);

        //m_machines.push_back(std::make_unique<KeywordMachine>("fn", TokenType::Function));
        // m_machines.push_back(std::make_unique<KeywordMachine>("if", TokenType::If));
        // m_machines.push_back(std::make_unique<KeywordMachine>("else", TokenType::Else));
        // m_machines.push_back(std::make_unique<KeywordMachine>("for", TokenType::For));
        // m_machines.push_back(std::make_unique<KeywordMachine>("while", TokenType::While));
        // m_machines.push_back(std::make_unique<KeywordMachine>("do", TokenType::Do));
        // m_machines.push_back(std::make_unique<KeywordMachine>("switch", TokenType::Switch));
        // m_machines.push_back(std::make_unique<KeywordMachine>("case", TokenType::Case));
        // m_machines.push_back(std::make_unique<KeywordMachine>("default", TokenType::Default));
        // m_machines.push_back(std::make_unique<KeywordMachine>("break", TokenType::Break));
        // m_machines.push_back(std::make_unique<KeywordMachine>("continue", TokenType::Continue));
        // m_machines.push_back(std::make_unique<KeywordMachine>("return", TokenType::Return));
        // m_machines.push_back(std::make_unique<KeywordMachine>("class", TokenType::Class));
        // m_machines.push_back(std::make_unique<KeywordMachine>("struct", TokenType::Struct));
        // m_machines.push_back(std::make_unique<KeywordMachine>("enum", TokenType::Enum));
        // m_machines.push_back(std::make_unique<KeywordMachine>("namespace", TokenType::Namespace));
        // m_machines.push_back(std::make_unique<KeywordMachine>("import", TokenType::Import));
        // m_machines.push_back(std::make_unique<KeywordMachine>("using", TokenType::Using));
        // m_machines.push_back(std::make_unique<KeywordMachine>("public", TokenType::Public));
        // m_machines.push_back(std::make_unique<KeywordMachine>("private", TokenType::Private));
        // m_machines.push_back(std::make_unique<KeywordMachine>("protected", TokenType::Protected));
        // m_machines.push_back(std::make_unique<KeywordMachine>("static", TokenType::Static));
        // m_machines.push_back(std::make_unique<KeywordMachine>("const", TokenType::Const));
        m_machines.push_back(std::make_unique<KeywordMachine>("let", TokenType::Let));
        m_machines.push_back(std::make_unique<KeywordMachine>("=", TokenType::Assign));
        // m_machines.push_back(std::make_unique<KeywordMachine>("var", TokenType::Var));
        // m_machines.push_back(std::make_unique<KeywordMachine>("new", TokenType::New));
        // m_machines.push_back(std::make_unique<KeywordMachine>("delete", TokenType::Delete));
        // m_machines.push_back(std::make_unique<KeywordMachine>("this", TokenType::This));
        // m_machines.push_back(std::make_unique<KeywordMachine>("base", TokenType::Base));
        // m_machines.push_back(std::make_unique<KeywordMachine>("try", TokenType::Try));
        // m_machines.push_back(std::make_unique<KeywordMachine>("catch", TokenType::Catch));
        // m_machines.push_back(std::make_unique<KeywordMachine>("finally", TokenType::Finally));
        // m_machines.push_back(std::make_unique<KeywordMachine>("throw", TokenType::Throw));
        // m_machines.push_back(std::make_unique<KeywordMachine>("true", TokenType::True));
        // m_machines.push_back(std::make_unique<KeywordMachine>("false", TokenType::False));
        //m_machines.push_back(std::make_unique<KeywordMachine>("null", TokenType::Null));

        m_machines.push_back(std::make_unique<IdentifierMachine>());
        m_machines.push_back(std::make_unique<IntegerMachine>());
        m_machines.push_back(std::make_unique<WhitespaceMachine>());

        for(auto& machine : m_machines){
            machine->init_state_table();
        }
    }

    void Lexer::set_input(std::string input){
        m_input = input;
        position = 0;
    }
    
    char Lexer::get_current_char() {
        return m_input[position];
    }

    void Lexer::advance(){
        position++;
    }
    
    TokenType Lexer::parse_next_token(){
        if(position >= m_input.length()){
            return TokenType::EndOfFile;
        }

        const int token_start = position;
        StateMachine* longest_running_machine = nullptr;
        int longest_run = 0;

        while(position < m_input.length() && is_machine_running()){
            char current_char = get_current_char();
            for(auto &machine : m_machines){
                machine->step(current_char);
                if(machine->is_in_final() && machine->get_steps() > longest_run){
                    longest_running_machine = machine.get();
                    longest_run = machine->get_steps();
                }
            }
            advance();
        }

        if(longest_running_machine == nullptr){
            position = token_start + 1;
            return TokenType::Invalid;
        }

        position = token_start + longest_run;
        return longest_running_machine->get_token_type();
    }

    bool Lexer::is_machine_running(){
        for(auto &machine : m_machines){
            if(!machine->is_in_error()){
                return true;
            }
        }
        return false;
    }

    std::vector<TokenType> Lexer::parse_input(){
        std::vector<TokenType> tokens{};
        while(position < m_input.length()){
            TokenType next_token = parse_next_token();
            tokens.push_back(next_token);
            for(auto& machine : m_machines){
                machine->reset_machine();
            }
        }
        return tokens;
    }
}
