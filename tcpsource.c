/*____________main.c _____________*/

#include "etcp.h"

int main( int argc, char** argv )
{
    struct sockaddr_in peer;
    char* buf;
    SOCKET s;
    int c;
    int blks = 5000;
    int sndbufsz = 32 * 1024;
    int sndsz = 1440; /* MSS по умолчанию */

    INIT();
    opterr = 0;
    while( ( c = getopt( argc, argv, "s:b:c:") ) != EOF )
    {
        switch( c )
        {
        case 's':
            sndsz = atoi( optarg );
            break;

        case 'b':
            sndbufsz = atoi( optarg );
            break;

        case 'c':
            blks = atoi( optarg );
            break;

        case '?':
            error( 1, 0, "incorrect parameter: %c\n", c );

        }
    }
    if( argc <= optind )
        error( 1, 0, "no host name\n" );
    if( ( buf = malloc( sndsz )) == NULL )
        error( 1, 0, "malloc() call error" );
    set_address( argv[ optind ], "9000", &peer, "tcp" );
    s = socket( AF_INET, SOCK_STREAM, 0 );
    if( !isvalidsock( s ) )
        error( 1, errno, "socket() call error" );
    if( setsockopt( s, SOL_SOCKET, SO_SNDBUF,
                    ( char* )&sndbufsz, sizeof( sndbufsz ) ) )
        error( 1, errno, "error setsockopt() with SO_SNDBUF option" );
    if( connect( s, ( struct sockaddr* )&peer,
                 sizeof( peer ) ) )
        error( 1, errno, "connect() call error" );

    while( blks-- > 0 )
        send( s, buf, sndsz, 0 );
    EXIT( 0 );

}
