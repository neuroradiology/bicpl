#ifndef  DEF_PRIORITY_QUEUE
#define  DEF_PRIORITY_QUEUE

#include  <def_arrays.h>

/* ----------------------------- MNI Header -----------------------------------
@NAME       : def_priority_queue.h
@INPUT      :
@OUTPUT     :
@RETURNS    :
@DESCRIPTION: Macros for maintaining priority queues of any element type.
@METHOD     : The linear array representation of a binary heap is used to
            : to allow logarithmic insertions of any value and deletion
            : of the top element
@GLOBALS    :
@CALLS      :
@CREATED    :                      David MacDonald
@MODIFIED   :
---------------------------------------------------------------------------- */

/* ----------------------------- MNI Header -----------------------------------
@NAME       : PRIORITY_QUEUE_STRUCT
@INPUT      : type
@OUTPUT     :
@RETURNS    :
@DESCRIPTION: Macro to define a priority queue of elements of type 'type'.
@METHOD     :
@GLOBALS    :
@CALLS      :
@CREATED    :                      David MacDonald
@MODIFIED   :
---------------------------------------------------------------------------- */

#define  PRIORITY_QUEUE_STRUCT( type ) \
         struct \
         { \
             int      n_alloced; \
             int      n_entries; \
             Real     *priorities; \
             type     *entries; \
         }

/* ----------------------------- MNI Header -----------------------------------
@NAME       : INITIALIZE_PRIORITY_QUEUE
@INPUT      : q
@OUTPUT     :
@RETURNS    :
@DESCRIPTION: Macro to initialize a priority queue to empty.
@METHOD     :
@GLOBALS    :
@CALLS      :
@CREATED    :                      David MacDonald
@MODIFIED   :
---------------------------------------------------------------------------- */

#define  INITIALIZE_PRIORITY_QUEUE( q ) \
         { \
             (q).n_alloced = 0; \
             (q).n_entries = 1; \
             (q).priorities = 0; \
             (q).entries = 0; \
         }

/* ----------------------------- MNI Header -----------------------------------
@NAME       : INSERT_IN_PRIORITY_QUEUE
@INPUT      : q
            : entry              - element to insert
            : priority           - priority of the element
@OUTPUT     : status
@RETURNS    :
@DESCRIPTION: Macro to insert an entry in the priority queue.
@METHOD     :
@GLOBALS    :
@CALLS      :
@CREATED    :                      David MacDonald
@MODIFIED   :
---------------------------------------------------------------------------- */

#define  INSERT_IN_PRIORITY_QUEUE( status, q, entry, priority ) \
         { \
             int  save_n_alloced; \
             save_n_alloced = (q).n_alloced; \
             SET_ARRAY_SIZE( status, (q).entries, (q).n_alloced, \
                             (q).n_entries+1, DEFAULT_CHUNK_SIZE ); \
             if( status == OK ) \
             { \
                 SET_ARRAY_SIZE( status, (q).priorities, save_n_alloced, \
                                 (q).n_entries+1, DEFAULT_CHUNK_SIZE ); \
             } \
\
             if( status == OK ) \
             { \
                 int  _index, _next_index; \
\
                 _index = (q).n_entries; \
\
                 while( _index > 1 ) \
                 { \
                     _next_index = _index >> 1; \
                     if( (q).priorities[_next_index] > priority ) \
                         break; \
                     (q).priorities[_index] = (q).priorities[_next_index]; \
                     (q).entries[_index] = (q).entries[_next_index]; \
                     _index = _next_index; \
                 } \
 \
                 (q).priorities[_index] = priority; \
                 (q).entries[_index] = entry; \
         \
                 ++(q).n_entries; \
 \
                 (q).n_alloced = (q).n_entries; \
             } \
         }

/* ----------------------------- MNI Header -----------------------------------
@NAME       : NUMBER_IN_PRIORITY_QUEUE
@INPUT      : q
@OUTPUT     :
@RETURNS    :
@DESCRIPTION: Returns the number of entries in the priority queue.
@METHOD     :
@GLOBALS    :
@CALLS      :
@CREATED    :                      David MacDonald
@MODIFIED   :
---------------------------------------------------------------------------- */

#define  NUMBER_IN_PRIORITY_QUEUE( q )  ((q).n_entries - 1)

/* ----------------------------- MNI Header -----------------------------------
@NAME       : IS_PRIORITY_QUEUE_EMPTY
@INPUT      :
@OUTPUT     :
@RETURNS    : TRUE or FALSE
@DESCRIPTION: Returns TRUE if the priority queue is empty
@METHOD     :
@GLOBALS    :
@CALLS      :
@CREATED    :                      David MacDonald
@MODIFIED   :
---------------------------------------------------------------------------- */

#define  IS_PRIORITY_QUEUE_EMPTY( q )  (NUMBER_IN_PRIORITY_QUEUE(q) == 0)

/* ----------------------------- MNI Header -----------------------------------
@NAME       : REMOVE_FROM_QUEUE
@INPUT      : q
@OUTPUT     : entry
@RETURNS    :
@DESCRIPTION: Removes the first entry (highest priority) from the queue,
            : and stores it in 'entry'.
            : Then it shifts up entries in logarithmic time.
@METHOD     :
@GLOBALS    :
@CALLS      :
@CREATED    :                      David MacDonald
@CALLS      :
@CREATED    :                      David MacDonald
@MODIFIED   :
---------------------------------------------------------------------------- */

#define  REMOVE_FROM_PRIORITY_QUEUE( q, entry, priority ) \
         { \
             if( !IS_PRIORITY_QUEUE_EMPTY(q) ) \
             { \
                 int  _index, _next_index; \
 \
                 entry = (q).entries[1]; \
                 priority = (q).priorities[1]; \
 \
                 _index = 1; \
                 _next_index = 2; \
 \
                 while( _next_index < (q).n_entries ) \
                 { \
                     if( _next_index+1 < (q).n_entries && \
                         (q).priorities[_next_index+1] > \
                         (q).priorities[_next_index] ) \
                     { \
                         ++_next_index; \
                     } \
 \
                     if( (q).priorities[(q).n_entries-1] >= \
                         (q).priorities[_next_index] ) \
                     { \
                         break; \
                     } \
                     else \
                     { \
                         (q).priorities[_index] = (q).priorities[_next_index]; \
                         (q).entries[_index] = (q).entries[_next_index]; \
 \
                         _index = _next_index; \
                         _next_index <<= 1; \
                     } \
                 } \
 \
                 if( (q).n_entries > 2 ) \
                 { \
                     (q).priorities[_index] = (q).priorities[(q).n_entries-1]; \
                     (q).entries[_index] = (q).entries[(q).n_entries-1]; \
                 } \
 \
                 --(q).n_entries; \
             } \
         }

/* ----------------------------- MNI Header -----------------------------------
@NAME       : DELETE_PRIORITY_QUEUE
@INPUT      : q
@OUTPUT     : status
@RETURNS    :
@DESCRIPTION: Deletes the priority queue.
@METHOD     :
@GLOBALS    :
@CALLS      :
@CREATED    :                      David MacDonald
@MODIFIED   :
---------------------------------------------------------------------------- */

#define  DELETE_PRIORITY_QUEUE( status, q ) \
         { \
             if( (q).n_alloced > 0 ) \
             { \
                 FREE( status, (q).entries ) \
 \
                 if( status == OK ) \
                 { \
                     FREE( status, (q).priorities ) \
                 } \
             } \
             else \
             { \
                 status = OK; \
             } \
         }


#endif