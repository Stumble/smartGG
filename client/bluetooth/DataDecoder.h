#ifndef DATADECODER_H
#define DATADECODER_H
#define PACKAGES_NUM 11
extern unsigned char datarec[75] ;
//extern unsigned char recv_flag,new_flag, INITcounter,recv_counter;
extern unsigned char buffer[75];
extern long Data[14];

void Receive(unsigned char * data);
int decode();



#endif // DATADECODER_H
