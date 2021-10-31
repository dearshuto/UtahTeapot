#include <stdint.h>

extern "C" int get_value();

extern "C" void *create_instance();

extern "C" void destroy_instance(void *ptr);

extern "C" void update(void *ptr, uint8_t div, uint8_t subDiv);

extern "C" size_t get_vertex_count(void *ptr);

extern "C" void get_position(void *ptr, float *pOutX, float *pOutY,
                             float *pOutZ, size_t size);

extern "C" void get_normal(void *ptr, float *pOutX, float *pOutY, float *pOutZ,
                           size_t index);

extern "C" size_t get_index_count(void *ptr);

extern "C" uint32_t get_index(void *ptr, size_t index);