#include "../includes/Core/Parser_Items.h"
void Init_Parser_Items(Parser_Items* parser_items, ProductionSalver* salver, 
    SymbolTable* symbol_table, 
    FirstSetTable* first_set_table, 
    FollowSetTable* follow_set_table)
    {
        parser_items->firsts_table = first_set_table;
        parser_items->follows_table = follow_set_table;
        parser_items->prod_salver = salver;
        parser_items->symbol_table = symbol_table;
    }