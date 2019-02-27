all:
	g++ shell.cpp utils.cpp customCommands.cpp -L/usr/include -lreadline  -o shell 
	# we have to include the readline library explicitly by mentioning 
	