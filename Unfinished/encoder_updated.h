#include <stdio.h>
#include "firmata.h"
#include "stdbool.h"
#include <time.h>


#define PI 3.14159265359
#define DIAMETER 0.07239
#define CUTOFF 0.5
#define FAST 0.01
#define SLOW 0.05

typedef struct Encoder
{
    float speed;
    long int buffer[10];
    long int i;
    time_t stime;
    time_t etime;
    bool value1;
    t_firmata *firmata1;
    int pin;
    
    void initialize();
    void loop();
    int main();
}


/*void main()
{
    t_firmata     *firmata1;
    firmata1 = firmata_new("/dev/ttyACM99"); //init Firmata
    while(!firmata1->isReady) //Wait until device is up
        firmata_pull(firmata1);
    
    firmata_pinMode(firmata1, 12, MODE_INPUT); //set pin 3 (led on most arduino) to out
    
    long int buffer[10];
    
    long int i=0;
    
    for (i=0;i<10;i++)
    {
        buffer[i]=0;
    }
    
    clock_t stime=clock();
    
    firmata_pull(firmata1);
    bool value1=firmata1->pins[12].value == HIGH;
    
    speed=0.0;
    
    i=0;
    
    while (i<9)
    {
        while(!firmata1->isReady) //Wait until device is up
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
            
/*            if((double)(1.0*(etime-buffer[j==0? 9:j-1])/CLOCKS_PER_SEC)>SLOW)
               {
                   speed = PI*DIAMETER/(4.0*(etime-buffer[j==0? 9:j-1]))*CLOCKS_PER_SEC;
                   buffer[j]=etime;
                   j=j==9? 0:j+1;
		   printf("speed: %0.2f\t 1\n",speed);
               }
            else if ((double)(1.0*(etime-buffer[j==0? 9:j-1])/CLOCKS_PER_SEC)>FAST)
               {
                   speed = 1.25*PI*DIAMETER/(etime-buffer[j>4? j-5:j+5])*CLOCKS_PER_SEC;
                   buffer[j]=etime;
                   j=j==9? 0:j+1;
                   printf("speed: %0.2f\t2\n",speed);
               }
            else
               {
                   speed = 2.5*PI*DIAMETER/(etime-buffer[j])*CLOCKS_PER_SEC;
		   printf("speed: %0.2f\t td %0.2f \t rt %0.2f \t %ld \n",speed,etime-buffer[j==0? 9:j-1],1.0*(etime-buffer[j==0? 9:j-1])/CLOCKS_PER_SEC,clock());
		   
                   buffer[j]=etime;
                   j=j==9? 0:j+1;
		   
               }*/
            
 /*       }
        else if ((double)(1.0*(etime-buffer[j==0? 9:j-1])/CLOCKS_PER_SEC)>CUTOFF)
        {
            speed=0.0;
            printf("speed: %0.2f\n",speed);
        }
	
               
    }
}
*/