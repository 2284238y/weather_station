/** Example c code for accessing Honeywell temperature+humidity sensors
*
* Authors: 
Aurelie Crawford - Electronics and Social Engagement
Craig McCallum - Data Acquisition and Processing
Damir Gulamov - Web App Display
*
* License: free 
*
* Pin connections for Raspberry Pi 3:
*
*   RPi2   |  Sensor
*  ------------------
*    01    |    8   (VDD)
*    03    |    4   (SDA)
*    05    |    3   (SCL)
*    09    |    2   (GND)
*
* Reference circuit: datasheet HIH6030
* "Honeywell HumidIcon Digital Humidity/Temperature Sensors - HIH6000 Series"
https://sensing.honeywell.com/index.php?ci_id=147070
*
* Technical note on I22 communication:
* http://sensing.honeywell.com/i2c-comms-humidicon-tn-009061-2-en-final-07jun12.pdf
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <time.h>


#include <my_global.h> // for mysql connection 
#include <mysql.h> // for mysql connection 
#include <mysql/mysql.h> // for mysql connection 

#define DATABASE_NAME  "sensor_log"
#define DATABASE_USERNAME "root"
#define DATABASE_PASSWORD "Your mysql password"


//#include "CppTimer.h"   //Generic C++ Timer for Linux. It's a wrapper around the Linux timers


void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int main(int argc, char **argv)
{
  int fd;                               /* File descriptor*/
  const char *fileName = "/dev/i2c-1";  /* Name of the port we will be using. On Raspberry 2 this is i2c-1, on an older Raspberry Pi 1 this might be i2c-0.*/
  int  address = 0x27;                  /* Address of Honeywell sensor shifted right 1 bit */
  unsigned char buf[4];                 /* Buffer for data read/written on the i2c bus */
  

  
  
  MYSQL *con = mysql_init(NULL);  // 
  
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  

  if (mysql_real_connect(con, "localhost", DATABASE_USERNAME, DATABASE_PASSWORD, 
          DATABASE_NAME, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  
  
  
  
  /* Open port (r/w) */
  if ((fd = open(fileName, O_RDWR)) < 0)
  {
    printf("Failed to open i2c port\n");
    exit(1);
  }

  /* Set port options and slave devie address */
  if (ioctl(fd, I2C_SLAVE, address) < 0)
  {
    printf("Unable to get bus access to talk to slave\n");
    exit(1);
  }


  for( int a = 10; a < 200; a = a + 1 )
	  
{
sleep(1); //delay 5 sec 
	  
  
  /* Initiate measurement by sending a zero bit (see datasheet for communication pattern) */
  if ((i2c_smbus_write_quick(fd, 0)) != 0)
  {
    printf("Error writing bit to i2c slave\n");
    exit(1);
  }

  /* Wait for 100ms for measurement to complete.
     Typical measurement cycle is 36.65ms for each of humidity and temperature, so you may reduce this to 74ms. */
  usleep(100000);

  /* read back data */
  if (read(fd, buf, 4) < 0)
  {
    printf("Unable to read from slave\n");
    exit(1);
  }
  else
  {
    
	/* Humidity is located in first two bytes */
    int reading_hum = (buf[0] << 8) + buf[1];
    double humidity = reading_hum / 16382.0 * 100.0;
    

    /* Temperature is located in next two bytes, padded by two trailing bits */
    int reading_temp = (buf[2] << 6) + (buf[3] >> 2);
    double temperature = reading_temp / 16382.0 * 165.0 - 40;
    
	
	
	// start insert data to mysql 
	  time_t current_time;
	  char* c_time_string;
	  char q[1024];
	  int sensor = 1; 
	  int sensor2 = 2;
	  int flag;
	  current_time = time(NULL);
	  c_time_string = ctime(&current_time); // convert time to string 
	  if (flag == 0) 
		  {
	  sprintf(q,"INSERT INTO table_sensor_log(sensor_id, sensor_value, timestamp) VALUES(%d,%g,NOW())",sensor,temperature); // convert query to the string q
			flag = 1;
			printf("Current temperature = %f C          time = %s  \n", temperature,c_time_string);
			}
			else
			{
	  	  sprintf(q,"INSERT INTO table_sensor_log(sensor_id, sensor_value, timestamp) VALUES(%d,%g,NOW())",sensor2,humidity);	// convert query to the string q
			flag = 0;
			printf("Current humidity    = %f percent    time = %s  \n", humidity,c_time_string);
			}
   if (mysql_query(con, q)) 
	{
      finish_with_error(con);
	}
	   	// end insert data to mysql 
	
	
  }
  
}
mysql_close(con);
  exit(0);
  return 0;
}

