/* ------------- udpsink.c --------------*/

#include "etcp.h"

int main( int argc, char** argv )
{
    SOCKET s;
//    struct sockaddr_in peerp;
    int rc;
    int datagrams = 0;
    int rcvbufsz = 5000 * 1440;
    char buf[ 1440 ];
   // int peerlen = sizeof( peerp );

    INIT();

    s = udp_server( NULL, "9000" );
    printf( "Started udp server, waiting for the stream...\n"
           "12000 datagrams to exit\n" );
    setsockopt( s, SOL_SOCKET, SO_RCVBUF,
                ( char* )&rcvbufsz, sizeof( int ) );
    for( ;; )
    {
        rc = recv( s, buf, sizeof(buf), 0 );
        if( rc <= 0 )
        {
            // break;
            error( 0, 0, "received datagrams: %d \n", datagrams );
            datagrams = 0;
            printf( "Waiting for new datagrams..\n" );
        }
        datagrams++;
        if( datagrams == 12000 )
            break;
    }
    error( 0, 0, "received datagrams: %d \n", datagrams );
    EXIT( 0 );

}
