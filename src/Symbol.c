#include "Symbol.h"

Symbol Create_Symbol(char* name, bool isTerminal)
{
    Symbol s;
    s.Name = strdup(name);
    s.IsTerminal = isTerminal;
    return s;
}
Symbol* Get_Symbol(SymbolTable* table, char* symbol_name)
{
    for (int i = 0; i < table->len_table; i++)
    {
        if (strcmp(table->symbols[i].Name, symbol_name) == 0)
        {
            return &table->symbols[i];
        }
    }
    return NULL;
}
bool ContainSymbol(SymbolTable* table, char* symbol_name)
{
    for (int i = 0; i < table->len_table; i++)
    {
        if (strcmp(table->symbols[i].Name, symbol_name) == 0)
        {
            return true;
        }
    }
    return false;
}
void Init_Symbol_Table(SymbolTable* table, ProductionSalver* salver)
{
    table->capacity = salver->len_productions * 2;
    table->len_table = 0;
    table->symbols = malloc(sizeof(Symbol) * table->capacity);

    Find_No_Terminal_Symbols(table, salver);
    Find_Terminal_Symbols(table, salver);
}

void Find_No_Terminal_Symbols(SymbolTable* table, ProductionSalver* salver)
{
    for (int i = 0; i < salver->len_productions; i++)
    {
        if(ContainSymbol(table, salver->productions[i].lhs)) continue;
        Symbol s = Create_Symbol(salver->productions[i].lhs, false);
        table->symbols[table->len_table++] = s;
    }
}

void Find_Terminal_Symbols(SymbolTable* table, ProductionSalver* salver)
{
    for (int i = 0; i < salver->len_productions; i++)
    {
        for (int j = 0; j < salver->productions[i].len_rhs; j++)
        {
            if(ContainSymbol(table, salver->productions[i].rhs[j])) continue;
            Symbol s = Create_Symbol(salver->productions[i].rhs[j], true);
            table->symbols[table->len_table++] = s;
        }
    }
}

void Free_Symbol(Symbol* symbol)
{
    free(symbol->Name);
    symbol->Name = NULL;
}

void Free_Symbol_Table(SymbolTable* table)
{
    for (int i = 0; i < table->len_table; i++)
    {
        Free_Symbol(&table->symbols[i]);
    }
    free(table->symbols);
    table->capacity = 0;
    table->len_table = 0;
}