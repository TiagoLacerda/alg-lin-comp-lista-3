SOURCE := $(wildcard *.cpp */*.cpp */*/*.cpp)

FLAGS := -Wall -O3 -Wno-unused-variable

INCLUDES := -Iinclude

build:
	g++ -g \
	src/lu/lu.cpp \
	src/matrix/matrix_io.cpp \
	src/matrix/matrix_operations.cpp \
	src/matrix/matrix.cpp \
	src/qr/qr.cpp \
	src/utils/utils.cpp \
	src/main.cpp \
	-o main.exe $(FLAGS) $(INCLUDES)

tests:
	g++ -g \
	src/matrix/matrix_io.test.cpp \
	src/matrix/matrix_operations.test.cpp \
	src/matrix/matrix.test.cpp \
	src/matrix/matrix_io.cpp \
	src/matrix/matrix_operations.cpp \
	src/matrix/matrix.cpp \
	src/test.cpp \
	-o tests.exe $(FLAGS) $(INCLUDES)
