#!/bin/bash
STL_START=$(date +%N)
#echo -e "START TIME: ${STL_START}"
sleep 1
STL_END=$(date +%N)
#echo -e "END TIME: ${STL_END}"
STL_DIFF=$(echo "$STL_END - $STL_START" | bc)
echo -e "STL DIFF  : ${STL_DIFF}"
YOURS_START=$(date +%N)
#echo -e "START TIME: ${YOURS_START}"
sleep 10
YOURS_END=$(date +%N)
#echo -e "END TIME: ${YOURS_END}"
YOURS_DIFF=$(echo "$YOURS_END - $YOURS_START" | bc)
echo -e "YOURS DIFF: ${YOURS_DIFF}"
MULTIPLE=$(echo "$YOURS_DIFF/$STL_DIFF" | bc)
echo -e "MULTIPLE: $MULTIPLE"