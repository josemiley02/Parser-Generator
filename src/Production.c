#include "../includes/Global/Production.h"

#define INIT_CAPACITY 8

void Init_Production_Salver(ProductionSalver* salver)
{
    salver->productions = malloc(INIT_CAPACITY * sizeof(Production));
    salver->len_productions = 0;
    salver->capacity = INIT_CAPACITY;
}

Production Create_Production(char* lhs, char** rhs, int len_rhs)
{
    Production p;
    p.lhs = strdup(lhs);
    p.len_rhs = len_rhs;
    p.rhs = malloc(sizeof(char*) * len_rhs);
    for (int i = 0; i < len_rhs; i++)
    {
        p.rhs[i] = strdup(rhs[i]);
    }
    return p;
}

void Save_Production(ProductionSalver* salver, Production prod)
{
    if(salver->len_productions >= salver->capacity)
    {
        salver->capacity *= 2;
        salver->productions = realloc(salver->productions, sizeof(Production) * salver->capacity);
    }
    salver->productions[salver->len_productions++] = prod;
}

void Free_Production(Production* prod)
{
    if(prod->lhs) free(prod->lhs);
    for (int i = 0; i < prod->len_rhs; i++)
    {
        if(prod->rhs[i]) free(prod->rhs[i]);
    }
    prod->len_rhs = 0;
    free(prod->rhs);
}

void Free_Production_Salver(ProductionSalver* salver)
{
    for (int i = 0; i < salver->len_productions; i++)
    {
        Free_Production(&salver->productions[i]);
    }
    free(salver->productions);
    salver->productions = NULL;
    salver->len_productions = 0;
    salver->capacity = 0;
}

void Print_Productions(const ProductionSalver* salver)
{
    for (int i = 0; i < salver->len_productions; ++i) {
        printf("%s -> ", salver->productions[i].lhs);
        for (int j = 0; j < salver->productions[i].len_rhs; ++j) {
            printf("%s ", salver->productions[i].rhs[j]);
        }
        if (salver->productions[i].len_rhs == 0)
            printf("ε");
        printf("\n");
    }
}

bool Equals_Productions(Production* p1, Production* p2)
{
    if(p1->len_rhs != p2->len_rhs) return false;
    if(strcmp(p1->lhs, p2->lhs) != 0) return false;
    for (int i = 0; i < p1->len_rhs; i++)
    {
        if(strcmp(p1->rhs[i], p2->rhs[i]) != 0) return false;
    }
    return true;
}

ProductionSalver* Get_Productions(char* lhs, ProductionSalver* salver)
{
    ProductionSalver result_salver;
    result_salver.len_productions = 0;
    result_salver.capacity = salver->len_productions;
    for (int i = 0; i < salver->len_productions; i++)
    {
        if(strcmp(salver->productions[i].lhs, lhs))
        {
            result_salver.productions[result_salver.len_productions++] = salver->productions[i];
        }
    }
    return &result_salver;
}