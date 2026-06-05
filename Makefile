all:
	g++ -O0 -g main.cpp -o my_secure_app

clean:
	rm -f my_secure_app
