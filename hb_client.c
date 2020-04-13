/*________________________main.c ( hb_client.c )______________________*/

#include "etcp.h"
#include "heartbeat.h"

char* program_name;

int main( int argc, char** argv )
{
    fd_set allfd;
    fd_set readfd;
    msg_t msg;
    struct timeval tv;
    SOCKET s;
    int rc;
    int heartbeats = 0;
    int cnt = sizeof( msg );

    INIT();
    s = tcp_client( argv[1], argv[2] );
    FD_ZERO( &allfd );
    FD_SET( s, &allfd );
    tv.tv_sec = T1;
    tv.tv_usec = 0;

    for( ;; )
    {
        readfd = allfd;
        rc = select( s + 1, &readfd, NULL, NULL, &tv );
        if( rc < 0 )
            error( 1, errno, "select() call error " );
        if( rc == 0 )
        {
            if( ++heartbeats > 3 )
                error( 1, 0, "no connection" );
            error( 0, 0, "sending pulse #%d\n", heartbeats );
            msg.type = htonl( MSG_HEARTBEAT );
            rc = send( s, ( char* )&msg, sizeof( msg ), 0 );
            if( rc < 0 )
                error( 1, errno, "send() call error" );
            tv.tv_sec = T2;
            continue;

        }
        if( !FD_ISSET( s, &readfd ) )
            error( 1, 0, "select() returned incorrect socket\n" );
        rc = recv( s, ( char* )&msg + sizeof( msg ) - cnt,
                  cnt, 0 );
        if( rc == 0 )
            error( 1, 0, "server is down\n" );
        if( rc < 0 )
            error( 1, errno, "recv() call error ");

        //reply from server received
        heartbeats = 0; //since the reply received, reset heartbeats
        tv.tv_sec = T1; //reset the timer for T1 seconds
        cnt -= rc; //reduce cnt on the number of bytes read
        if( cnt > 0 )   //if not the whole message read
            continue;   //repeat the cycle from select()
        cnt = sizeof( msg );  //otherwise the length of msg in cnt
                              //and process the message received
        /* -- Processing the message -- */

    }
}
