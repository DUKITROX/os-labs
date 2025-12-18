/*
 * Demonstrates a simple (and intentionally inefficient) bubble sort.
 * Defines a tiny array of items and sorts them by the key field before
 * printing the ordered contents to stdout.
 */
/*   1  */  #include <stdio.h>
/*   2  */  typedef struct {
/*   3  */      char data[4096];
/*   4  */      int key;
/*   5  */  } item;
/*   6  */  
/*   7  */  item array[] = {
/*   8  */      {"bill", 3},
/*   9  */      {"neil", 4},
/*  10  */      {"john", 2},
/*  11  */      {"rick", 5},
/*  12  */      {"alex", 1},
/*  13  */  };
/*  14  */  
/*  15  */  void sort(item *a, int n) { 
/*  16  */
/*  17  */      int i = 0, j = 0; /* loop indices for outer and inner passes */
/*  18  */      int s = 1;       /* swap counter: stops early if already sorted */
/*  19  */  
/*  20  */      for(; i < n & s != 0; i++) { /* outer loop shrinks unsorted tail */
/*  21  */              s = 0; /* reset swap count for this pass */
/*  22  */              for(j = 0; j < n; j++) { /* bubble the largest key to the end */
/*  23  */                      if(a[j].key > a[j+1].key) {
/*  24  */                              item t = a[j]; /* swap adjacent out-of-order items */
/*  25  */                              a[j] = a[j+1];
/*  26  */                              a[j+1] = t;
/*  27  */                              s++;
/*  28  */                      }
/*  29  */              }
/*  30  */              n--; /* last element now in place; exclude from next pass */
/*  31  */      }
/*  32  */  }
/*  33  */  
/*  34  */  int main()
/*  35  */  {
/*  36  */          int i;
/*  37  */          sort(array,5); /* sort the statically defined array */ 
/*  38  */          for(i = 0; i < 5; i++)
/*  39  */                  printf("array[%d] = {%s, %d}\n",
/*  40  */                          i, array[i].data, array[i].key);
/*  41  */          return 0;
/*  42  */  }
