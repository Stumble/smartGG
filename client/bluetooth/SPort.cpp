#include "SPort.h"


using namespace std;

char sendbuf[22];
int ifwritesucc;
Udata P_pch,I_pch,D_pch,P_yaw,I_yaw,D_yaw;

/**
 * @brief send_sp 发送数据，这里是三个数据的发送，没用到
 * @param fd
 * @param data1
 * @param data2
 * @param data3
 * @param ctl
 */
void send_byte(int fd, unsigned char c){
    ifwritesucc=write(fd,&c,1);
    if(ifwritesucc<0){
        cout<<"send failed."<<endl;
    }

}

void send_sp(int fd, Udata & data1,Udata & data2,Udata & data3,char ctl ){
	//构建数据针
	sendbuf[4]=ctl;
	sendbuf[5]=data1.c[0];
	sendbuf[6]=data1.c[1];
	sendbuf[7]=data1.c[2];
	sendbuf[8]=data1.c[3];
	sendbuf[9]=ctl;
	sendbuf[10]=data2.c[0];
	sendbuf[11]=data2.c[1];
	sendbuf[12]=data2.c[2];
	sendbuf[13]=data2.c[3];
	sendbuf[14]=ctl;
	sendbuf[15]=data3.c[0];
	sendbuf[16]=data3.c[1];
	sendbuf[17]=data3.c[2];
	sendbuf[18]=data3.c[3];
	sendbuf[19]=ctl;
	sendbuf[20]=data1.c[0]+data2.c[0]+data3.c[0];
	//发送
    ifwritesucc=write(fd,sendbuf,22);
	if(ifwritesucc<0){
		cout<<"send failed."<<endl;
	}
}

/**
 * @brief init_sp 初始化数据发送，本程序未用到
 * @param fd ： 串口文件
 */
void init_sp(int fd){
	ifstream inf("PIDdata");
	inf>>P_pch.f;inf>>I_pch.f;inf>>D_pch.f;inf>>P_yaw.f;inf>>I_yaw.f;inf>>D_yaw.f;
	inf.close();
	sendbuf[0]=0xFF;
	sendbuf[1]=0xFF;
	sendbuf[2]=0xFF;
	sendbuf[3]=0xFF;
	sendbuf[4]=0x00;
	sendbuf[5]=0x00;
	sendbuf[6]=0x00;
	sendbuf[7]=0x00;
	sendbuf[8]=0x00;
	sendbuf[9]=0x00;
	sendbuf[10]=0x00;
	sendbuf[11]=0x00;
	sendbuf[12]=0x00;
	sendbuf[13]=0x00;
	sendbuf[14]=0x00;
	sendbuf[15]=0x00;
	sendbuf[16]=0x00;
	sendbuf[17]=0x00;
	sendbuf[18]=0x00;
	sendbuf[19]=0x00;
	sendbuf[20]=0x00;
	sendbuf[21]=0xAA;
	send_sp(fd, P_pch,I_pch,D_pch,0x11);//修改pitch的PID
	send_sp(fd, P_yaw,I_yaw,D_yaw,0x22);//修改yaw的PID
}

/**
 * @brief open_port 用于打开串口文件
 * @param str : 串口文件名
 * @return ： 返回串口文件
 */

int open_port(char * str)
{
	int fd; /* File descriptor for the port */

	fd = open(str, O_RDWR | O_NOCTTY | O_NDELAY);
	//fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
	if (fd == -1)
	{
		/*
		 * Could not open the port.
		 */
		perror("open_port: Unable to open /dev/ttyUSB0 -");
		return fd;
	}
	else
	{
		fcntl(fd, F_SETFL, 0);
		return (fd);
	}
}

/**
 * @brief set_port 设置串口参数
 * @param fd ：已经打开的串口文件
 */
void set_port(int fd){
	struct termios Opt;
	tcgetattr(fd,&Opt);
	//printf("%s\n", );
	tcflush(fd,TCIOFLUSH);
    cfsetispeed(&Opt,B115200);  //波特率设置
	cfsetospeed(&Opt,B115200);
	Opt.c_lflag=0;
	Opt.c_oflag=0;
	Opt.c_iflag=0;
	Opt.c_cc[VINTR] = 0;
	Opt.c_cc[VQUIT] = 0;
	Opt.c_cc[VKILL] = 0;
	Opt.c_cc[VERASE] = 0;
	Opt.c_cc[VEOF] = 0;
	Opt.c_cc[VTIME] = 0;
	Opt.c_cc[VMIN] = 0;
	Opt.c_cc[VSWTC] = 0;
	Opt.c_cc[VSTART] = 0;
	Opt.c_cc[VSTOP] = 0;
	Opt.c_cc[VSUSP] = 0;
	Opt.c_cc[VEOF] = 0;
	Opt.c_cc[VREPRINT] = 0;
	Opt.c_cc[VDISCARD] = 0;
	Opt.c_cc[VWERASE] = 0;
	Opt.c_cc[VLNEXT] = 0;
	Opt.c_cc[VEOL2] = 0;
	int stat=tcsetattr(fd,TCSANOW,&Opt);
	if(stat!=0){
		printf("error");
		return;
	}
	tcflush(fd,TCIOFLUSH);
}
