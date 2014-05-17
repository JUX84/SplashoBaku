INC=inc/
SRC=src/
OBJ=obj/
BIN=bin/
OUT=-o $(OBJ)
C11=-std=c++11
IRR=-I/usr/include/irrlicht -L/usr/lib -lIrrlicht -lGL -lGLU

$(BIN)exe: $(OBJ)Main.o $(OBJ)SplashBack.o $(OBJ)Splash.o $(OBJ)SplashDamier.o $(OBJ)MouseEventReceiver.o
	g++ $(OBJ)*.o $(IRR) -o $(BIN)exe
$(OBJ)Main.o: $(SRC)Main.cpp $(INC)SplashBack.hpp
	g++ -c $(SRC)Main.cpp -I$(INC) $(IRR) $(OUT)Main.o
$(OBJ)SplashBack.o: $(SRC)SplashBack.cpp $(INC)SplashBack.hpp $(INC)SplashDamier.hpp $(INC)Splash.hpp 
	g++ -c $(SRC)SplashBack.cpp -I$(INC) $(IRR) $(C11) $(OUT)SplashBack.o
$(OBJ)SplashDamier.o: $(SRC)SplashDamier.cpp $(INC)SplashDamier.hpp $(INC)Splash.hpp
	g++ -c $(SRC)SplashDamier.cpp -I$(INC) $(IRR) $(OUT)SplashDamier.o
$(OBJ)Splash.o: $(SRC)Splash.cpp $(INC)Splash.hpp
	g++ -c $(SRC)Splash.cpp -I$(INC) $(IRR) $(OUT)Splash.o
$(OBJ)MouseEventReceiver.o: $(SRC)MouseEventReceiver.cpp $(INC)MouseEventReceiver.hpp
	g++ -c $(SRC)MouseEventReceiver.cpp -I$(INC) $(IRR) $(OUT)MouseEventReceiver.o
run:
	make && ./bin/exe
clean:
	rm $(OBJ)*.o $(BIN)exe
