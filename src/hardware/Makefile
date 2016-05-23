all:	
	arm-linux-gnueabihf-gcc -fPIC -I include/ -c devreg.c
	arm-linux-gnueabihf-gcc -fPIC -I include/ -c cf_stub.c
	arm-linux-gnueabihf-gcc -fPIC -I include/ -c portinfo.c
	arm-linux-gnueabihf-g++ -fPIC -I include/  -I src/ -Wall -O3 -D __SDSOC__ -c cpp_FIR.cpp
	arm-linux-gnueabihf-g++ -fPIC -I include/  -I src/ -Wall -O3 -D __SDSOC__ -c cpp_FIR_test.cpp
	arm-linux-gnueabihf-g++ -shared -fPIC -rdynamic devreg.o portinfo.o cf_stub.o cpp_FIR.o cpp_FIR_test.o -L build_linux/ -Wl,--start-group -l pthread  libsds_lib.a -Wl,--end-group -o libfir.so

clean:
	rm *.o *.so
