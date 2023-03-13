# build g++
#   export LDFLAGS="-L/opt/homebrew/opt/lapack/lib"
#   export CPPFLAGS="-I/opt/homebrew/opt/lapack/include"

g++ -std=c++11 -o main main.cpp -llapacke -llapack -lblas -L/opt/homebrew/opt/lapack/lib -I/opt/homebrew/opt/lapack/include