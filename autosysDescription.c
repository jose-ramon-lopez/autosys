/*
AutoSys deja programar una librería para forzar ciertos estándares. en este caso para forzar que haya una descripción en la definición del job.
El ejemplo está sacado de la web de broadcom. He decidido no comentarlo ya que no soy un programador de C y no quiero dar información falsa en los comentarios del script por desconocimiento. Aunque podeís mandarme un correo con alguna duda.

    Paso 1: Compilar el fichero c
        gcc -c -fPIC description.c -o autoextvj.o
        gcc -shared -o libautoextvj.so autoextvj.o
    Paso 2: Copiar libautoextvj.so a $AUTOSYS/lib
        cp libautoextvj.so $AUTOSYS/lib

*/

#include <stdio.h>
#include <string.h>
#include "autoextvj.h"


AUTOEXTVJ_RET AUTOEXTVJ_ValidateJob(AUTOEXTVJ_JILKEYVAL *pJob, AUTOEXTVJ_JOBINFO *pJobInfo, AUTOEXTVJ_CALLBACK_ROUTINES Callbacks, AUTOEXTVJ_MSG *ppReturnMsg)
{
  int return_code = 0;
  PAUTOEXTVJ_JILKEYVAL pJilKv;

  if( pJobInfo->action == EXTVJ_INSERT || pJobInfo->action == EXTVJ_UPDATE )
    pJilKv = Callbacks.pfnFindJilKeyVal(pJob, "description");


  if( pJilKv ) {
    return_code = AUTOEXTVJ_VALIDATED;
  } else {
    return_code = AUTOEXTVJ_DENIED;
  }

  return return_code;

}

