#define COMMENT 300
#define ID 301
#define GENERIC_T 302
#define BOOL 303
#define BOOL_T 304
#define BOOL_FALSE 305
#define UINT8 306
#define UINT16 307
#define UINT32 308
#define UINT64 309
#define INT8 310
#define INT16 311
#define INT32 312
#define INT64 313
#define FLOAT32 314
#define FLOAT64 315
#define COMPLEX64 316
#define COMPLEX128 317
#define BYTE 306
#define RUNE 308
#define STRING 318
#define MAKE 319
#define NEW 320
#define STRUCT 321
#define FUNC 322
#define CHANNEL 323
#define CONST 324
#define VAR 325
#define PACKAGE 326
#define IMPORT 327
#define FOR 328
#define RANGE 329
#define REAL 330
#define GO 331
#define BREAK 332
#define CASE 333
#define CONTINUE 334
#define DEFAULT 335
#define DEFER 336
#define ELSE 337
#define FALLTHROUGH 338
#define GOTO 339
#define IF 340
#define INTERFACE 341
#define MAP 342
#define RETURN 343
#define SELECT 344
#define SWITCH 345
#define TYPE 346
#define BLANKID 347
#define LINEBREAK 348

//OPERATORS
//+=
#define OP_PLUSEQ 700
//&=
#define OP_AMPEQ 701
//&&
#define OP_AMPAMP 702
//==
#define OP_EQEQ 703
//!=
#define OP_NEQ 704
//-=
#define OP_SUBEQ 705
//|=
#define OP_OREQ 706
//||
#define OP_OROR 707
//<=
#define OP_LEQ 708
//*=
#define OP_MULTEQ 709
//^=
#define OP_EXPEQ 710
//<-
#define OP_LEFTARROW 711
//>=
#define OP_MEQ 712
//<<
#define OP_LESSLESS 713
///=
#define OP_FORWARDSLASHEQ 714
//<<=
#define OP_LESSLESSEQ 715
//++
#define OP_PLUSPLUS 716
//:=
#define OP_COLONEQ 717
//>>
#define OP_MOREMORE 718
//%=
#define OP_PERCENTAGEEQ 719
//>>=
#define OP_MOREMOREEQ 720
//--
#define OP_SUBSUB 721
//...
#define OP_DOTS 722
//&^
#define OP_AMPEXP 723
//&^=
#define OP_AMPEXPEQ 724

#define ERROR (-42)
#define UNIDENTIFIED (-88)

//LITERALS
#define LIT_INTEGER 800
#define LIT_FLOAT 801
#define LIT_IMAGINARY 802
#define LIT_STRING 803
#define LIT_OCTAL 804
#define LIT_HEXADECIMAL 805