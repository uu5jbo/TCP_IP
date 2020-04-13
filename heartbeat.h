/*______________________________heartbeat.h_____________*/

#ifndef __HEARTBEAT_H__
#define __HEARTBEAT_H__

#define MSG_TYPE1		1	/* Application level message */
#define MSG_TYPE2		2	/* One more */
#define MSG_HEARTBEAT	3	/* Pulse message */

typedef struct 			/* The structure of the message */
{
	u_int32_t type;		/* MSG_TYPE1, ... */
	char data[ 2000 ];
} msg_t;

#define T1		60	/* Idle time before the send of pulse */
#define T2		10	/* Stand-by time for the reply */

#endif //__HEARTBEAT_H__ 
