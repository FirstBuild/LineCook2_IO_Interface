#ifndef I2C_HEADER
#define I2C_HEADER
    
/* Buffer and packet size */
#define BUFFER_SIZE     (5u)
#define PACKET_SIZE     (BUFFER_SIZE)

/* Packet positions */
#define PACKET_SOP_POS  (0u)
#define PACKET_CMD_POS  (1u)
#define PACKET_STS_POS  (PACKET_CMD_POS)
#define PACKET_PRM_POS  (2u)
#define PACKET_EOP_POS  (4u)

/* Start and end of packet markers */
#define PACKET_SOP      (0x01u)
#define PACKET_EOP      (0x17u)

/* Command valid status */
#define STS_CMD_DONE    (0x00u)
#define STS_CMD_FAIL    (0xFFu)

#endif
