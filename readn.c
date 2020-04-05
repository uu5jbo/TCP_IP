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
            return 0;       //return the error code
        }
        if( rc == 0 )       //end of file?
            return len - cnt;   //return incomplete counter
        buffer += rc;
        cnt -= rc;
    }
    return len;
}
