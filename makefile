output:
	g++ *.cpp -lSDL2 -L"lib/" -I"include/" -o RachitEngine

clean:
	rm *.o RachitEngine