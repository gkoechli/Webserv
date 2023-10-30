#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage: $0 filename [GET|DELETE]"
	exit 1
fi

if [ ! -f "$1" ]; then
	echo "Error: $1 is not a file"
	exit 1
fi

url="localhost:8080/test1.html"
data=$(cat "$1")
method=${2:-POST}

case $method in
	GET)
		curl -X GET "$url"
		;;
	DELETE)
		curl -X DELETE "$url"
		;;
	*)
		curl -X POST -H "Content-Type: application/json" -d "$data" "$url"
		;;
esac