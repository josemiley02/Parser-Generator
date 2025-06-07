#include "../includes/Global/Follow.h"

void Init_Follow_Set_Table(FollowSetTable* follow_table, FirstSetTable* first_table, 
    SymbolTable* symbol_table, ProductionSalver* salver)
{
    // Iniciar la tabla
    follow_table->len_sets = 0;
    follow_table->capacity = first_table->len_sets;
    follow_table->sets = malloc(sizeof(FollowSet) * follow_table->capacity);

    Symbol* initial_symbol = Get_Symbol(symbol_table, salver->productions[0].lhs);

    for (int i = 0; i < symbol_table->len_table; i++)
    {
        Symbol* s = &symbol_table->symbols[i];
        if (!s->IsTerminal)
        {
            FollowSet set;
            set.key = s;
            set.cardinality = 0;
            set.total_cardinality = 4;
            set.symbols = malloc(sizeof(Symbol *) * set.total_cardinality);

            // Si es el símbolo inicial, agregamos $
            if (strcmp(s->Name, initial_symbol->Name) == 0)
            {
                set.symbols[0] = Get_Symbol(symbol_table, "$");
                set.cardinality = 1;
            }

            follow_table->sets[follow_table->len_sets++] = set;
        }
    }

    Compute_Follow_Sets(follow_table, first_table, symbol_table, salver);
}

void Compute_Follow_Sets(FollowSetTable* follow_table, FirstSetTable* first_table, 
                         SymbolTable* symbol_table, ProductionSalver* salver)
{
    bool changed = true;

    while (changed)
    {
        changed = false;

        for (int p = 0; p < salver->len_productions; p++)
        {
            Production prod = salver->productions[p];
            Symbol* A = Get_Symbol(symbol_table, prod.lhs);
            FollowSet* follow_A = Get_Follow_Set(follow_table, A);

            for (int i = 0; i < prod.len_rhs; i++)
            {
                Symbol* B = Get_Symbol(symbol_table, prod.rhs[i]);
                if (!B->IsTerminal)
                {
                    bool nullable = true;

                    // FIRST(β) = FIRST of the rest of RHS after B
                    for (int j = i + 1; j < prod.len_rhs; j++)
                    {
                        Symbol* beta_sym = Get_Symbol(symbol_table, prod.rhs[j]);
                        FirstSet* first_beta = Get_First_Set(first_table, beta_sym);

                        for (int f = 0; f < first_beta->cardinality; f++)
                        {
                            Symbol* sym = first_beta->symbols[f];
                            if (strcmp(sym->Name, "ε") != 0)
                            {
                                if (Add_To_Follow_Set(Get_Follow_Set(follow_table, B), sym))
                                    changed = true;
                            }
                        }

                        // Si beta no tiene ε, terminamos aquí
                        if (!Contains_Epsilon(first_beta))
                        {
                            nullable = false;
                            break;
                        }
                    }

                    // Si β es vacía o nullable, añadimos FOLLOW(A) a FOLLOW(B)
                    if (i == prod.len_rhs - 1 || nullable)
                    {
                        FollowSet* follow_B = Get_Follow_Set(follow_table, B);
                        for (int f = 0; f < follow_A->cardinality; f++)
                        {
                            if (Add_To_Follow_Set(follow_B, follow_A->symbols[f]))
                                changed = true;
                        }
                    }
                }
            }
        }
    }
}

bool Add_To_Follow_Set(FollowSet* set, Symbol* symbol)
{
    for (int i = 0; i < set->cardinality; i++)
    {
        if(strcmp(set->symbols[i]->Name, symbol->Name) == 0)
        {
            return false;
        }
    }
    if (set->cardinality >= set->total_cardinality)
    {
        set->total_cardinality *= 2;
        set->symbols = realloc(set->symbols, sizeof(Symbol *) * set->total_cardinality);
    }
    set->symbols[set->cardinality++] = symbol;
    return true;
}

bool Contains_Epsilon(FirstSet* set)
{
    for (int i = 0; i < set->cardinality; i++)
    {
        if (strcmp(set->symbols[i]->Name, "ε") == 0)
            return true;
    }
    return false;
}

FollowSet* Get_Follow_Set(FollowSetTable* table, Symbol* symbol)
{
    for (int i = 0; i < table->len_sets; i++)
    {
        if (strcmp(table->sets[i].key->Name, symbol->Name) == 0)
            return &table->sets[i];
    }
    return NULL; // o manejar error
}

void Free_Follow_Set(FollowSet* set)
{
    free(set->symbols);
    set->symbols = NULL;
    set->cardinality = 0;
    set->total_cardinality = 0;
}

void Free_Follow_Set_Table(FollowSetTable* follow_table)
{
    for (int i = 0; i < follow_table->len_sets; i++)
    {
        Free_Follow_Set(&follow_table->sets[i]);
    }
    follow_table->capacity = 0;
    follow_table->len_sets = 0;
}