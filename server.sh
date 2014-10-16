#!/bin/bash          
cd Server; make
cd Server; gnome-terminal -x sh -c "./Server 8080; sleep 10"