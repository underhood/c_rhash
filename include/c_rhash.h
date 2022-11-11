#include <sys/types.h>
#include <stdint.h>

#ifndef DEFAULT_BIN_COUNT
    #define DEFAULT_BIN_COUNT 1000
#endif

#define ITEMTYPE_UNSET      (0x0)
#define ITEMTYPE_STRING     (0x1)
#define ITEMTYPE_UINT8      (0x2)
#define ITEMTYPE_OPAQUE_PTR (0x3)

typedef struct c_rhash_s *c_rhash;

c_rhash c_rhash_new(size_t bin_count);

void c_rhash_destroy(c_rhash hash);

int c_rhash_insert_str_ptr(c_rhash hash, const char *key, void *value);
int c_rhash_insert_str_uint8(c_rhash hash, const char *key, uint8_t value);

int c_rhash_get_ptr_by_str(c_rhash hash, const char *key, void **ret_val);
int c_rhash_get_uint8_by_str(c_rhash hash, const char *key, uint8_t *ret_val);

typedef struct {
    size_t bin;
    struct bin_item *item;
    int initialized;
} c_rhash_iter_t;

#define C_RHASH_ITER_T_INITIALIZER { .bin = 0, .item = NULL, .initialized = 0 }

/* 
 * goes trough whole hash map and returns every
 * type uint64 key present/stored
 * 
 * it is not necessary to finish iterating and iterator can be reinitialized
 * there are no guarantees on the order in which the keys will come
 * behavior here is implementation dependent and can change any time
 * 
 * returns:
 *     0 for every key and stores the key in *key
 *     1 on error or when all keys of this type has been already iterated over
 */
int c_rhash_iter_uint64_keys(c_rhash hash, c_rhash_iter_t *iter, uint64_t *key);
