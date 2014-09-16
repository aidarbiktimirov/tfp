TFP_INC          = ./include
INC              = -I$(TFP_INC)

CFLAGS           = $(INC) -std=c++11
CXX              = g++

# Basic test with numbers
main: $(TFP_INC)/tfp.h ./src/main.cpp
	$(CXX) $(CFLAGS) ./src/main.cpp -otest

clean:
	rm -f ./test
