#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. The reference implementation added approximately
 *  110 lines of code to this file. This count includes lines containing
 *  only a single closing bracket (}).
 * <p>
 * @author <b>Your name</b> goes here
 */
 
/** size of LC3 memory */
#define LC3_MEMORY_capacity  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      capacity;        /**< capacity of hash table         */
  node_t** hash_table;  /**< array of linked list heads */
  char**   addr_table;  /**< look up symbols by addr    */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function */
sym_table_t* symbol_init (int capacity) {
	sym_table_t *table = malloc(sizeof(sym_table_t));
	table->capacity = capacity;
	table->hash_table = calloc(capacity, sizeof(node_t *));
	table->addr_table = calloc(LC3_MEMORY_capacity, sizeof(char *));
	return table;
}

/** @todo implement this function */
void symbol_add_unique (sym_table_t* symTab, const char* name, int addr) {
    char *myName = strdup(name);
    symbol_t *s = malloc(sizeof(symbol_t));
    s->name = myName;
    s->addr = addr;
    node_t *n = malloc(sizeof(node_t));
    n->hash = symbol_hash(myName);
    int index = n->hash % symTab->capacity;
    n->next = symTab->hash_table[index];
    n->symbol = *s;
    symTab->hash_table[index] = n;
    if (symTab->addr_table[addr]==NULL)
        symTab->addr_table[addr] = myName;
    free(s);
}

/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
    char *symbolName = symTab->addr_table[addr];    
    return symbolName;
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
    for (int i = 0; i<symTab->capacity; i++)
    {
        node_t *temp = symTab->hash_table[i];
        while (temp!=NULL)
        {
            symbol_t *mySymbol = &temp->symbol;
            (*fnc)(mySymbol, data);
            temp = temp->next;
        }
    }
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
    char *myName = strdup(name);
    *hash = symbol_hash(myName);
    *index = *hash%symTab->capacity;
    node_t* myNode = NULL;
    for (int i = 0; i<symTab->capacity; i++)
    {
        node_t *temp = symTab->hash_table[i];
        
        while (temp!=NULL)
        {
            if (temp->hash == *hash){
                if (strcasecmp(myName, temp->symbol.name)==0){
                    myNode = temp;
                    break;
                }
            }
            temp = temp->next;
        }
    }
    free(myName);
	return myNode;
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
    int hash;
    int index;
    if (symbol_search(symTab, name, &hash, &index)!=NULL){
        return 0;
    }
    symbol_add_unique(symTab, name, addr);
    return 1;
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
    int hash;
    int index;
    if (symbol_search(symTab, name, &hash, &index)!=NULL){
        node_t *n = symbol_search(symTab, name, &hash, &index);
        symbol_t r = n->symbol;
        symbol_t *result = &r;
        return result;
    }
    else
        return NULL;
}

/** @todo implement this function */
void symbol_reset(sym_table_t* symTab) {
    for (int i = 0; i<symTab->capacity; i++){
        node_t *temp = symTab->hash_table[i];
        while (temp!=NULL){
            int index = temp->hash % symTab->capacity;
            symTab->addr_table[index] = NULL;
            free(temp->symbol.name);
            node_t *n = temp;
            temp = temp->next;
            free(n);
        }
        
    }
}


/** @todo implement this function */
void symbol_term (sym_table_t* symTab) {
    symbol_reset(symTab);
    free(symTab->hash_table);
    free(symTab->addr_table);
    free(symTab);
}

/** @todo implement this function */
int symbol_size (sym_table_t* symTab) {
	int fin = 0;
	for (int i = 0; i<symTab->capacity; i++){
        node_t *temp = symTab->hash_table[i];
        while (temp!=NULL){
			fin++;
			temp = temp->next;
		}
	}
	return fin;
}

/** @todo implement this function */
int compare_names (const void* vp1, const void* vp2) {
  // symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
	symbol_t* sym1 = *((symbol_t**) vp1);
	symbol_t* sym2 = *((symbol_t**) vp2);
	return strcmp(sym1->name,sym2->name);
}

/** @todo implement this function */
int compare_addresses (const void* vp1, const void* vp2) {
	symbol_t* sym1 = *((symbol_t**) vp1);
	symbol_t* sym2 = *((symbol_t**) vp2);
	if(sym1->addr - sym2->addr != 0)
		return sym1->addr - sym2->addr;
	return compare_names(vp1,vp2);
}

/** @todo implement this function */
symbol_t** symbol_order (sym_table_t* symTab, int order) {
	// will call qsort with either compare_names or compare_addresses
	symbol_t** tempTable = calloc(symTab->capacity,sizeof(symbol_t *));
	int j = 0;
	for (int i = 0; i<symTab->capacity; i++){
		node_t *temp = symTab->hash_table[i];
		while (temp!=NULL){
			tempTable[j++] = &(temp->symbol);
			temp = temp->next;
		}
	}
	if(order==HASH) {
		return tempTable;
	}
	if(order==NAME) {
		qsort(*tempTable,symbol_size(symTab),sizeof(symbol_t),compare_names);
		return tempTable;
	}
	if(order==ADDR) {
		qsort(*tempTable,symbol_size(symTab),sizeof(symbol_t),compare_addresses);
		return tempTable;
	}
	return NULL;
}