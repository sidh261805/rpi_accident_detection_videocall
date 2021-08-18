#include <stdio.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include<arpa/inet.h>

typedef struct {
   int degrees;
   int mins;
   int minFrac;
   char quadrasphere;
} DMData;

typedef struct {
  DMData latDM;
  DMData longDM;
   int quality;
   int numSats;
   int checkSum;
} GPSData;

GPSData *gpsData;
