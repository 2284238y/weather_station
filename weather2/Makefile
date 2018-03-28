CC=g++

weather-station:
	$(CC) weather-station.c -lrt -o weather-station `mysql_config --cflags` `mysql_config --libs` 

clean:
	rm weather-station
