#!/bin/bash          
cd Client; make
cd Client; gnome-terminal -x sh -c "./Client localhost 8080; sleep 10"