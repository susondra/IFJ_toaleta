#include "dynamic_string.h"
#include "types.h"

Dynamic_string dyn_str;
operation op;
stack_operation st_op;

#define MAX_DIGITS 40

#define ADD_LINE(_line)                                        \
    if (!dynamic_string_add_const_str(&dyn_str, (_line "\n"))) \
    return false

#define ADD_TOLINE(_to)                               \
    if (!dynamic_string_add_const_str(&dyn_str, _to)) \
    return false

#define ADD_INT(_str)             \
    do                            \
    {                             \
        char str[MAX_DIGITS];     \
        sprintf(str, "%d", _str); \
        ADD_STR(str);             \
    } while (0)

#define readstr                                        \
    LABEL readstr                                      \
        CREATEFRAME                                    \
            DEFVAR TF @input                           \
                READ TF @input string                  \
                    JUMPIFEQ end_readstr TF @input nil \
                        STRLEN TF @length TF @input    \
                            SUB TF @length TF @length int @1 GETCHAR TF @input TF @input int @0 end_readi32 : RETURN

#define readi32                                                         \
    LABEL readi32                                                       \
        CREATEFRAME                                                     \
            DEFVAR TF @input                                            \
                READ TF @input int                                      \
                    JUMPIFEQ end_readi32 TF @input nil                  \
                        TYPE TF @type TF @input                         \
                            JUMPIFNEQ end_readi32 TF @type string @ int \
                                end_readi32 : RETURN

#define readf64                                     \
    "LABEL readf64"                                 \
    "CREATEFRAME"                                   \
    "DEFVAR TF @input"                              \
    "READ TF @input float"                          \
    "JUMPIFEQ end_readf64 TF @input nil"            \
    "TYPE TF @type TF @input"                       \
    "JUMPIFNEQ end_readf64 TF @type string @ float" \
    "end_readf64 : RETURN"

bool gen_header()
{
    ADD_LINE("#Start of the program");
    ADD_LINE(".IFJCode24");
    return true;
}

bool gen_main_start()
{
    ADD_LINE("\n#Main start");
    ADD_LINE("LABEL main");
    ADD_LINE("CREATEFRAME");
    ADD_LINE("PUSHFRAME");
    return true;
}

bool gen_main_end()
{
    ADD_LINE("\n#Main end");
    ADD_LINE("POPFRAME");
    ADD_LINE("CLEARS");
    return true;
}

bool gen_function_start()
{
    ADD_LINE("\n#Function start");
    ADD_TOLINE("LABEL ");
    ADD_LINE("function_id");
    ADD_LINE("CREATEFRAME");
    ADD_LINE("PUSHFRAME");
    return true;
}

bool gen_function_end()
{
    ADD_LINE("\n#Function end");
    ADD_TOLINE("LABEL ");
    ADD_LINE("function_id");
    ADD_LINE("POPFRAME");
    ADD_LINE("RETURN");
    ADD_LINE("CLEARS");
    return true;
}

bool gen_call()
{
    ADD_TOLINE("CALL ");
    ADD_LINE("function_id");
    return true;
}

bool gen_label()
{
    return true;
}

bool gen_if_start()
{
    ADD_LINE("\n#If start");
    ADD_LINE("DEFVAR temp");
    ADD_LINE("NOT temp");
    ADD_TOLINE("JUMPIFEQ");
    ADD_TOLINE("label_name");
    ADD_TOLINE("temp");
    ADD_LINE("TRUE");

    return true;
}

bool gen_if_else()
{
    return true;
}

bool gen_if_end()
{
    ADD_LINE("\n#If end");

    return true;
}

bool gen_operation(operation op)
{
    switch (op)
    {
    case PLUS:
        ADD_LINE("ADD");
        break;

    case MINUS:
        ADD_LINE("SUB");
        break;

    case TIMES:
        ADD_LINE("MUL");
        break;

    case DIVIDE:
        ADD_LINE("DIV");
        break;

    case IDIV:
        ADD_LINE("DIV");
        break;

    case EQUAL:
        ADD_LINE("EQ");
        break;

    case NOTEQUAL:
        ADD_LINE("EQ");
        ADD_LINE("NOT");
        break;

    case LESS:
        ADD_LINE("LT");
        break;

    case GREATER:
        ADD_LINE("GT");
        break;

    case LESSOREQUAL:

        break;

    case GREATEROREQUAL:

        break;

    default:
        break;
    }

    return true;
}

bool gen_stack_operation(stack_operation st_op)
{
    switch (st_op)
    {
    case S_PLUS:
        ADD_LINE("ADDS");
        break;

    case S_MINUS:
        ADD_LINE("SUBS");
        break;

    case S_TIMES:
        ADD_LINE("MULS");
        break;

    case S_DIVIDE:
        ADD_LINE("DIVS");
        break;

    case S_IDIV:
        ADD_LINE("IDIVS");
        break;

    case S_EQUAL:
        ADD_LINE("EQS");
        break;

    case S_NOTEQUAL:
        ADD_LINE("EQS");
        ADD_LINE("NOTS");
        break;

    case S_LESS:
        ADD_LINE("LTS");
        break;

    case S_GREATER:
        ADD_LINE("GTS");
        break;

    case S_LESSOREQUAL:
        ADD_LINE("POPS GF@tmp_2");
        ADD_LINE("POPS GF@tmp_1");
        ADD_LINE("PUSHS GF@tmp_2");
        ADD_LINE("PUSHS GF@tmp_1");
        ADD_LINE("LTS");
        ADD_LINE("PUSHS GF@tmp_2");
        ADD_LINE("PUSHS GF@tmp_1");
        ADD_LINE("EQS");
        ADD_LINE("ORS");
        break;

    case S_GREATEROREQUAL:
        ADD_LINE("POPS GF@tmp_op1");
        ADD_LINE("POPS GF@tmp_op2");
        ADD_LINE("PUSHS GF@tmp_op2");
        ADD_LINE("PUSHS GF@tmp_op1");
        ADD_LINE("GTS");
        ADD_LINE("PUSHS GF@tmp_op2");
        ADD_LINE("PUSHS GF@tmp_op1");
        ADD_LINE("EQS");
        ADD_LINE("ORS");
        break;

    default:
        break;
    }

    return true;
}