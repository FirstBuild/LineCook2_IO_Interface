#include <main.h>
#include <commands.h>
#include <buttons.h>
#include <i2c_constants.h>

command_t command;
uint8 params[2];

/* I2C slave read and write buffers */
uint8 i2cReadBuffer [BUFFER_SIZE] = {PACKET_SOP, STS_CMD_FAIL, PACKET_EOP};
uint8 i2cWriteBuffer[BUFFER_SIZE];

int main()
{
    uint8 i, 
          status = STS_CMD_FAIL;
    
    CyGlobalIntEnable;
    
    /* Start I2C slave (SCB mode) */
    I2CS_I2CSlaveInitReadBuf (i2cReadBuffer,  BUFFER_SIZE);
    I2CS_I2CSlaveInitWriteBuf(i2cWriteBuffer, BUFFER_SIZE);
    I2CS_Start();    
    
	for (;;) {
        // Set time to 2:45 AM
        params[0] = 2u;
        params[1] = 45u;
        command = CMD_SET_CLOCK;
        (void) executeCommand(command, &params);
    	
    	CyDelay(3000);
    }

    for(;;)
    {
        /* Write complete: parse command packet */
        if (0u != (I2CS_I2CSlaveStatus() & I2CS_I2C_SSTAT_WR_CMPLT))
        {      
            /* Check packet length */
            if (PACKET_SIZE == I2CS_I2CSlaveGetWriteBufSize())
            {
                /* Check start and end of packet markers */
                if ((i2cWriteBuffer[PACKET_SOP_POS] == PACKET_SOP) &&
                    (i2cWriteBuffer[PACKET_EOP_POS] == PACKET_EOP))
                {
                    // Copy param bytes into memory
                    for (i = 0; i < 2; i++)
                    {
                        params[i] = i2cWriteBuffer[PACKET_PRM_POS + i];
                    }
                    command = (command_t) i2cWriteBuffer[PACKET_CMD_POS];
                    status = executeCommand(command, &params);
                }
            }

            /* Clear slave write buffer and status */
            I2CS_I2CSlaveClearWriteBuf();
            (void) I2CS_I2CSlaveClearWriteStatus();

            /* Update read buffer */
            i2cReadBuffer[PACKET_STS_POS] = status;
            status = STS_CMD_FAIL;
        }

        /* Read complete: expose buffer to master */
        if (0u != (I2CS_I2CSlaveStatus() & I2CS_I2C_SSTAT_RD_CMPLT))
        {
            /* Clear slave read buffer and status */
            I2CS_I2CSlaveClearReadBuf();
            (void) I2CS_I2CSlaveClearReadStatus();
        }
    }
}
