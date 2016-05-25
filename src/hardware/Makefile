CC = arm-linux-gnueabihf-gcc
CPP = arm-linux-gnueabihf-g++

OBJS = devreg.o portinfo.o cf_stub.o cpp_FIR.o
LIBS = -l pthread libsds_lib.a
INC = -I include/

all:	
	$(CC) -fPIC $(INC) -c devreg.c
	$(CC) -fPIC $(INC) -c cf_stub.c
	$(CC) -fPIC $(INC) -c portinfo.c
	$(CPP) -fPIC $(INC)  -Wall -O3 -D __SDSOC__ -c cpp_FIR.cpp
	$(CPP) -shared -fPIC -rdynamic $(OBJS)  -L build_linux/ -Wl,--start-group $(LIBS) -Wl,--end-group -o libfir.so

clean:
	rm *.o *.so 
