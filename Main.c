#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "Common.h"
#include "Uart.h"
#include "Portable.h"

#define DEBUG_MODULE
#define DEBUG_LEVEL DBG_TRACE|DBG_WARN|DBG_ERROR 
#include "Debug.h"

int 
main(
    int     ac, 
    char    **av
    )
{
    int Retval = 0;

    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    printf("usage: uuart <port>\n");

	Retval = ac == 2 ? S_OK : E_FAIL;
	CHECK_RETVAL(Retval, ExitOnFailure);

	Retval = UartTest(av[1]);
	CHECK_RETVAL(Retval, ExitOnFailure);

ExitOnFailure:

    return Retval;
}

    
