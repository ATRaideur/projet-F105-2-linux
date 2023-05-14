FLAGS = -std=c++17 -Wall -Wextra -Wpedantic -D_GNU_SOURCE -Werror=all -O2 -g

all : ulbzip ulbunzip 

ulbunzip : ulbunzip.cpp
	g++ $(FLAGS) utils.cpp ulbunzip.cpp -o decodeur

ulbzip : ulbzip.cpp
	g++ $(FLAGS) utils.cpp ulbzip.cpp -o encodeur
