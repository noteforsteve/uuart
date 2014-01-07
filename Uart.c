#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "Portable.h"
#include "Common.h"
#include "Uart.h"

#if OS_TYPE == OS_TYPE_WINDOWS
#include "WinUart.h"
#elif OS_TYPE == OS_TYPE_OSX
#include "OsxUart.h"
#endif

#define DEBUG_MODULE 
//#define DEBUG_LEVEL iDBG_TRACE|DBG_WARN|DBG_ERROR
#define DEBUG_LEVEL DBG_WARN|DBG_ERROR
#include "Debug.h"

#if OS_TYPE == OS_TYPE_WINDOWS
#pragma warning(disable: 4127)
#endif

int
UartCtor(
    OUT uhandle_t   *phUart
    )
{
    int Retval;

    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    Retval = phUart ? S_OK : E_INVALIDARG;
    CHECK_RETVAL(Retval, ExitOnFailure);

#if OS_TYPE == OS_TYPE_WINDOWS
    Retval = WinUartCtor(phUart);
#elif OS_TYPE == OS_TYPE_OSX
    Retval = OsxUartCtor(phUart);
#endif

ExitOnFailure:

    return Retval;
}

void
UartDtor(
    IN uhandle_t    hUart
    )
{
    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    if (hUart)
    {
        UartClose(hUart);

#if OS_TYPE == OS_TYPE_WINDOWS
        WinUartDtor(hUart);
#elif OS_TYPE == OS_TYPE_OSX
        OsxUartDtor(hUart);
#endif
    }
}

int
UartOpen(
    IN uhandle_t    hUart,
    IN const char   *pName,
    IN unsigned int uRate,
    IN unsigned int uDataBits,
    IN unsigned int uParity,
    IN unsigned int uStopBits
    )
{
    int Retval;

    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    Retval = hUart && pName ? S_OK : E_INVALIDARG;
    CHECK_RETVAL(Retval, ExitOnFailure);

#if OS_TYPE == OS_TYPE_WINDOWS
    Retval = WinUartOpen(hUart, pName, uRate, uDataBits, uParity, uStopBits);
#elif (OS_TYPE == OS_TYPE_OSX)
    Retval = OsxUartOpen(hUart, pName, uRate, uDataBits, uParity, uStopBits);
#endif

ExitOnFailure:

    return Retval;
}

void
UartClose(
    IN uhandle_t    hUart
    )
{
    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

#if OS_TYPE == OS_TYPE_WINDOWS
    WinUartClose(hUart);
#elif (OS_TYPE == OS_TYPE_OSX)
    OsxUartClose(hUart);
#endif
}

int
UartRead(
    IN uhandle_t    hUart,
    IO void         *pBuff, 
    IN unsigned int uLength, 
    OUT unsigned int *puRead,
    IN unsigned int uWaitTime
    )
{
    int Retval;

    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    Retval = hUart && pBuff ? S_OK : E_INVALIDARG;
    CHECK_RETVAL(Retval, ExitOnFailure);

    if (puRead) *puRead = 0;

#if OS_TYPE == OS_TYPE_WINDOWS
    Retval = WinUartRead(hUart, pBuff, uLength, puRead, uWaitTime);
#elif (OS_TYPE == OS_TYPE_OSX)
    Retval = OsxUartRead(hUart, pBuff, uLength, puRead, uWaitTime);
#endif

ExitOnFailure:

    return Retval;
}

int
UartWrite(
    IN uhandle_t    hUart,
    OUT const void  *pBuff,
    IN unsigned int uLength,
    OUT unsigned int *puWritten,
    IN unsigned int uWaitTime
    )
{
    int Retval;

    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    Retval = hUart && pBuff ? S_OK : E_INVALIDARG;
    CHECK_RETVAL(Retval, ExitOnFailure);

    if (puWritten) *puWritten = 0;

#if OS_TYPE == OS_TYPE_WINDOWS
    Retval = WinUartWrite(hUart, pBuff, uLength, puWritten, uWaitTime);
#elif (OS_TYPE == OS_TYPE_OSX)
    Retval = OsxUartWrite(hUart, pBuff, uLength, puWritten, uWaitTime);
#endif

ExitOnFailure:

    return Retval;
}

int
UartSetStatus(
    IN uhandle_t    hUart,
    IN unsigned int uState
    )
{
    int Retval;

    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    Retval = hUart ? S_OK : E_INVALIDARG;
    CHECK_RETVAL(Retval, ExitOnFailure);

#if OS_TYPE == OS_TYPE_WINDOWS
    Retval = WinUartSetStatus(hUart, uState);
#elif (OS_TYPE == OS_TYPE_OSX)
    Retval = OsxUartSetStatus(hUart, uState);
#endif

ExitOnFailure:

    return Retval;
}

int
UartGetStatus(
    IN uhandle_t    hUart,
    OUT unsigned int *puState
    )
{
    int Retval;

    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    Retval = hUart && puState ? S_OK : E_INVALIDARG;
    CHECK_RETVAL(Retval, ExitOnFailure);

#if OS_TYPE == OS_TYPE_WINDOWS
    Retval = WinUartGetStatus(hUart, puState);
#elif (OS_TYPE == OS_TYPE_OSX)
    Retval = OsxUartGetStatus(hUart, puState);
#endif

ExitOnFailure:

    return Retval;
}

