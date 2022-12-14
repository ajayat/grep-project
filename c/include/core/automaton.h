#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <stdbool.h>

#include "hashtable.h"
#include "multitype.h"
#include "vector.h"

extern const char EPSILON;
extern const char ALPHABET[];

/**
 * Deterministic Finite Automaton
 */
typedef struct DFA {
    MultiType initial;
    Set* final;
    HashTable* _transitions;  // (state -> letter -> state)
} DFA;

extern DFA* dfa_create(MultiType initial);

extern void dfa_set_transition(DFA* dfa, MultiType state, char a, MultiType p);

extern MultiType dfa_delta(DFA* dfa, MultiType state, char a);

extern bool dfa_accept(DFA* dfa, char* word);

extern void dfa_free(DFA* dfa, bool deep);

/**
 * Non-deterministic Finite Automaton with epsilon transitions
 */
typedef struct NFA {
    Set* initial;
    Set* final;
    HashTable* _transitions;  // (state -> letter -> Set of state)
} NFA;

extern NFA* nfa_create(void);

extern void nfa_set_transition(NFA* nfa, MultiType state, char a, MultiType p);

extern Set* nfa_delta(NFA* nfa, MultiType state, char a);

extern bool nfa_accept(NFA* nfa, char* word);

extern void nfa_free(NFA* nfa, bool deep);

extern NFA* dfa_transpose(DFA* dfa);

extern DFA* nfa_determinize(NFA* nfa);

#endif  // AUTOMATON_H