#include<stdio.h>

//cat /proc/cpuinfo  ==> 2.5Ghz
#define CPU_FREQ 2500000000

unsigned long long GetCPUTickCount(){
    unsigned long high32=0, low32=0;
#ifdef WIN32 // WIN32
    _asm
    {
        RDTSC;
        mov high32,ebx;  
        mov low32,eax;  
    }
#else
    __asm__ ("RDTSC" : "=a"(low32),"=d"(high32));
#endif
    unsigned long long counter = high32;
    counter = (counter<<32) + low32;
    return counter;
} 




int main()
{
 unsigned long long t = GetCPUTickCount();
 unsigned long long t2 = GetCPUTickCount();

 printf("t=%llu t2=%llu t2-t1=%llu\n", t, t2, t2-t );
}
