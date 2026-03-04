#pragma once
#include <string>

namespace ll {
   enum class TokenType
{
        // ===== Special =====
        EndOfFile,
        Invalid,

        // ===== Whitespace & Comments =====
        Whitespace,
        NewLine,
        CommentLine,
        CommentBlock,

        // ===== Identifiers & Literals =====
        Identifier,
        Number,
        Float,
        String,
        Char,
        Boolean,
        Null,

        // ===== Keywords =====
        If,
        Else,
        For,
        While,
        Do,
        Switch,
        Case,
        Default,
        Break,
        Continue,
        Return,

        Function,
        Class,
        Struct,
        Enum,
        Namespace,
        Import,
        Using,

        Public,
        Private,
        Protected,
        Static,
        Const,
        Let,
        Var,

        New,
        Delete,
        This,
        Base,

        Try,
        Catch,
        Finally,
        Throw,

        True,
        False,

        // ===== Operators =====
        Plus,              // +
        Minus,             // -
        Multiply,          // *
        Divide,            // /
        Modulo,            // %

        Increment,         // ++
        Decrement,         // --

        Assign,            // =
        PlusAssign,        // +=
        MinusAssign,       // -=
        MultiplyAssign,    // *=
        DivideAssign,      // /=
        ModuloAssign,      // %=

        Equal,             // ==
        NotEqual,          // !=
        Less,              // <
        LessEqual,         // <=
        Greater,           // >
        GreaterEqual,      // >=

        LogicalAnd,        // &&
        LogicalOr,         // ||
        LogicalNot,        // !

        BitAnd,            // &
        BitOr,             // |
        BitXor,            // ^
        BitNot,            // ~

        ShiftLeft,         // <<
        ShiftRight,        // >>

        Arrow,             // ->
        Dot,               // .
        ScopeResolution,   // ::

        Question,          // ?
        Colon,             // :

        // ===== Delimiters =====
        LeftParen,         // (
        RightParen,        // )

        LeftBrace,         // {
        RightBrace,        // }

        LeftBracket,       // [
        RightBracket,      // ]

        Comma,             // ,
        Semicolon,         // ;
}
; 
}
