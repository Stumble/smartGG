#pragma once

#include <fstream>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h> /* File control definitions */
#include <errno.h>
#include <termios.h> /* POSIX terminal control definitions */
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>


using namespace std;

//为串口发送准备的变量和buf
union Udata{
	unsigned char c[4];
	float f;
	long l;
};



void send_sp(int fd, Udata & data1,Udata & data2,Udata & data3,char ctl );
void init_sp(int fd);
int open_port(char * str);
void set_port(int fd);
void send_byte(int fd, unsigned char c);
