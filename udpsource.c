*--------- main.c ( udpsource.c ) -------- */

/* UDP sender that sends a number of datagramss
* the number and the size of datagrams is read
* from the commandline
*/
#define DEF_NUM     10000 //datagrams
#define DEF_SIZE    1440   //default size

#include "etcp.h"


int main( int argc, char** argv )
{
    struct sockaddr_in peer;
    SOCKET s;
    int rc;
    int datagrams;
    int dgramsz = DEF_SIZE;
    char buf[ DEF_SIZE ];

    INIT();
/*
    if( argc < 2 )
    {
        printf( "Default config %d datagrams with %d bytes\n",
               DEF_NUM, dgramsz );
        itoa( DEF_NUM, buf, 10 );
        puts( buf );
        argv[2] = &buf[0];
    }
*/
    datagrams = atoi( argv[ 2 ] );  //read the number of datagrams
    if( argc > 3 )
        dgramsz = atoi( argv[ 3 ] );  // the size of datagrams
    s = udp_client( argv[ 1 ], "9000", &peer );
    while( datagrams-- > 0 )
    {
        rc = sendto( s, buf, dgramsz, 0,
            (struct sockaddr* )&peer, sizeof( peer ) );
        if( rc <= 0 )
            error( 0, errno, "sendto() call error" );
    }
    sendto( s, "", 0, 0,
           ( struct sockaddr* )&peer,
           sizeof( peer ) );    //send final datagram with null byte
    EXIT( 0 );
}
