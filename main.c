#include "includes/Global/Read_Grammar.h"
#include "includes/Global/Symbol.h"
#include "includes/Global/First.h"
#include "includes/Global/Follow.h"

#include "includes/Core/LR1Item.h"

int main() {
    ProductionSalver salver;
    Init_Production_Salver(&salver);
    
    Load_Grammar_From_File("./grammar/hulk_grammar.txt", &salver);

    // for (int i = 0; i < salver.len_productions; ++i) {
    //     Production p = salver.productions[i];
    //     printf("%s -> ", p.lhs);
    //     for (int j = 0; j < p.len_rhs; ++j) {
    //         printf("%s ", p.rhs[j]);
    //     }
    //     printf("\n");
    // }

    SymbolTable table;
    Init_Symbol_Table(&table, &salver);

    // for (int i = 0; i < table.len_table; i++)
    // {
    //     Symbol s = table.symbols[i];
    //     printf("%-10s : %s\n", s.Name, s.IsTerminal ? "Terminal" : "No Terminal");
    // }
    
    FirstSetTable set_table;
    Init_Set_Table(&set_table, &table, &salver);

    for (int i = 0; i < set_table.len_sets; i++)
    {
        FirstSet set = set_table.sets[i];
        printf("First(%s) = {", set.key.Name);
        for (int j = 0; j < set.cardinality; j++)
        {
            printf("%s, ",set.symbols[j].Name);
        }
        printf("} \n");
    }
    
    // FollowSetTable follow_table;
    // Init_Follow_Set_Table(&follow_table, &set_table, &table, &salver);

    // for (int i = 0; i < follow_table.len_sets; i++)
    // {
    //     FollowSet set = follow_table.sets[i];
    //     printf("Follow(%s) = {", set.key->Name);
    //     for (int j = 0; j < set.cardinality; j++)
    //     {
    //         printf("%s, ",set.symbols[j]->Name);
    //     }
    //     printf("} \n");
    // }

    // Parser_Items parser_items;
    // Init_Parser_Items(&parser_items, &salver, &table, &set_table, &follow_table);
    
    // LR1ItemSetTable lr1_set_table;
    // Items(&lr1_set_table, &parser_items);

    Free_Production_Salver(&salver);
    Free_Symbol_Table(&table);
    Free_Set_Table(&set_table);
    // Free_Follow_Set_Table(&follow_table);
    return 0;
}
