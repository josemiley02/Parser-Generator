#ifndef LR1ITEM_H
#define LR1ITEM_H
#include "Production.h"
typedef struct LR1Item
{
    Production* production;
    int dot_position;
    char* lookahead;
}LR1Item;

#endif