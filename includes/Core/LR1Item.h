#ifndef LR1Item_H
#define LR1Item_H

#include "Parser_Items.h"

typedef struct LR1Item
{
    Production production;
    Symbol lookahead;
    int dot_pos;
}LR1Item;

typedef struct LR1ItemSet
{
    LR1Item* items;
    int cardinality;
    int total_cardinality;
}LR1ItemSet;

typedef struct LR1ItemSetTable
{
    LR1ItemSet* sets;
    int cardinality;
    int total_cardinality;
}LR1ItemSetTable;

LR1ItemSet Clousure(LR1ItemSet* I, Parser_Items* parser_items);
LR1ItemSet GoTo(LR1ItemSet* I, Symbol X, Parser_Items* parser_items);
FirstSet* Get_First_Beta_LA(LR1Item item, int dot, Parser_Items* parse_items);
void Items(LR1ItemSetTable* lr1_items_table, Parser_Items* parser_items);
bool Add_To_LR1Items_Set(LR1ItemSet* set, LR1Item item);
bool Add_To_LR1Items_Set_Table(LR1ItemSetTable* table, LR1ItemSet set);
bool Equals_LR1Item_Set(LR1ItemSet* set1, LR1ItemSet* set2);
bool Equals_LR1Item(LR1Item item1, LR1Item item2);
#endif