/**
 * Implementation of a multi-type data structure to handle
 * variables of different types without using macros.
 * https://en.wikipedia.org/wiki/Tagged_union
 */

#include "multitype.h"

#include <stdbool.h>  // bool
#include <stdio.h>    // for printf, sprintf
#include <stdlib.h>
#include <string.h>  // strcmp

#include "hashtable.h"

const MultiType MULTI_NULL = {NullType, {.p = NULL}};

bool multi_is_equal(MultiType m1, MultiType m2)
{
    if (m1.type != m2.type)
        return false;

    switch (m1.type) {
        case CharType:
            return m1.value.c == m2.value.c;
        case StringType:
            return strcmp(m1.value.s, m2.value.s) == 0;
        case IntType:
            return m1.value.i == m2.value.i;
        case PointerType:
            return m1.value.p == m2.value.p;
        case HtblType:
            return hashtable_is_equal((Set*)m1.value.p, (Set*)m2.value.p);
        default:
            goto InvalidType;
    }
InvalidType:
    fprintf(stderr, "Type of arguments are invalid.\n");
    exit(EXIT_FAILURE);
}

char* multi_to_string(MultiType m)
{
    switch (m.type) {
        case IntType: {
            static char buffer[21];  // 4-bytes integer can be 20 digits long
            sprintf(buffer, "%d", m.value.i);
            return buffer;
        }
        case CharType: {
            static char buffer[2];  // 1 bit char + null terminator
            sprintf(buffer, "%c", m.value.c);
            return buffer;
        }
        case StringType:
            return m.value.s;

        case HtblType:
        case PointerType: {
            static char buffer[21];  // Pointer is a 8-bytes integer
            sprintf(buffer, "%p", m.value.p);
            return buffer;
        }
        default:
            goto InvalidType;
    }
InvalidType:
    fprintf(stderr, "MultiType value cannot be converted to string.\n");
    exit(EXIT_FAILURE);
}

inline MultiType multi_int(int i)
{
    return (MultiType){IntType, {.i = i}};
}

inline MultiType multi_char(char c)
{
    return (MultiType){CharType, {.c = c}};
}

inline MultiType multi_string(char* s)
{
    return (MultiType){StringType, {.s = s}};
}

inline MultiType multi_htbl(void* p)
{
    return (MultiType){HtblType, {.p = p}};
}

inline MultiType multi_pointer(void* p)
{
    return (MultiType){PointerType, {.p = p}};
}

void multi_free(MultiType m)
{
    if (m.type == HtblType)
        hashtable_free(m.value.p, true);
}