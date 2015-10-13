#include <stdio.h>
#include "firmata.h"
#include "stdbool.h"
#include <time.h>
#include "encoder_updated.h"


void encoder_updated::initialize()
{
    firmata1 = firmata_new("/dev/ttyACM99"); //init Firmata
    while(!firmata1->isReady)
        firmata_pull(firmata1);
    
    firmata_pinMode(firmata1, pin, MODE_INPUT);//set pin 3
    
    for (i=0;i<10;i++)
    {
        buffer[i]=0;
    }
    bool value1=firmata1->pins[12].value == HIGH;
    speed=0.0;
    
}

void loop()
{
    stime=time(NULL);
    while(!firmata1->isReady)
        firmata_pull(firmata1);
    if((firmata1->pins[12].value == HIGH)^(value1))
    {
        buffer[i+1]=difftime(time(NULL)-stime);
        speed = PI*DIAMETER/(4.0*(buffer[i+1]-buffer[i]));
    }
}

void main()
{
    
    stime=clock();
    
    firmata_pull(firmata1);
    
    
    i=0;
    
    while (i<9)
    {
        while(!firmata1->isReady)
            firmata_pull(firmata1);
        if((firmata1->pins[12].value == HIGH)^(value1))
        {
            buffer[i+1]=clock()-stime;
            speed = PI*DIAMETER/(4.0*(buffer[i+1]-buffer[i]))*CLOCKS_PER_SEC;
        }
    }
    
    int j=0;
    clock_t etime=0;

    double time_s=0;
    
    int index=0;
    
    while (1)
    {
        while(!firmata1->isReady) //Wait until device is up
            firmata_pull(firmata1);
        etime=clock()-stime;
        if((firmata1->pins[12].value == HIGH)^(value1))
        {
            value1=firmata1->pins[12].value == HIGH;
            i=i+1;
            time_s=(1.0*(etime-buffer[j==0? 9:j-1])/CLOCKS_PER_SEC);
            
            index=(10-(int)(time_s/0.01))<1? 1:(10-(int)(time_s/0.01));
            
            speed=PI*DIAMETER/(4.0*(etime-buffer[j>index-1? j-index:j+10-index]))*CLOCKS_PER_SEC;
            
            buffer[j]=etime;
            j=j==9? 0:j+1;
            
            printf("speed: %0.2f\t %d 1\n",speed,index);
            
        }
        else if ((double)(1.0*(etime-buffer[j==0? 9:j-1])/CLOCKS_PER_SEC)>CUTOFF)
        {
            speed=0.0;
            printf("speed: %0.2f\n",speed);
        }
	
               
    }
}
