#include "head.h"


#define BAUDRATE B9600   
#define MODEMDEVICE "/dev/ttyUSB0" 
#define _POSIX_SOURCE 1 

#define FALSE 0
#define TRUE 1

#define MPU_ACCEL_XOUT1 0x3b
#define MPU_ACCEL_XOUT2 0x3c
#define MPU_ACCEL_YOUT1 0x3d
#define MPU_ACCEL_YOUT2 0x3e
#define MPU_ACCEL_ZOUT1 0x3f
#define MPU_ACCEL_ZOUT2 0x40

#define MPU_GYRO_XOUT1 0x43
#define MPU_GYRO_XOUT2 0x44
#define MPU_GYRO_YOUT1 0x45
#define MPU_GYRO_YOUT2 0x46
#define MPU_GYRO_ZOUT1 0x47
#define MPU_GYRO_ZOUT2 0x48

#define MPU_TEMP1 0x41
#define MPU_TEMP2 0x42

#define MPU_POWER1 0x6b
#define MPU_POWER2 0x6c
//extern GPSdata *gpsData;
//void printGPSData(GPSData *gpsData);
int hexStr2Int(char* str, int sPos, int numChars);
int extractNum(char* str, int sPos, int ePos, int *valPtr);
extern int decodeGPSString(char *str,GPSData *gpsData);
extern int serv();

int main()
{

    int fd1;
    char *fileName = "/dev/i2c-1";

    int  address = 0x68;
	
    if ((fd1 = open(fileName, O_RDWR)) < 0) {
        printf("Failed to open i2c port\n");
        exit(1);
    }
	
    if (ioctl(fd1, I2C_SLAVE, address) < 0) {
        printf("Unable to get bus access to talk to slave\n");
        exit(1);
    }
    
    int8_t power = i2c_smbus_read_byte_data(fd1, MPU_POWER1);
    i2c_smbus_write_byte_data(fd1, MPU_POWER1, ~(1 << 6) & power);

    while (1) {
        int16_t temp = i2c_smbus_read_byte_data(fd1, MPU_TEMP1) << 8 |
                        i2c_smbus_read_byte_data(fd1, MPU_TEMP2);

        int16_t xaccel = i2c_smbus_read_byte_data(fd1, MPU_ACCEL_XOUT1) << 8 |
                         i2c_smbus_read_byte_data(fd1, MPU_ACCEL_XOUT2);
        int16_t yaccel = i2c_smbus_read_byte_data(fd1, MPU_ACCEL_YOUT1) << 8 |
                         i2c_smbus_read_byte_data(fd1, MPU_ACCEL_YOUT2);
        int16_t zaccel = i2c_smbus_read_byte_data(fd1, MPU_ACCEL_ZOUT1) << 8 |
                         i2c_smbus_read_byte_data(fd1, MPU_ACCEL_ZOUT2);

        int16_t xgyro = i2c_smbus_read_byte_data(fd1, MPU_GYRO_XOUT1) << 8 |
                        i2c_smbus_read_byte_data(fd1, MPU_GYRO_XOUT2);
        int16_t ygyro = i2c_smbus_read_byte_data(fd1, MPU_GYRO_YOUT1) << 8 |
                        i2c_smbus_read_byte_data(fd1, MPU_GYRO_YOUT2);
        int16_t zgyro = i2c_smbus_read_byte_data(fd1, MPU_GYRO_ZOUT1) << 8 |
                        i2c_smbus_read_byte_data(fd1, MPU_GYRO_ZOUT2);


float aa,bb,cc;
aa=((float)xaccel/16384)*9.8;
bb=((float)yaccel/16384)*9.8;
cc=((float)zaccel/16384)*9.8;

float az,bz,cz;
az=((float)xgyro/131);
bz=((float)ygyro/131);
cz=((float)zgyro/131);

        printf("temp: %f\n", (float)temp / 340.0f + 36.53);
        printf("accel x,y,z: %.3f m/s², %.3f m/s², %.3f m/s²\n", aa,bb,cc);
        printf("gyro x,y,z: %.3f°, %.3f°, %.3f°\n", az,bz,cz);


if((aa>17||aa<(-17))||(bb>17||bb<(-17))||(cc>17||cc<(-17)))
{
printf("accident happen\n\n");
////////////////////////////////////////gps
int fd, c, res;
    struct termios oldtio, newtio;
    char buf[255];
    //int ret = system("echo uart1 > /sys/devices/bone_capemgr.9/slots");
    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY );
    if (fd < 0) { perror(MODEMDEVICE); exit(-1); }

    bzero(&newtio, sizeof(newtio)); 
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = ICANON;
    
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
    write(fd, "$PTNLSNM,273F,01*27\r\n", 21);
    
    while (TRUE) {    
        res = read(fd, buf, 255);
        buf[res] = 0;  
             
      
int result = decodeGPSString(buf,&gpsData);
    
    }
    tcsetattr(fd, TCSANOW, &oldtio);

}
else 
printf("accident not occur\n\n");
sleep(1);
    }
	//system("/home/sidd/Desktop/SimpleRTC-gh-pages/minivid2.html\n");
	
    return 0;
}











