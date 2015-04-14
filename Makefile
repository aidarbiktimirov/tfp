TFP_INC          = ./include
INC              = -I$(TFP_INC)

CFLAGS           = $(INC) -std=c++11
CXX              = g++

# Basic test with numbers
main: $(TFP_INC)/tfp.h ./src/main.cpp
	$(CXX) $(CFLAGS) ./src/main.cpp -otest

bf: $(TFP_INC)/tfp.h ./src/bf.cpp
	$(CXX) $(CFLAGS) ./src/bf.cpp -obf

clean:
	rm -f ./test
