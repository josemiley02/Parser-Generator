#include "../includes/Global/First.h"

void Init_Set_Table(FirstSetTable* set_table, SymbolTable* symbol_table, ProductionSalver* prod_salver)
{
    set_table->len_sets = 0;
    set_table->capacity = symbol_table->len_table;
    set_table->sets = malloc(sizeof(FirstSet) * symbol_table->len_table);

    for (int i = 0; i < symbol_table->len_table; i++)
    {
        Symbol s = symbol_table->symbols[i];
        FirstSet set;
        set.key = s;
        if (s.IsTerminal)
        {
            set.cardinality = 1;
            set.total_cardinality = 1;
            set.symbols = malloc(sizeof(Symbol *) * set.total_cardinality);
            set.symbols[0] = set.key;
        }
        else
        {
            set.cardinality = 0;
            set.total_cardinality = 4;
            set.symbols = malloc(sizeof(Symbol *) * set.total_cardinality);
        }
        set_table->sets[set_table->len_sets++] = set;
    }

    Compute_First_Sets(set_table, symbol_table, prod_salver);
}

bool Add_To_First_Set(FirstSet* set, Symbol symbol)
{
    if (set->cardinality >= set->total_cardinality)
    {
        set->total_cardinality *= 2;
        set->symbols = realloc(set->symbols, sizeof(Symbol*) * set->total_cardinality);
    }
    for (int i = 0; i < set->cardinality; i++)
    {
        if(strcmp(set->symbols[i].Name, symbol.Name) == 0) return false;
    }
    set->symbols[set->cardinality++] = symbol;
    return true;
}

FirstSet* Get_First_Set(FirstSetTable* set_table, Symbol* symbol)
{
    for (int i = 0; i < set_table->len_sets; i++)
    {
        if(strcmp(set_table->sets[i].key.Name, symbol->Name) == 0)
        {
            return &set_table->sets[i];
        }
    }
    return NULL;
}

void Compute_First_Sets(FirstSetTable* set_table, SymbolTable* symbol_table, ProductionSalver* prod_salver)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i < prod_salver->len_productions; i++)
        {
            Symbol A;
            Get_Symbol(symbol_table, prod_salver->productions[i].lhs, A);
            char** RHS = prod_salver->productions[i].rhs;

            FirstSet* first_A = Get_First_Set(set_table, &A);
            bool prefix = true;
            bool have_epsilon = false;
            int j = 0;
            while (j < prod_salver->productions[i].len_rhs)
            {
                Symbol Xi; 
                Get_Symbol(symbol_table, RHS[j], Xi);
                FirstSet* first_xi = Get_First_Set(set_table, &Xi);

                for (int sym = 0; sym < first_xi->cardinality; sym++)
                {
                    if(strcmp(first_xi->symbols[sym].Name, "ε") != 0)
                    {
                        if(Add_To_First_Set(first_A, first_xi->symbols[sym]))
                            changed = true;
                    }
                    else have_epsilon = true;
                }
                j += 1;
            }
            if(!have_epsilon)
            {
                prefix = false;
            }
            if(prefix)
            {
                Symbol e;
                if(Get_Symbol(symbol_table, "ε", e));
                if(Add_To_First_Set(first_A, e))
                    changed = true;
            }
        }
    }
}

void Free_Set(FirstSet* set)
{
    free(set->symbols);
    set->symbols = NULL;
    set->cardinality = 0;
    set->total_cardinality = 0;
}

void Free_Set_Table(FirstSetTable* set_table)
{
    for (int i = 0; i < set_table->len_sets; i++)
    {
        Free_Set(&set_table->sets[i]);
    }
    set_table->capacity = 0;
    set_table->len_sets = 0;
}