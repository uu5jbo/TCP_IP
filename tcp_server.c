/*----------- tcp_server.c ---------- */

#include "etcp.h"

//SOCKET tcp_server( char* hname, char* sname );

SOCKET s;

SOCKET tcp_server( char* hname, char* sname )
{
    struct sockaddr_in local;
    extern SOCKET s;
    const int on = 1;

    set_address( hname, sname, &local, "tcp" );
    s = socket( AF_INET, SOCK_STREAM, 0 );
    if( !isvalidsock( s ) )
        error( 1, errno, "socket call error" );

    if( setsockopt( s, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof( on ) ) )
        error( 1, errno, "setsockopt call error" );

    if( bind( s, ( struct sockaddr*) &local, sizeof( local ) ) )
        error( 1, errno, "bind call error" );

    if( listen( s, NLISTEN ) )
        error( 1, errno, "listen() call error" );

    return s;

}

