/*---------- netaux.c ------------ */
#include "etcp.h"
//#include "wincompat.c"

/* The string was added by me on github.com in order to test how to edit the file right from the github */

void error( int status, int err, char *fmt, ... )
{
    va_list ap;
    va_start( ap, fmt );
    fprintf( stderr, "%s: ", program_name );
    vfprintf( stderr, fmt, ap );
    va_end( ap );
    if ( err )
        fprintf( stderr, ": %s (%d)\n", strerror( err ), err );
    if ( status )
        EXIT( status );
}

void set_address( char *hname, char *sname,
                  struct sockaddr_in *sap, char *protocol )
{
    struct servent *sp;
    struct hostent *hp;
    char *endptr;
    short port;
    bzero( sap, sizeof( *sap ) );
    sap->sin_family = AF_INET;
    if ( hname != NULL )
    {
        if ( !inet_aton( hname, &sap->sin_addr ) )
        {
            hp = gethostbyname( hname );
            if ( hp == NULL )
                error( 1, 0, "unknown host: %s\n", hname );
            sap->sin_addr = *( struct in_addr * )hp->h_addr;
        }
    }
    else
        sap->sin_addr.s_addr = htonl( INADDR_ANY );
    port = strtol( sname, &endptr, 0 );
    if ( *endptr == '\0' )
        sap->sin_port = htons( port );
    else
    {
        sp = getservbyname( sname, protocol );
        if ( sp == NULL )
            error( 1, 0, "unknown service: %s\n", sname );
        sap->sin_port = sp->s_port;
    }
}
