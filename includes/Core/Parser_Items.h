#ifndef PARSER_ITEMS_H
#define PARSER_ITEMS_H

#include "../Global/Follow.h"

typedef struct Parser_Items
{
    ProductionSalver* prod_salver;
    SymbolTable* symbol_table;
    FirstSetTable* firsts_table;
    FollowSetTable* follows_table;
}Parser_Items;

void Init_Parser_Items(Parser_Items* parser_items, ProductionSalver* salver, 
    SymbolTable* symbol_table, 
    FirstSetTable* first_set_table, 
    FollowSetTable* follow_set_table);
#endif