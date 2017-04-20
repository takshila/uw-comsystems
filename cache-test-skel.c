/*
SAURABH SETH
CSE 410 - WINTER 2017
Lab 4 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 262144 bytes
    associativity = 1
mystery1:
    block size = 8 bytes
    cache size = 16384 bytes
    associativity = 4
mystery2:
    block size = 16 bytes
    cache size = 65536 bytes
    associativity = 16
mystery3:
    block size = 2 bytes
    cache size = 131072 bytes
    associativity = 2
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address.
 * You should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  int add = 0;
  access_cache(add);
  while(access_cache(add)){
     add++;
  }
  return add;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  int add = 0;
  access_cache(add);
  long int count = 1;
  int status = 1;
  while(status){
     access_cache(block_size*count);
     int temp = count;
     while(--temp >=0){
	if(!access_cache(block_size*temp)){
	   status = 0;
	}
     }
     count++;
  }	

  return block_size*(count-1);
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  int add = 0;
  access_cache(add);
  long int count = 1;
  int status = 1;
  while(status){
     access_cache(cache_size*count);
     int temp = count;
     while(--temp >=0){
        if(!access_cache(cache_size*temp)){
           status = 0;
        }
     }
     count++;
  }

  return count-1;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
