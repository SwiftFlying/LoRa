/*
Original code by : https://github.com/Snootlab/lora_chisterapi
Edited by : Ramin Sangesari
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <RH_RF95.h>

#include "example.hpp"




RH_RF95 rf95;

int run = 1;

/* Signal the end of the software */


void get_loc(char* outStr)
{
    //printf("You have made it into the look function\n");
    /* If we receive one message we show on the prompt
     * the address of the sender and the Rx power.
     */
    if( rf95.available() ) 
    {
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);

        if (rf95.recv(buf, &len)) 
        {
            for(int i=0;i<RH_RF95_MAX_MESSAGE_LEN;i++){
                outStr[i] = (char)(bug[i]);
            }
            
            //string str = (char*)buf;
           //printf("Reading: %s\n",buf);
            //fflush(stdout);

           
        }
    }

    
}


void sigint_handler(int signal)
{
    run = 0;
}

void setup()
{ 

    wiringPiSetupGpio();
    if (!rf95.init())
    {
        fprintf(stderr, "Init failed\n");
        exit(1);
    }
    
    /* Tx Power is from +5 to +23 dbm */
    printf("Set Power\n");
    rf95.setTxPower(23);
    /* There are different configurations
     * you can find in lib/radiohead/RH_RF95.h
     * at line 437 
     */
    printf("Setting config\n");
    rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128);
    printf("Setting Frequency\n");
    printf("The Max packet length is %d\n", RH_RF95_MAX_MESSAGE_LEN);
    rf95.setFrequency(915.0); /* MHz */
}

void loop()
{
    //printf("You have made it into the look function\n");
    /* If we receive one message we show on the prompt
     * the address of the sender and the Rx power.
     */
    if( rf95.available() ) 
    {
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);

        if (rf95.recv(buf, &len)) 
        {
            printf("Reading: %s\n",buf);
			fflush(stdout);
        }
    }
}

// int main(int argc, char **argv)
// { 
//     signal(SIGINT, sigint_handler);

//     setup();

//     while( run )
//     {
//         loop();
//         usleep(1);
//     }

//     return EXIT_SUCCESS;
// }
