#ifndef  DEF_HASH
#define  DEF_HASH

/* ----------------------------- MNI Header -----------------------------------
@NAME       : def_hash.h
@INPUT      : 
@OUTPUT     : 
@RETURNS    : 
@DESCRIPTION: Structures and definitions for the generic hash table routines.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    :                      David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

#include  <def_basic.h>

typedef  struct  hash_entry_struct
{
    char                         *data_ptr;
    struct   hash_entry_struct   *next;
    int                          keys[1];
} hash_entry_struct;

typedef  struct
{
    int                 n_keys;
    int                 size;
    int                 n_entries;
    Real                enlarge_threshold;
    Real                new_density;
    hash_entry_struct   **table;
} hash_table_struct;

typedef  struct
{
    int                current_index;
    hash_entry_struct  *current_entry;
} hash_table_pointer;

#endif
