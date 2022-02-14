#!/bin/bash

EXIT_CODE=1;
while [[ $EXIT_CODE -eq 1 ]]
do
	./run.sh
	EXIT_CODE=$?
done
