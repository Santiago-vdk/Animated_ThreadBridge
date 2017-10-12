DIRS=build

all:	\
	main.c main.h \
	principal.c principal.h \
	rasp.c rasp.h \
	thread_data.c thread_data.h \
	lector_archivos.c lector_archivos.h \
	\
	arduino.c arduino.h \
	firmata.c firmata.h \
	serial.c serial.h \
	\
	calendarizador_fcfs.c calendarizador_fcfs.h \
	calendarizador_priority_queue.c calendarizador_priority_queue.h \
	calendarizador_real_time.c calendarizador_real_time.h \
	calendarizador_rr.c calendarizador_rr.h \
	calendarizador_sjf.c calendarizador_sjf.h \
	\
	algoritmos_control.c algoritmos_control.h \
	control_puentes_hardware.c control_puentes_hardware.c \
	puentes.c puentes.h \
	manejo_carros.c manejo_carros.h \
	mythread.c mythread.h 
	

	gcc -o build/main.o -c main.c 
	gcc -o build/principal.o -c principal.c 
	gcc -o build/rasp.o -c rasp.c 
	gcc -o build/thread_data.o -c thread_data.c -std=c99
	gcc -o build/lector_archivos.o -c lector_archivos.c 

	gcc -o build/arduino.o -c arduino.c 
	gcc -o build/firmata.o -c firmata.c 
	gcc -o build/serial.o -c serial.c 

	gcc -o build/calendarizador_fcfs.o -c calendarizador_fcfs.c 
	gcc -o build/calendarizador_priority_queue.o -c calendarizador_priority_queue.c 
	gcc -o build/calendarizador_real_time.o -c calendarizador_real_time.c 
	gcc -o build/calendarizador_rr.o -c calendarizador_rr.c 
	gcc -o build/calendarizador_sjf.o -c calendarizador_sjf.c 

	gcc -o build/algoritmos_control.o -c algoritmos_control.c 
	gcc -o build/control_puentes_hardware.o -c control_puentes_hardware.c 
	gcc -o build/puentes.o -c puentes.c 

	gcc -o build/manejo_carros.o -c manejo_carros.c 
	
	gcc -o build/mythread.o -c mythread.c -w

	gcc -o Animated_ThreadBridge build/main.o build/principal.o \
		build/rasp.o \
		build/thread_data.o \
		build/lector_archivos.o \
		build/arduino.o \
		build/firmata.o \
		build/serial.o \
		build/calendarizador_fcfs.o \
		build/calendarizador_priority_queue.o \
		build/calendarizador_real_time.o \
		build/calendarizador_rr.o \
		build/calendarizador_sjf.o \
		build/algoritmos_control.o \
		build/control_puentes_hardware.o \
		build/puentes.o \
		build/mythread.o \
		build/manejo_carros.o  -pthread -lSDL2 -lSDL2_image -lSDL2_ttf -lm
	


calendarizadores: \
		calendarizador_fcfs.c calendarizador_fcfs.h \
		calendarizador_priority_queue.c calendarizador_priority_queue.h \
		calendarizador_real_time.c calendarizador_real_time.h \
		calendarizador_rr.c calendarizador_rr.h \
		calendarizador_sjf.c calendarizador_sjf.h \

	gcc -Wall -o build/calendarizador_fcfs.o -c calendarizador_fcfs.c 
	gcc -Wall -o build/calendarizador_priority_queue.o -c calendarizador_priority_queue.c 
	gcc -Wall -o build/calendarizador_real_time.o -c calendarizador_real_time.c 
	gcc -Wall -o build/calendarizador_rr.o -c calendarizador_rr.c 
	gcc -Wall -o build/calendarizador_sjf.o -c calendarizador_sjf.c 


rasp: \
	rasp.c rasp.h

	gcc -Wall -o build/rasp.o -c rasp.c 

		
$(shell mkdir -p $(DIRS))


