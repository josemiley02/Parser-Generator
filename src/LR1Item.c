#include "../includes/Core/LR1Item.h"

LR1ItemSet Clousure(LR1ItemSet* I, Parser_Items* parser_items)
{
    int index = 0;
    bool changed = true;
    while (changed)
    {
        changed = false;
        LR1Item item = I->items[index];
        Symbol B;
        int dot = item.dot_pos;
        while(dot < item.production.len_rhs) 
        {
            Get_Symbol(parser_items -> symbol_table, item.production.rhs[dot], B);
            if(!B.IsTerminal) break;
            dot++;
        }
        if(B.Name) continue;

        ProductionSalver* reduce_grammar = Get_Productions(B.Name, parser_items->prod_salver);
        FirstSet* first_beta = Get_First_Beta_LA(item, dot + 1, parser_items);
        for (int p = 0; p < reduce_grammar->len_productions; p++)
        {
            for (int b = 0; b < first_beta->cardinality; b++)
            {
                Symbol sb = first_beta->symbols[b];
                if(sb.IsTerminal)
                {
                    LR1Item new;
                    new.dot_pos = 0;
                    new.lookahead = sb;
                    new.production = reduce_grammar->productions[p];
                    changed = Add_To_LR1Items_Set(I, new);
                }
            }
        }

        Free_Symbol(&B);
        Free_Production_Salver(reduce_grammar);
        Free_Set(first_beta);
        index++;
    }
    LR1ItemSet result;
    result.cardinality = I->cardinality;
    result.total_cardinality = I->total_cardinality;
    result.items = realloc(I->items, sizeof(LR1Item) * result.total_cardinality);
    return result;
}

LR1ItemSet GoTo(LR1ItemSet* I, Symbol X, Parser_Items* parser_items)
{
    LR1ItemSet J;
    J.cardinality = 0;
    J.items = malloc(4);
    J.total_cardinality = 4;
    for (int i = 0; i < I->cardinality; i++)
    {
        LR1Item item = I->items[i];
        if(strcmp(item.production.rhs[item.dot_pos], X.Name))
        {
            item.dot_pos++;
            Add_To_LR1Items_Set(&J, item);
        }
    }
    return Clousure(&J, parser_items);
}

FirstSet* Get_First_Beta_LA(LR1Item item, int dot, Parser_Items* parse_items)
{
    FirstSet* set;
    set->cardinality = 0;
    set->total_cardinality = 4;
    set->symbols = malloc(sizeof(Symbol *) * set->total_cardinality);
    for (int i = dot; i < item.production.len_rhs; i++)
    {
        Symbol s;
        Get_Symbol(parse_items->symbol_table, item.production.rhs[i], s);
        FirstSet* s_set = Get_First_Set(parse_items->firsts_table, &s);
        for (int item = 0; item < s_set->cardinality; item++)
        {
            Add_To_First_Set(set, s_set->symbols[item]);
        }
    }
    set->key = set->symbols[0];
    return set;
}

void Items(LR1ItemSetTable* lr1_items_table, Parser_Items* parser_items)
{
    lr1_items_table->cardinality = 0;
    lr1_items_table->total_cardinality = 16;
    lr1_items_table->sets = malloc(sizeof(LR1ItemSet*) * lr1_items_table->total_cardinality);

    LR1Item init;
    init.dot_pos = 0;
    init.production = parser_items->prod_salver->productions[0];
    init.lookahead = parser_items->symbol_table->symbols[parser_items->symbol_table->len_table - 1];

    LR1ItemSet* init_set;
    init_set->cardinality = 0;
    init_set->total_cardinality = 64;
    init_set->items = malloc(sizeof(LR1ItemSet*) * init_set->total_cardinality);
    init_set->items[init_set->cardinality++] = init;

    lr1_items_table->sets[0] = Clousure(init_set, parser_items);
    bool changed = true;
    int index = 0;

    while (changed)
    {
        changed = false;
        LR1ItemSet set = lr1_items_table->sets[index];
        for (int s = 0; s < parser_items->symbol_table->len_table; s++)
        {
            LR1ItemSet go_to = GoTo(&set, parser_items->symbol_table->symbols[s], parser_items);
            if(go_to.cardinality > 0)
            {
                changed = Add_To_LR1Items_Set_Table(lr1_items_table, go_to);
            }
        }
    }
}

bool Add_To_LR1Items_Set(LR1ItemSet* set, LR1Item item)
{
    if (set->cardinality >= set->total_cardinality)
    {
        set->total_cardinality *= 2;
        set->items = realloc(set->items, sizeof(LR1Item *) * set->total_cardinality);
    }
    for (int i = 0; i < set->cardinality; i++)
    {
        if(Equals_LR1Item(set->items[i], item)) return false;
    }
    set->items[set->cardinality++] = item;
    return true;
}

bool Add_To_LR1Items_Set_Table(LR1ItemSetTable* table, LR1ItemSet set)
{
    if (table->cardinality >= table->total_cardinality)
    {
        table->total_cardinality *= 2;
        table->sets = realloc(table->sets, table->total_cardinality);
    }
    for (int i = 0; i < table->cardinality; i++)
    {
        if(Equals_LR1Item_Set(&table->sets[i], &set)) return false;
    }
    table->sets[table->cardinality++] = set;
    return true;
}

bool Equals_LR1Item_Set(LR1ItemSet* set1, LR1ItemSet* set2)
{
    if(set1->cardinality != set2->cardinality) return false;
    for (int i = 0; i < set1->cardinality; i++)
    {
        if(!Equals_LR1Item(set1->items[i], set2->items[i])) return false;
    }
    return true;
}

bool Equals_LR1Item(LR1Item item1, LR1Item item2)
{
    return Equals_Productions(&item1.production, &item2.production) 
        && Equals_Symbols(&item1.lookahead, &item2.lookahead);
}