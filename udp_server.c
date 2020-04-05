/*------------- udp_server.c ------------ */

#include "etcp.h"

SOCKET udp_server( char* hname, char* sname )
{
    SOCKET s;
    struct sockaddr_in local;

    set_address( hname, sname, "udp" );
    s = socket( AF_INET, SOCK_DGRAM, 0 );
    if( !isvalidsock( s ) )
        error( 1, errno, "socket() call error" );
    if( bind( s, ( struct sockaddr* )& local,
             sizeof( local ) ) )
    error( 1, errno, "bind() call error" );
    return s;
}
