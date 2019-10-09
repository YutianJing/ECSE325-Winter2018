#include<sys/time.h>
#include<stdio.h>
 
int SetTimer(struct timeval *tv, time_t sec)
{
    gettimeofday(tv,NULL);
    tv->tv_sec+=sec;
 
    return 1;
}
////////////////////////////////////////////////// 
int CheckTimer(struct timeval *tv, time_t sec)
{
    struct timeval ctv;
    gettimeofday(&ctv,NULL);
 
    if( (ctv.tv_sec >= tv->tv_sec) )
    {
        gettimeofday(tv,NULL);
        tv->tv_sec+=sec;
        return 1;
    }
    else {
	 return 0;
	}
}

//////////////////////////////////////
int pack_hex(int hex3, int hex2, int hex1, int hex0)
{
	return ((hex3 << 24) | (hex2 << 16) | (hex1 << 8) | hex0);
}
//////////////////////////////////////
int hex_to_7segment(int hex)
{
	switch(hex) {
	case 0 :
		return 0b11000000;
	case 1 :
		return 0b11111001;
	case 2 :
		return 0b10100100;
	case 3 :
		return 0b10110000;
	case 4 :
		return 0b10011001;
	case 5 :
		return 0b10010010;
	case 6 :
		return 0b10000010;
	case 7 :
		return 0b11111000;
	case 8 :
		return 0b10000000;
	case 9 :
		return 0b10010000;
	default :
		return 0b11111111;
}
return(0);
}
///////////////////////////////////////////


// Simple test program
int main(void)
{
volatile int * led = (int *) 0xFF200040; // red LED address
volatile int * hex3_hex0 = (int *) 0xFF200020; // red LED address
volatile int * hex5_hex4 = (int *) 0xFF200010; // red LED address
volatile int * switchptr = (int *) 0xFF200030; // SW slider switch address
int switch_value;

struct timeval tv;
SetTimer(&tv,1); 

int secs = 0;
int secs_tens = 0;
int mins = 0;
int mins_tens = 0;
int hours = 0;
int hours_tens = 0;

while (1)
{
if (CheckTimer(&tv,1)==1) {
	secs++;
	if (secs == 10) {
	secs = 0;
	secs_tens++;
	if (secs_tens == 6) {
		secs_tens = 0;
		mins++;
		if (mins == 10) {
			mins = 0;
			mins_tens++;
			if (mins_tens == 6) {
				mins_tens = 0;
				hours++;
				if (hours == 10 || ((hours_tens == 1) && (hours == 2))) {
					hours = 0;
					hours_tens++;
					if (hours_tens == 2) {
						hours_tens = 0;
					}
				}
			}
		}
	}
}
}
  
switch_value = *(switchptr);
*(led) = switch_value;
*(hex3_hex0) = pack_hex(hex_to_7segment(mins_tens),hex_to_7segment(mins),hex_to_7segment(secs_tens),hex_to_7segment(secs));
*(hex5_hex4) = pack_hex(0,0,hex_to_7segment(hours_tens),hex_to_7segment(hours));
}
}
