/* 
    forzar un job a que ejecute un programa llamado m2p.pl

    Paso 1: Reiniciar el application server
        unicntrl restart waae_server.TST
    Paso 2: Compilar el fichero c
        gcc -c -fPIC description.c -o autoextvj.o
        gcc -shared -o libautoextvj.so autoextvj.o
    Paso 3: Copiar libautoextvj.so a $AUTOSYS/lib
        cp libautoextvj.so $AUTOSYS/lib
*/

#include 
#include 
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

AUTOEXTVJ_RET AUTOEXTVJ_ValidateJob(AUTOEXTVJ_JILKEYVAL *pJob, AUTOEXTVJ_JOBINFO *pJobInfo, AUTOEXTVJ_CALLBACK_ROUTINES Callbacks, AUTOEXTVJ_MSG *ppReturnMsg)
{

        PAUTOEXTVJ_JILKEYVAL pJilKvJn = NULL;
        pJilKvJn = Callbacks.pfnFindJilKeyVal(pJob, "job_name");


        PAUTOEXTVJ_JILKEYVAL pJilKvCo = NULL;
        pJilKvCo = Callbacks.pfnFindJilKeyVal(pJob, "command");

        if (strcmp(pJilKvJn->pValue, "m2p") == 0 )
        {
                strcat(*ppReturnMsg,"Move to production job!!");
                fprintf(stdout, "%s\n", *ppReturnMsg);

                if (strstr(pJilKvCo->pValue, "m2p.pl") != NULL)
                {
                        strcat(*ppReturnMsg," Running the right command!!");
                        fprintf(stdout, "%s\n", *ppReturnMsg);
                        return AUTOEXTVJ_VALIDATED;
                }
                else
                {
                        strcat(*ppReturnMsg, " Running the wrong command!!");
                        fprintf(stdout, "%s\n", *ppReturnMsg);
                        return AUTOEXTVJ_DENIED;
                }
        }
        else
        {
                return AUTOEXTVJ_VALIDATED;

        }

/*


        if (strcmp(pJilKvCo->pValue, AUTOSYS_JOB_NAME) == 0 )
        {
                strcat(*ppReturnMsg,"111111111111111111111111111111111111111");
                fprintf(stdout, "%s\n", *ppReturnMsg);

                if (strstr(pJilKvJn->pValue, AUTOSYS_COMMAND) != NULL)
                {
                        strcat(*ppReturnMsg,"222222222222222222222222222222222222222222222222");
                        fprintf(stdout, "%s\n", *ppReturnMsg);

                        return AUTOEXTVJ_VALIDATED;
                }
                else
                {
                        return AUTOEXTVJ_DENIED;
                }
                return AUTOEXTVJ_DENIED;
        }
        else
        {
                return AUTOEXTVJ_VALIDATED;
        }*/

}





