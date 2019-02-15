/** MSGCODES.H */

#ifndef _MSGCODES_H_
#define _MSGCODES_H_

/** common messages */

#define BMSG_POSITIVE 0
#define BMSG_NEGATIVE -1
#define BMSG_DISCONNECT -2

/** server messages */

#define SMSG_VERIFY_CONNECTION 1
#define SMSG_REQUEST_NAME 2
#define SMSG_INFO_MAP 3
#define SMSG_INFO_PLAER_LIST 4
#define SMSG_INFO_GAME 5

/** client messages */

#define CMSG_SET_NAME 1
#define CMSG_REQUEST_GAME 2
#define CMSG_REQUEST_PLAYER_LIST 3
#define CMSG_REQUEST_MAP 4

#endif
