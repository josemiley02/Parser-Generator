#ifndef FOLLOW_H
#define FOLLOW_H
#include "First.h"

typedef struct FollowSet
{
    Symbol key;
    Symbol* symbols;
    int cardinality;
    int total_cardinality;
}FollowSet;

typedef struct FollowSetTable
{
    FollowSet* sets;
    int len_sets;
    int capacity;
}FollowSetTable;

void Init_Follow_Set_Table(FollowSetTable* follow_table, FirstSetTable* first_table, SymbolTable* symbol_table, ProductionSalver* salver);
void Compute_Follow_Sets(FollowSetTable* follow_table, FirstSetTable* first_table, SymbolTable* symbol_table, ProductionSalver* salver);
bool Add_To_Follow_Set(FollowSet* set, Symbol symbol);
bool Contains_Epsilon(FirstSet* set);
FollowSet* Get_Follow_Set(FollowSetTable* table, Symbol* symbol);

void Free_Follow_Set(FollowSet* set);
void Free_Follow_Set_Table(FollowSetTable* follow_table);
#endif