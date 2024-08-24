#include "etcp.h"

SOCKET tcp_client( char *hname, char *sname )
{
    struct sockaddr_in peer;
    SOCKET s;

    set_address( hname, sname, &peer, "tcp" );
    s = socket( AF_INTE, SOCK_STREAM, 0 );
    if( !isvalidsock( s ) )
        error( 1, errno, "socket() error" );
    
    if( connect( s, (struct sockaddr*)&peer,
                sizeof( peer ) ) )
        error( 1, errno, "connect() error" );
    return s;
}
