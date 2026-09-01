#ifndef FOREACH
#define FOREACH
 
#include <stdio.h>
#include <stdlib.h>

#define foreach( iter__, head__ ) \
  for ( iter__ = (head__); iter__ != 0; iter__ = iter__->next )

#endif