int
UartSetTimeouts(
    IN uhandle_t    hUart,          /* Uart instance handle                     */
    IN unsigned int ReadTimeout,    /* Minimum read timeout period              */   
    IN unsigned int WriteTimeout    /* Minimum write timeout period             */
    )
{
    int Retval;

    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    /* The read and write timeout must be atleast 1 */
    Retval = hUart && ReadTimeout && WriteTimeout ? S_OK : E_INVALIDARG;
    CHECK_RETVAL(Retval, ExitOnFailure);

#if OS_TYPE == OS_TYPE_WINDOWS
    Retval = WinUartSetTimeouts(hUart, ReadTimeout, WriteTimeout);
#elif (OS_TYPE == OS_TYPE_OSX)
    Retval = OsxUartSetTimeouts(hUart, ReadTimeout, WriteTimeout);
#endif

ExitOnFailure:

    return Retval;
}

/*** Uart Test ****************************************************************/
#if defined (UART_TESTS)

/* Show state of modem status signals */ 
int 
UartTest(
    IN const char *pszPort
    )
{
    int Retval;
    uhandle_t hUart;
    unsigned int uStatus;
    char WriteBuff[256];
    char ReadBuff[256];
    unsigned int Len;
    unsigned int BytesRead; 
    unsigned int BytesWritten;
    unsigned int StartTick;

    DBG_MSG(DBG_TRACE, "%s\n", __FUNCTION__);

    printf("UartTest: Starting...\n");
    printf("UartTest: Signals must be in loop back configuration\n");
    printf("UartTest: TXD->RXD\n");
    printf("UartTest: RTS->CTS\n");
    printf("UartTest: DTR->DSR\n");

    Retval = UartCtor(&hUart);
    CHECK_RETVAL(Retval, ExitOnFailure);

    Retval = UartOpen(hUart, 
                      pszPort,
                      UART_RATE_57600, 
                      UART_DATA_BITS_8, 
                      UART_PARITY_NONE, 
                      UART_STOP_1);
    CHECK_RETVAL(Retval, ExitOnFailure);

    /* Create the loop back message */
    strcpy(WriteBuff, "Loop Back Message");
    Len = strlen(WriteBuff); 

    /* Send Loop back message */
    Retval = UartWrite(hUart, WriteBuff, Len, &BytesWritten, 1000);                        
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    
    
    /* Check the loop back message was sent */
    Retval = (Retval == S_OK && BytesWritten == Len) ? S_OK : E_FAIL;
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    /* Read the loop back message */
    Retval = UartRead(hUart, ReadBuff, sizeof(ReadBuff), &BytesRead, 1000);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    /* Check the read length matches the loop back message */
    Retval = (Retval == S_OK && BytesRead == Len) ? S_OK : E_FAIL;    
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    /* Check the contents of the loop back message was read correctly */
    Retval = memcmp(WriteBuff, ReadBuff, Len) ? E_FAIL : S_OK;
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    /* Set the status signals to a known state */
    Retval = UartSetStatus(hUart, UART_STATUS_SETRTS);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    Retval = UartSetStatus(hUart, UART_STATUS_SETDTR);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    /* Get the current modem state state */
    Retval = UartGetStatus(hUart, &uStatus);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    /* Check against known state */
    Retval = ((uStatus & UART_STATUS_MASK) == (UART_STATUS_CTS|UART_STATUS_DSR)) ? S_OK : E_FAIL;
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    Retval = UartSetStatus(hUart, UART_STATUS_CLRRTS);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    Retval = UartGetStatus(hUart, &uStatus);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    Retval = ((uStatus & UART_STATUS_MASK) == (UART_STATUS_DSR)) ? S_OK : E_FAIL;
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    Retval = UartSetStatus(hUart, UART_STATUS_CLRDTR);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    Retval = UartGetStatus(hUart, &uStatus);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    Retval = ((uStatus & UART_STATUS_MASK) == 0) ? S_OK : E_FAIL;
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    /* Test the set timeouts */
    Retval = UartSetTimeouts(hUart, 100, 100);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    StartTick = PortableGetTick();
    Retval = UartRead(hUart, ReadBuff, sizeof(ReadBuff), &BytesRead, 0);

    Retval = Retval == E_TIMEOUT ? S_OK : E_FAIL;
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    
    
    Retval = (PortableGetTick() - StartTick) < 150 ? S_OK : E_FAIL;
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    Retval = UartSetTimeouts(hUart, 500, 500);
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    StartTick = PortableGetTick();
    Retval = UartRead(hUart, ReadBuff, sizeof(ReadBuff), &BytesRead, 0);

    Retval = Retval == E_TIMEOUT ? S_OK : E_FAIL;
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

    Retval = (PortableGetTick() - StartTick) < 550 ? S_OK : E_FAIL;
    CHECK_RETVAL(Retval, ExitOnFailure);                                                    

ExitOnFailure:

    if (SUCCEEDED(Retval))
    {
        printf("UartTest: passed\n");
    }
    else
    {
        printf("UartTest: failed\n");
    }

    UartDtor(hUart);

    return Retval;
}

#endif


