#!/bin/bash
function report(){
        echo "Error $?"
        exit $1
}
make all || report 1
./create_delete $* || report 2
