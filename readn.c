/*------------readn.c-----------*/
#include "etcp.h"

int readn( SOCKET fd, char* buffer, size_t len )
{
    int cnt;
    int rc;

    cnt = len;
    while( cnt > 0 )
    {
        rc = recv( fd, buffer, cnt, 0 );
        if( rc < 0 ) /* Ошибка чтения */
        {
            if( errno == EINTR ) // if the syscall intetrrupted
                continue;       // continue reading from the socket
            return -1;       //return the error code
        }
        if( rc == 0 )       //end of file?
            return len - cnt;   //return incomplete counter
        buffer += rc;    //shift buffer pointer by the number of bytes received
        cnt -= rc;       //decrease the counter by the number of bytes reeceived
    }
    return len;
}
