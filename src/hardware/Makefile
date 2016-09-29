CC = arm-linux-gnueabihf-gcc
CPP = arm-linux-gnueabihf-g++

OBJSH = devreg.o cf_stub.o cpp_FIR.o portinfo.o 
LIBS = -l pthread /usr/lib/libsds_lib.so
INC = -I include/

all:	
	$(CC) -fPIC $(INC) -c -g3 -gstabs devreg.c
	$(CC) -fPIC $(INC) -c -g3 -gstabs cf_stub.c
	$(CC) -fPIC $(INC) -c -g3 -gstabs cpp_FIR.cpp
	$(CC) -fPIC $(INC) -c -g3 -gstabs portinfo.c
	$(CPP) -g3 -gstabs -shared -fPIC -rdynamic $(OBJSH)  -Wl,--start-group $(LIBS) -Wl,--end-group -o libfir.so
	rm *.o

clean:
	rm -f *.so *.o
