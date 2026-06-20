g++ src/main.cpp -I C:/raylib/raylib/src -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -o main.exe

g++ src/main.cpp -I C:/raylib/raylib/src -I src -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -o main.exe