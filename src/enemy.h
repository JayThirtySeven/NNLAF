#ifndef enemy_h
#define enemy_h

typedef struct enemy_t enemy_t;

#include "rect.h"

struct enemy_t{
    rect_t *rect;
    rect_t *weapon;
    
    int32_t flashing;
};

enemy_t *enemy_create(void);
void enemy_init(enemy_t *enemy, double x, double y, double w, double h);
void enemy_delete(enemy_t *enemy);

#endif
