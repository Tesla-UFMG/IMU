#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <stdint.h>

#define MEDIAN_WINDOW_SIZE 5

typedef struct {
    int16_t buffer[MEDIAN_WINDOW_SIZE];
    uint8_t index;
    uint8_t count;
} MedianFilter_t;

void MedianFilter_Init(MedianFilter_t *filter);
int16_t MedianFilter_Update(MedianFilter_t *filter, int16_t new_value);

#endif // MEDIAN_FILTER_H
