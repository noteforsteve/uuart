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
	int 	ac, 
	char 	**av
	)
{
	int Retval = 0;
    uhandle_t hUart = 0;

	DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    printf("usage: uuart <port>\n");

    Retval = UartCtor(&hUart);
    CHECK_RETVAL(Retval, ExitOnFailure);

    Retval = UartOpen(hUart, 
                      av[1], 
                      UART_RATE_57600, 
                      UART_DATA_BITS_8, 
                      UART_PARITY_NONE, 
                      UART_STOP_1);
    CHECK_RETVAL(Retval, ExitOnFailure);

ExitOnFailure:

    UartClose(hUart);

    UartDtor(hUart);

	return Retval;
}

    
