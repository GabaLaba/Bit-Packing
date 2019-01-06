/* NOTE: Not finished and not working version.
Posted here just for portfolio. Will update in
like a week or some shit                    */

#include <stdlib.h>
#include <math.h>

long strbts(byte *barr, ui32 len, int *pos){
   
   ui32 bits[50];
   int bt, ofs, ido, i, skp;
   long ret;
   int bb = BITSPERBYTE;
   
   if (len > sizeof(bits)/sizeof(ui32)){
      printf("Not enough space for 'bit' buffer."); /* replace w/ bits[] reallocation */      
      return -1;
   }
   for (i=0;i<len;i++){

      bt = *pos/bb;                       /* determine byte to read  */
      if ((len-(bb*bt)) <= bb)            /* bits need to be packed  */
         ofs = ((bb*bt)+len-1)-i;
      else                                /* bits fit into one byte  */
         ofs = ((bb*(bt+1)-1)-i+(bt*bb));
      
      ido = (len > ((bt+1)*bb)) ? 0 :     /* Determine shift amount  */ 
      bb*(bt+1)-len;     
      
      bits[ofs] = (barr[bt] >>            /* Place bits with offset  */
      ((*pos-bt*bb)+ido)) & 1;
      (*pos)++;

      if (bits[i] == 1)
         ret += pow(2, len-ofs);          /* Add to return value     */

   }

   /* Print bytes with spacing */
#if DUMP_STRBITS
   skp = 0;
   for (i=0;i<len;i++){
      if (skp == bb){
         printf("   ");
         skp = 1;
      }
      else skp++;      
      printf("%d", bits[i]);
   }
#endif

   /* Convert value to character string */

   return ret;
}
