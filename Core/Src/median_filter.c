#include "median_filter.h"
#include <string.h>

void MedianFilter_Init(MedianFilter_t *filter) {
    memset(filter->buffer, 0, sizeof(filter->buffer));
    filter->index = 0;
    filter->count = 0;
}

int16_t MedianFilter_Update(MedianFilter_t *filter, int16_t new_value) {
    filter->buffer[filter->index] = new_value;
    filter->index = (filter->index + 1) % MEDIAN_WINDOW_SIZE;
    if (filter->count < MEDIAN_WINDOW_SIZE) {
        filter->count++;
    }

    // Copy to temp buffer for sorting
    int16_t temp[MEDIAN_WINDOW_SIZE];
    uint8_t sort_size = filter->count;
    for (uint8_t i = 0; i < sort_size; i++) {
        temp[i] = filter->buffer[i];
    }

    // Insertion sort
    for (uint8_t i = 1; i < sort_size; i++) {
        int16_t key = temp[i];
        int8_t j = i - 1;
        while (j >= 0 && temp[j] > key) {
            temp[j + 1] = temp[j];
            j = j - 1;
        }
        temp[j + 1] = key;
    }

    // Return median
    return temp[sort_size / 2];
}
