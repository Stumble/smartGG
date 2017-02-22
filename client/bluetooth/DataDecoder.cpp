#include "DataDecoder.h"

unsigned char datarec[75] = { 0 };
unsigned char recv_flag=0,new_flag=0, INITcounter=0,recv_counter=0;
unsigned char datalast=0;
unsigned char buffer[75] = { 0 };
long Data[14] = { 0 };

union Udata{
    long l;
    float f;
    char c[4];
};

void Receive(unsigned char * data){
  if(recv_flag==0&&*data==0xFF){
    if(INITcounter==0){
      INITcounter++;
    }else if(datalast==0xFF){
      INITcounter++;
    }else{
      INITcounter=0;
    }

    if(INITcounter==4){
      INITcounter=0;
      recv_flag=1;
      recv_counter=0;
    }
  }else if(recv_flag==1){
    INITcounter=0;
    buffer[recv_counter++]=*data;
    if(recv_counter==PACKAGES_NUM*5+3){
      recv_flag=0;
      //重置接收计数器
      recv_counter=0;
      //新数据标志
      new_flag=1;
    }
  }else{
    INITcounter=0;
  }
  datalast=*data;
  if(recv_counter==PACKAGES_NUM*5+3) recv_counter--;  //防止越界
}

int decode(){
  if(new_flag!=1) return 0;
  new_flag=0;
  if(buffer[PACKAGES_NUM*5+2]!=0x00) return 0;
  unsigned char check=0;
  for (int i = 0; i<PACKAGES_NUM*5+1; i++){
    check += buffer[i];
  }
  //if(check!=buffer[PACKAGES_NUM*5+1]) return 0;
  for (int i = 0; i<PACKAGES_NUM;i++){
    if(buffer[i*5]!=0){
        Udata dcvt;
        dcvt.c[0]=buffer[i*5+1];
        dcvt.c[1]=buffer[i*5+2];
        dcvt.c[2]=buffer[i*5+3];
        dcvt.c[3]=buffer[i*5+4];
        Data[buffer[i*5]]=dcvt.l;
    }
  }
  return 1;
}
