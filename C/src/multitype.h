#ifndef MULTITYPE_H
#define MULTITYPE_H

#include <stdbool.h>

enum TypeTag { CharType, StringType, IntType, PointerType, NullType };

union MultiTypeValue { char c; int i; char* s; void* p; };

typedef struct MultiType {
    enum TypeTag type;
    union MultiTypeValue value;
} MultiType;

extern const MultiType MULTI_NULL;

extern bool multi_is_equal(MultiType m1, MultiType m2);

extern char* multi_to_string(MultiType m);

extern MultiType multi_int(int object);

extern MultiType multi_char(char object);

extern MultiType multi_string(char* object);

extern MultiType multi_pointer(void* object);

#if __STDC_VERSION__ >= 201112L //  C11 support
    // _Generic is a C11 feature
    #define multi(object) _Generic((object), \
        int: multi_int, \
        char: multi_char, \
        char*: multi_string, \
        void*: multi_pointer
    )((object))
#endif

#endif // MULTITYPE_H