#include "includes/Read_Grammar.h"

int main() {
    ProductionSalver salver;
    Init_Production_Salver(&salver);
    
    Load_Grammar_From_File("./hulk_grammar.txt", &salver);

    for (int i = 0; i < salver.len_productions; ++i) {
        Production p = salver.productions[i];
        printf("%s -> ", p.lhs);
        for (int j = 0; j < p.len_rhs; ++j) {
            printf("%s ", p.rhs[j]);
        }
        printf("\n");
    }

    Free_Production_Salver(&salver);
    return 0;
}
