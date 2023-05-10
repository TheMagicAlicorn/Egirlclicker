#include <stdint.h>

#ifndef DB_H
#define DB_H

int db_init();
int db_save(uint64_t egirls, uint64_t daddy, uint64_t catears);
int db_newsave(uint64_t egirls, uint64_t daddy, uint64_t catears);
int db_close();

extern uint64_t savedEgirls;
extern uint64_t savedDaddy;
extern uint64_t savedCatears;

#endif