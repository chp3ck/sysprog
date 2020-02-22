#!/bin/bash

function report()
{
	echo "Error $?"
	exit $1
}
make all || report 1
#./socket_client $* || report 2
#./socket_server $* || report 3
