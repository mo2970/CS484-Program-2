all:
	cd Server; $~make
	cd Client; $~make
	cd Server; gnome-terminal -x sh -c "./Server 8080"
	sleep 1
	cd Client; gnome-terminal -x sh -c "./Client localhost 8080"
