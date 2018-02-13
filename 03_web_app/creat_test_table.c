#include <my_global.h>
#include <mysql.h>
#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include <unistd.h>

#define DATABASE_NAME  "sensor_log"
#define DATABASE_USERNAME "root"
#define DATABASE_PASSWORD "labuser"


void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}


int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL);
  
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
  
  if (mysql_query(con, "DROP TABLE IF EXISTS table_sensor_log")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE table_sensor_log(id MEDIUMINT NOT NULL AUTO_INCREMENT, sensor_id INT, sensor_value FLOAT, timestamp DATETIME, PRIMARY KEY (id))")) {      
      finish_with_error(con);
  }
  
		// insert data for test reasons 
  for( int a = 1; a < 40; a++ ) 
  {
	  time_t current_time;
	  char* c_time_string;
	  int r = rand() % 3;
	  float t = a*0.129+20;  //just random temperature value
	  char q[1024];
	  int sensor = 1; 
	  current_time = time(NULL);
	  c_time_string = ctime(&current_time); // convert time to string 
	  sprintf(q,"INSERT INTO table_sensor_log(sensor_id, sensor_value, timestamp) VALUES(%d,%g,NOW())",sensor,t); // convert query to the string q
	  	  
   if (mysql_query(con, q)) 
	{
      finish_with_error(con);
	}
	// output on the screen for testing reasons
	printf("Current temperature  on = %f  C    time = %s  \n", t,c_time_string); 
	sleep(1); //delay 1 sec 
	// output on the screen for testing reasons
   }
		// insert data for test reasons 	

  mysql_close(con);
  exit(0);
}



