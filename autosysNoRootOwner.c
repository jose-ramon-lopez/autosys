/*
    AutoSys deja programar una librería para forzar ciertos estándares.    en este caso para forzar que un job no se pueda crear/modificar con el owner root a través del WCC/jil/SDK.
    El script es una modificación de un ejemplo de la web de broadcom. He decidido no comentarlo ya que no soy un programador de C y no quiero dar información falsa en los comentarios del script por desconocimiento. Aunque podeís mandarme un correo con alguna duda.

    Paso 1: Compilar el fichero c
        gcc -c -fPIC description.c -o autoextvj.o
        gcc -shared -o libautoextvj.so autoextvj.o
    Paso 2: Copiar libautoextvj.so a $AUTOSYS/lib
        cp libautoextvj.so $AUTOSYS/lib
*/

#include "autoextvj.h"

/* Function:    AUTOEXTVJ_ValidateJob
   Description: User defined function which contains the custom job validation routine. Job attributes may be modified to
                satisfy any custom criteria prior to final validation by AutoSys.
   In:          pJobInfo - pointer to the AUTOEXTVJ_JOBINFO structre containing useful read-only information about
                the current job.

   In/Out:      pJil - pJil points to a list which contains the modifiable job attribute data.
                                The custom routine may update/add/delete any fields as it deems necessary to satisfy any custom job criteria.  The
                                following helper APIs are available to traverse the list and add/update/delete nodes:

                                        * pfnGetFirstJilKeyVal          -- returns a pointer to the first keyword/value node in the list or returns NULL if error.
                                        * pfnGetNextJilKeyVal           -- returns a pointer to the next node in the keyword/value list or returns NULL if error.
                                        * pfnGetPreviousJilKeyVal       -- returns a pointer to the previous node in the keyword/value list or returns NULL if error.
                                        * pfnAddJilKeyVal                       -- add a node to the end of the list.  Accepts any node in the list, then traverses to
                                                                                                        the end of the list and adds a new node.  Copies the passed keyword/value pair into
                                                                                                        the new node and returns a pointer to the added node.
                                    * pfnDeleteJilKeyVal                -- deletes the passed in node.  Returns 1 if successful, or 0 if unsuccessful.
                                    * pfnUpdateJilVal                   -- updates the value of the passed in node.  Returns 1 if successful, or 0 if unsuccessful.
                                        * pfnGetJilKeyword                      -- returns the jil keyword for the passed in node or returns NULL if error.
                                        * pfnGetJilValue                        -- returns the jil value for the passed in node or returns NULL if error.
                                        * pfnFindJilKeyVal                      -- returns a pointer to the node that contains the passed in
                                                                                                        keyword.  If the keyword is not found, a NULL pointer is returned.

                ppReturnMsg - pointer to a character byte-array that will be stuffed with any meaningful message that the custom
                              routine wishes to be displayed should the job fail or is modified to satisfy custom job criteria.
   Returns:     AUTOEXTVJ_VALIDATED - Indicates that the job satisfies custom criteria as-is without modifying any fields
                AUTOEXTVJ_DENIED    - Indicates that the job does not satisfy the custom criteria and must be rejected by AutoSys
                AUTOEXTVJ_MODIFIED  - Indicates that the job passed custom criteria after modifications.

                NOTE: If AUTOEXTVJ_VALIDATED is returned and any modifications are made to any of the job fields, AutoSys will
                automatically ignore any modifications (AUTOEXTVJ_MODIFIED should be returned). All job field modifications are subject to
                the native AutoSys job validation criteria.
*/
#define AUTOSYS_USER "root"

AUTOEXTVJ_RET AUTOEXTVJ_ValidateJob(AUTOEXTVJ_JILKEYVAL *pJob, AUTOEXTVJ_JOBINFO *pJobInfo, AUTOEXTVJ_CALLBACK_ROUTINES Callbacks, AUTOEXTVJ_MSG *ppReturnMsg)
{
        PAUTOEXTVJ_JILKEYVAL pJilKvOw = NULL;

        pJilKvOw = Callbacks.pfnFindJilKeyVal(pJob, "owner");

        if (strcmp(pJilKvOw->pValue, AUTOSYS_USER) == 0 )
        {
                strcat(*ppReturnMsg,"Job owner is root");
                fprintf(stdout, "%s\n", *ppReturnMsg);
                return AUTOEXTVJ_DENIED;
        }
        else
        {
                strcat(*ppReturnMsg,"Job owner is not root");
                fprintf(stdout, "%s\n", *ppReturnMsg);
                return AUTOEXTVJ_VALIDATED;

        }
}