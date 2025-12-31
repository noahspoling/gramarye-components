#ifndef BAR_VALUE_H
#define BAR_VALUE_H 

#include <stdbool.h>

#define BAR_VALUE_DEFAULT_MAX 100.0f

typedef struct BarValue {
    float value;
    float maxValue;
} BarValue;

#endif // BAR_VALUE_H