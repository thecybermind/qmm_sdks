#pragma once
#include "msg.h"
// number of old messages that must be kept on client and
// server for delta comrpession and ping estimation
#define	PACKET_BACKUP	32
#define	PACKET_MASK		(PACKET_BACKUP-1)
#define	MAX_PACKET_USERCMDS		32		// max number of usercmd_t in a packet
#define	PORT_ANY			-1
#define	MAX_RELIABLE_COMMANDS	128			// max string commands buffered for restransmit
#define FAKELATENCY_MAX_PACKETS_HELD 512
enum netadrtype_t {
    NA_BOT,
    NA_BAD,					// an address lookup failed
    NA_LOOPBACK,
    NA_BROADCAST,
    NA_IP,
    NA_IPX,
    NA_BROADCAST_IPX
};
enum netsrc_t 
{                                       
    NS_CLIENT1,
    NS_SERVER,
    NS_MAXCLIENTS,
    NS_PACKET,
};
inline netsrc_t &operator++(netsrc_t &e) {
    e = static_cast<netsrc_t>(static_cast<int>(e) + 1);
    return e;
}
inline netsrc_t &operator++(netsrc_t &e, int i)
{
    ++e;
    return e;
}
struct netadr_t {
    netadrtype_t	type;
    unsigned char  ip[4];
    unsigned short port;
    unsigned char  ipx[10];
};
struct ClientSnapshotData 
{
    int snapshotSize[8];
    int compressedSize[8];
    int index;
};
struct netProfilePacket_t 
{                                       
    int iTime;
    int iSize;
    int bFragment;
};
struct netProfileStream_t 
{                                       
    netProfilePacket_t packets[60];
    int iCurrPacket;
    int iBytesPerSecond;
    int iLastBPSCalcTime;
    int iCountedPackets;
    int iCountedFragments;
    int iFragmentPercentage;
    int iLargestPacket;
    int iSmallestPacket;
};
struct netProfileInfo_t 
{                                       
    netProfileStream_t send;
    netProfileStream_t recieve;         
};
struct netchan_t 
{                                       
    int outgoingSequence;
    netsrc_t sock;
    int dropped;
    int incomingSequence;
    netadr_t remoteAddress;             
    int qport;
    int fragmentSequence;
    int fragmentLength;
    unsigned char* fragmentBuffer;
    int fragmentBufferSize;
    int unsentFragments;
    int unsentFragmentStart;
    int unsentLength;
    unsigned char* unsentBuffer;
    int unsentBufferSize;
    netProfileInfo_t prof;
};
struct fakedLatencyPackets_t 
{
    bool outbound;
    bool loopback;
    netsrc_t sock;
    netadr_t addr;
    unsigned int length;
    unsigned char *data;
    int startTime;
    msg_t msg;
};
struct loopmsg_t 
{                                       
    unsigned char data[1400];
    int datalen;
    int port;
};
struct loopback_t 
{                                       
    loopmsg_t msgs[16];
    volatile unsigned int get;
    volatile unsigned int send;
};
struct clientHeader_t 
{                                       
    int state;                          
    int sendAsActive;
    int deltaMessage;
    int rateDelayed;
    netchan_t netchan;                  
    float predictedOrigin[3];
    int predictedOriginServerTime;      
};