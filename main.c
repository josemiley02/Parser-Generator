#include "includes/Read_Grammar.h"
#include "includes/Symbol.h"

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

    for (int i = 0; i < table.len_table; i++)
    {
        Symbol s = table.symbols[i];
        printf("%-10s : %s\n", s.Name, s.IsTerminal ? "Terminal" : "No Terminal");
    }
    

    Free_Production_Salver(&salver);
    Free_Symbol_Table(&table);
    return 0;
}
