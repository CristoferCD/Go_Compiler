#include "definiciones.h"

const char* reservedWords[] =       {"break"      , "case"   , "chan"   , "const"    , "continue"  , "default", "defer"    , "else"     ,
                                     "fallthrough", "for"    , "func"   , "go"       , "goto"      , "if"     , "import"   , "interface",
                                     "map"        , "package", "range"  , "return"   , "select"    , "struct" , "switch"   , "type"     ,
                                     "var"        , "uint8"  , "uint16" , "uint32"   , "uint64"    , "int8"   , "int16"    , "int32"    ,
                                     "int64"      , "float32", "float64", "complex64", "complex128", "byte"   , "rune"     , "uint"     ,
                                     "int"        , "uintptr", "make"   , "new"      , "string"    , "real"};

const int reservedWords_lexComp[] = {BREAK        , CASE     , CHANNEL  , CONST      , CONTINUE  , DEFAULT  , DEFER      , ELSE       ,
                                     FALLTHROUGH  , FOR      , FUNC     , GO         , GOTO      , IF       , IMPORT     , INTERFACE  ,
                                     MAP          , PACKAGE  , RANGE    , RETURN     , SELECT    , STRUCT   , SWITCH     , TYPE       ,
                                     VAR          , UINT8    , UINT16   , UINT32     , UINT64    , INT8     , INT16      , INT32      ,
                                     INT64        , FLOAT32  , FLOAT64  , COMPLEX64  , COMPLEX128, BYTE     , RUNE       , UINT32     ,
                                     UINT32       , UINT64   , MAKE     , NEW        , STRING    , REAL     , -42};