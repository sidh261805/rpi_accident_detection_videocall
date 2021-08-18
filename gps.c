#include "head.h"
extern int latdegree,latmin,latsec;
extern int londegree,lonmin,lonsec;


extern int hexStr2Int(char* str, int sPos, int numChars)
{
   int val = 0;
   while (numChars > 0)   {
      int d = str[sPos] - 48;
      if (d>9) d -= 7;
      val = (val << 4) + (d & 0xF);
      sPos++;
      numChars--;
   }

   return val;
}




int extractNum(char* str, int sPos, int ePos, int *valPtr)
{
   int val = 0;
   for ( ; sPos<=ePos ; sPos++)
   {
      if (str[sPos] > 57 || str[sPos] < 48) return 1;

      val = (val*10) + str[sPos] - 48;
   }

   *valPtr = val;
   return 0;
}



extern int decodeGPSString(char *str,GPSData *gpsData)
{
   const char *code = "$GPGGA";
   int i;

   // Check for the correct code
   for (i=0 ; i<6 ; i++) if (str[i] != code[i]) return 1;
int pos = 1;
   int commaPos[14];
   int commaCount = 0;
   int starPos = 0;
   int nlPos = 0;
   char checkSum = 0;

   // Iterate through string characters
   while (pos < 100) {

      // Check for end of line
      if (str[pos] == '\n') {
         nlPos = pos;
         break;
      }

      // Check for star and update checksum
      if (starPos == 0) {
         if (str[pos] == '*') starPos = pos;
         else checkSum ^= str[pos];
      }

      // Check for comma
      if (str[pos] == ',') {
         if (commaCount < 14) commaPos[commaCount] = pos;
         commaCount ++;
      }

 pos ++;
   }

   // Check for sensible format
   if (starPos==0 || nlPos==0 || commaCount!=14 || (nlPos-starPos)!=4) return 2;

   // Compare Checksums
   gpsData->checkSum = hexStr2Int(str, starPos+1, 2);
   if (checkSum != gpsData->checkSum) return 3;

   // Extract Latitude
   int err = 0;
   err |= extractNum(str, commaPos[1]+1, commaPos[1]+2, &gpsData->latDM.degrees);
   err |= extractNum(str, commaPos[1]+3, commaPos[1]+4, &gpsData->latDM.mins);
   err |= extractNum(str, commaPos[1]+6, commaPos[1]+10, &gpsData->latDM.minFrac);
   gpsData->latDM.quadrasphere = str[commaPos[2]+1];
   if (err) return 3;

   // Extract Longtude
   err = 0;
   err |= extractNum(str, commaPos[3]+1, commaPos[3]+3, &gpsData->longDM.degrees);
   err |= extractNum(str, commaPos[3]+4, commaPos[3]+5, &gpsData->longDM.mins);
   err |= extractNum(str, commaPos[3]+7, commaPos[3]+11, &gpsData->longDM.minFrac);
   gpsData->longDM.quadrasphere = str[commaPos[4]+1];
   if (err) return 4;


printf("Lat: %d° %d' %d'' , Long: %d° %d' %d''\n",
      gpsData->latDM.degrees, gpsData->latDM.mins, gpsData->latDM.minFrac,gpsData->longDM.degrees, 
     gpsData->longDM.mins, gpsData->longDM.minFrac);  


latdegree=(gpsData->latDM.degrees);
latmin=(gpsData->latDM.mins);
latsec=(gpsData->latDM.minFrac);
londegree=(gpsData->longDM.degrees);
lonmin=(gpsData->longDM.mins);
lonsec=(gpsData->longDM.minFrac);

serv();

return 0;
}
