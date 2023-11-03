
TARGET = fdcp

SOURCE = main.c serial.c udp.c fdcp_forward.c

make:
	$(CC) -o $(TARGET) $(SOURCE)

clean: 	
	rm -v $(TARGET)






