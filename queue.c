/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->list_count = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q != NULL) {
        list_ele_t *itr = q->head;
        while (q->head != NULL) {
            itr = q->head;
            if (q->head->value != NULL) {
                free(q->head->value);
            }
            q->head = q->head->next;
            free(itr);
        }
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }


    newh = (list_ele_t *) malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    if (newh == NULL) {
        return false;
    }
    newh->value = malloc(strlen(s) + 1);

    /* What if either call to malloc returns NULL? */
    strcpy(newh->value, s);

    // Check if the queue is empty
    // If empty then assign the new node to both head and tail
    if (q->tail == NULL) {
        q->tail = newh;
    }

    newh->next = q->head;
    q->head = newh;
    q->list_count++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;

    if (q == NULL) {
        return false;
    }

    newh = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }

    newh->value = malloc(strlen(s) + 1);

    strcpy(newh->value, s);

    if (q->head == NULL || q->tail == NULL) {
        q->head = newh;
    } else {
        q->tail->next = newh;
    }
    newh->next = NULL;
    q->tail = newh;
    q->list_count++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL) {
        return false;
    }

    if (sp != NULL) {
        int length = strlen(q->head->value);
        if (length > bufsize - 1) {
            strncpy(sp, q->head->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        } else {
            strncpy(sp, q->head->value, length);
            sp[length] = '\0';
        }
    }
    // int i = 0;
    // for(i = 0; q->head->value[i] != '\0' && i < bufsize; i++) {
    //     sp[i] = q->head->value[i];
    // }
    list_ele_t *temp = q->head;
    q->head = q->head->next;
    free(temp->value);
    free(temp);
    q->list_count--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q->head == NULL) {
        return 0;
    }
    return q->list_count;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q != NULL && q->head != NULL && q->head->next != NULL) {
        list_ele_t *itr1 = q->head;
        list_ele_t *itr2 = q->head->next;
        list_ele_t *temp;

        q->tail = itr1;
        while (itr2 != NULL) {
            temp = itr2->next;
            itr2->next = itr1;
            itr1 = itr2;
            itr2 = temp;
        }
        q->head = itr1;
        q->tail->next = NULL;
    }
}
