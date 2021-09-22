#!/bin/bash

FQBN='esp32:esp32:esp32doit-devkit-v1'
BASE_CMD="arduino-cli compile -b $FQBN"

compile() {
	$BASE_CMD "$@"
}

upload() {
	PORT=$1
	if [ -z $PORT ]; then
		echo 'Missing port'
		exit 1
	fi
	shift
	$BASE_CMD -ut -p $PORT "$@"
}

if [ -z "$1" ]; then
	echo 'Missing subcommand'
elif [[ $1 =~ ^(compile|upload)$ ]]; then
  "$@"
else
  echo "Invalid subcommand $1" >&2
  exit 1
fi
