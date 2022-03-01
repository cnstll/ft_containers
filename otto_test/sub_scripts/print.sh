#!/bin/bash

print_welcome()
{
	OTTO_WELCOME="./assets/otto_welcome"
	if [ $QUIET_SWITCH -eq 0 ]
	then
		cat "${OTTO_WELCOME}"
		echo -e "${BOLDBLUE}\nWELCOME TO OTTO!! AN AUTOMATED TEST SUITE FOR MINISHELL$RESET"
		sleep 2
		echo
	fi
}

print_success()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -e " ${BOLDGREEN}✔${RESET} ${GREEN}test $1${RESET}"
	fi
}

print_failure()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -e " ${BOLDRED}✖${RESET} ${RED}test $1${RESET}"
	fi
	if [ "$2" ]
	then
		echo "$2" >> "failed_tests"
	fi
}

print_crash()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -e "${BOLDRED}💣${RESET} ${RED}test $1${RESET}"
	fi
	echo "$2" >> "crash_tests"
}

print_test_name()
{
	if [ $QUIET_SWITCH -eq 0 ]
	then
		echo -ne "\n${BOLDBLUE}CURRENT TEST: $1${RESET}"
	fi
}

print_score()
{
	TOTAL_PASSED_TESTS=$1
  TOTAL_NUMBER_OF_TESTS=$2
	if [ "$TOTAL_PASSED_TESTS" -eq "$TOTAL_NUMBER_OF_TESTS" ]
	then
		echo -e "${BOLDGREEN}>> SCORE: ${TOTAL_PASSED_TESTS} / ${TOTAL_NUMBER_OF_TESTS} ${RESET}"
	else
		echo -e "${BOLDRED}>> SCORE: ${TOTAL_PASSED_TESTS} / ${TOTAL_NUMBER_OF_TESTS} ${RESET}"
	fi
}