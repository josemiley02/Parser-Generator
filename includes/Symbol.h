#ifndef SYMBOL_H
#define SYMBOL_H
#include "Production.h"
#include <stdbool.h>

typedef struct Symbol
{
    char* Name;
    bool IsTerminal;
}Symbol;

typedef struct SymbolTable
{
    Symbol* symbols;
    int len_table;
    int capacity;
}SymbolTable;

Symbol Create_Symbol(char* name, bool isTerminal);
void Init_Symbol_Table(SymbolTable* table,ProductionSalver* salver);
void Find_No_Terminal_Symbols(SymbolTable* table, ProductionSalver* salver);
void Find_Terminal_Symbols(SymbolTable* table, ProductionSalver* salver);
void Free_Symbol(Symbol* symbol);
void Free_Symbol_Table(SymbolTable* table);
bool ContainSymbol(SymbolTable* table, char* symbol_name);
#endif