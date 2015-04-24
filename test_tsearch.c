#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <search.h>

typedef struct
{
      char* key;
      int value;
} intStrMap;

int lookup_compare(const void* l, const void* r)
{

    const intStrMap *lm = l;
    const intStrMap *lr = r;
    return strcmp(lm->key, lr->key);

}

int insert_compare(const void* l, const void* r)
{
    // always put after
    return -1;
}

void freeStructMemory(void *mt_data)
{
    intStrMap* m = mt_data;
    if(!m) {
        return;
    }
    free(mt_data);
    return;
}

void walker(const void *node, const VISIT which, const int depth) {
  intStrMap *f;
  f = *(intStrMap **)node;

   switch (which) {
   case preorder:
       break;
   case postorder:
       printf("%s: %d\n", f->key, f->value);
       break;
   case endorder:
       break;
   case leaf:
       printf("%s: %d\n", f->key, f->value);
       break;
   }
}


void* root = NULL;

int main(int argc, char **argv)
{

    /* 
     * insertions 
     */

    printf("Insert with tsearch\n");

    intStrMap* a1 = malloc(sizeof(intStrMap));
    a1->key = strdup("three");
    a1->value = 3;
    tsearch(a1, &root, insert_compare); /* insert */

    intStrMap* a2 = malloc(sizeof(intStrMap));
    a2->key = strdup("two");
    a2->value = 2;
    tsearch(a2, &root, insert_compare); /* insert */

    intStrMap* a3 = malloc(sizeof(intStrMap));
    a3->key = strdup("one");
    a3->value = 1;
    tsearch(a3, &root, insert_compare); /* insert */

    /* 
     * lookup 
     */

     printf("Lookup with tfind\n");

    // failure case
    intStrMap* find_a1 = malloc(sizeof(intStrMap));
    find_a1->key = strdup("lolitos");

    void* r1 = tfind(find_a1, &root, lookup_compare); /* read */
    if( r1 != NULL)
        printf("%d\n", (*(intStrMap**)r1)->value);

    // success case
    intStrMap* find_a2 = malloc(sizeof(intStrMap));
    find_a2->key = strdup("three");

    void* r2 = tfind(find_a2, &root, lookup_compare); /* read */
    if( r2 != NULL)
        printf("%d\n", (*(intStrMap**)r2)->value);

    /* 
     * print all 
     */

    printf("Print with twalk\n");
    twalk(root, walker);   

    /* 
     * deletion 
     */

    /*
    printf("Free with tdestroy\n");
    tdestroy(root, freeStructMemory);
    tdestroy(root, free);
    */

    return 0;
}