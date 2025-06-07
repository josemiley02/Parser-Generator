#ifndef FIRST_H
#define FIRST_H

#include "Symbol.h"
#include "Production.h"

typedef struct FirstSet
{
    Symbol* key;
    Symbol** symbols;
    int cardinality;
    int total_cardinality;
}FirstSet;

typedef struct FirstSetTable
{
    FirstSet* sets;
    int len_sets;
    int capacity;
}FirstSetTable;

void Init_Set_Table(FirstSetTable* set_table, SymbolTable* symbol_table, ProductionSalver* prod_salver);
FirstSet* Get_First_Set(FirstSetTable* set_table, Symbol* symbol);
void Compute_First_Sets(FirstSetTable* set_table, SymbolTable* symbol_table, ProductionSalver* prod_salver);
bool Add_To_Set(FirstSet* set, Symbol* Symbol);

void Free_Set(FirstSet* set);
void Free_Set_Table(FirstSetTable* set_table);
#endif