all:
	g++ shell.cpp utils.cpp -L/usr/include -lreadline  -o shell 
	# we have to include the readline library explicitly by mentioning 
	