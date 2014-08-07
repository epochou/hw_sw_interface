/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size =
    cache size =
    associativity =
mystery1:
    block size =
    cache size =
    associativity =
mystery2:
    block size =
    cache size =
    associativity =
mystery3:
    block size =
    cache size =
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  addr_t  addr = 0;
  access_cache(addr);
  while(access_cache(++addr)) {	  
  }
  return addr;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  /* YOUR CODE GOES HERE */
  int blockSize = get_block_size();
  int b = 1;
  int cacheSize = blockSize;
  flush_cache();
  access_cache(0);
  while(b) {
	  addr_t addr = 0;
	  while( addr <= cacheSize ) {
		  access_cache(addr);
		  addr = addr + blockSize;
	  }
	  if(!access_cache(0)) {
		  b = 0;
	  }
	  else {
		  cacheSize = cacheSize + blockSize;
		  flush_cache();
	  }  
  }
  return cacheSize;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  access_cache(0);
  int assoc = 1;
  int cacheSize = get_cache_size(0);
  int temp;
  int b = 1;
  while(b) {
	  temp = assoc * cacheSize;
	  addr_t addr = 0;
	  while(addr <= temp) {
		  access_cache(addr);
		  addr = addr + cacheSize;
	  }
	  if(!access_cache(0)) {
		  b = 0;
	  }
	  else {
		  assoc++;
		  flush_cache();
	  }
  }
  return assoc;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
