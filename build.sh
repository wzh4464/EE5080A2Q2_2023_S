# build g++
#   export LDFLAGS="-L/opt/homebrew/opt/lapack/lib"
#   export CPPFLAGS="-I/opt/homebrew/opt/lapack/include"

# add_definitions(-DGL_SILENCE_DEPRECATION)

# include_directories(/usr/local/include)
# include_directories(/opt/homebrew/include)

# "-framework glut"
# "-framework opengl"
# "-lglew"
# "debug mode"

g++ -std=c++11 -o main main.cpp -llapacke -llapack -lblas -L/opt/homebrew/opt/lapack/lib -I/opt/homebrew/opt/lapack/include -I/opt/homebrew/include -I/usr/local/include -DGL_SILENCE_DEPRECATION -framework glut -framework opengl -lglew -g