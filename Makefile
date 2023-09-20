CC = gcc
CFLAGS = -lwiringPi -lpthread
OBJS = rpi_1_stub.o rpi_1_can.o rpi_1_main.o 
TARGET = executable

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm	-f	*.o
	rm	-f	$(TARGET)




# rpi1

# executable1 : rpi_1_stub.o rpi_1_can.o rpi_1_main.o 
# 	gcc -o executable1 rpi_1_stub.o rpi_1_can.o rpi_1_main.o 

# rpi_1_stub.o : rpi_1_stub.c
# 	gcc -c -o rpi_1_stub.o rpi_1_stub.c

# rpi_1_can.o : rpi_1_can.c
# 	gcc -c -o rpi_1_can.o rpi_1_can.c

# rpi_1_main.o : rpi_1_main.c
# 	gcc -c -o rpi_1_main.o rpi_1_main.c


# clean:
# 	rm	-f	*.o
# 	rm	-f	$(TARGET)



# rpi2
# executable2 : rpi_2_lcd.o rpi_2_stub.o rpi_2_can.o rpi_2_main.o
# 	gcc -o executable1 rpi_2_lcd.o rpi_2_stub.o rpi_2_can.o rpi_2_main.o

# rpi_1_led.o : rpi_2_lcd.c
# 	gcc -c -o rpi_2_lcd.o rpi_2_lcd.c

# rpi_1_stub.o : rpi_2_stub.c
# 	gcc -c -o rpi_2_stub.o rpi_2_stub.c

# rpi_1_can.o : rpi_2_can.c
# 	gcc -c -o rpi_2_can.o rpi_2_can.c

# rpi_1_main.o : rpi_2_main.c
# 	gcc -c -o rpi_2_main.o rpi_2_main.c


# clean:
# 	rm	-f	*.o
# 	rm	-f	$(TARGET)
