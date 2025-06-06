#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Production
{
    char* lhs;
    char** rhs;
    int len_rhs;
}Production;

typedef struct ProductionSalver
{
    Production* productions;
    int len_productions;
    int capacity;
}ProductionSalver;

Production Create_Production(char* lhs, char** rhs, int len_rhs);
void Save_Production(ProductionSalver* salver, Production prod);
void Init_Production_Salver(ProductionSalver* salver);
void Free_Production(Production* prod);
void Free_Production_Salver(ProductionSalver* salver);
void Print_Productions(const ProductionSalver* salver);
#endif