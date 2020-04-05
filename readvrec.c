/* -------------------- readvrec.c ---------- */
#include "etcp.h"

int readvrec( SOCKET fd, char* buffer, size_t len )
{
    u_int32_t reclen;
    int rc;

    /* Read the length of the record */
    rc = readn( fd, ( char* )&reclen, sizeof( u_int32_t ) );
    if( rc != sizeof( u_int32_t ) )
        return ( rc < 0 ) ? -1 : 0;
    reclen = ntohl( reclen ); //transform the length into the host type
    if( reclen > len )
    {
        /* No room in the buffer for the data
        * discard them and return the error code
        */
        while( reclen > 0 )
        {
            rc = readn( fd, buffer, len );
            if( rc != len )
                return ( rc < 0 ) ? -1 : 0;
            reclen -= len;
            if( reclen < len )
                len = reclen;
        }
        set_errno( EMSGSIZE );
        return -1;
    }
    /* Read the record itself */
    rc = readn( fd, buffer, reclen );
    if( rc != reclen )
        return ( rc < 0 ) ? -1 : 0;
    return rc;
}
