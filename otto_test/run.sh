#!/bin/bash

source sub_scripts/colors.sh
source sub_scripts/print.sh

function is_test_folder(){
    current_folder=$1
    if [ "$current_folder" == "../otto_test/" ]
    then
        return 1
    else
        return 0
    fi
}

# Global variables
ROOT_DIR="../"
TESTED_CONTAINER=$1
COMPILATION_ERROR_FILE="compilation.log"
EXECUTION_ERROR_FILE="execution.log"
STL_BIN="stl_bin"
YOUR_BIN="your_bin"
STL_OUTPUT="stl_${TESTED_CONTAINER}_output"
YOUR_OUTPUT="your_${TESTED_CONTAINER}_output"
STL_OUTPUT_FOLDER="stl_output/"
YOUR_OUTPUT_FOLDER="your_output/"
SRC_TESTS_FOLDER="tests/${TESTED_CONTAINER}_testing"
DIFF_FOLDER="diff/"
DIFF_FILE="diff_${TESTED_CONTAINER}"
TESTED_FILES_FOLDER="under_test/"
COMPILATION_FLAGS="-Wall -Wextra -Werror -g3 -fsanitize=address -std=c++98"
COUNT_PASSED_TESTS=0;
COUNT_FAILED_COMPILATION=0
COUNT_TOTAL_TESTS=0;

# Cleaning files
rm -rf ${DIFF_FOLDER} ${TESTED_FILES_FOLDER}
rm -f ${YOUR_BIN} ${YOUR_OUTPUT} ${STL_BIN} ${STL_OUTPUT}
rm -f ${COMPILATION_ERROR_FILE} ${EXECUTION_ERROR_FILE}

#Verify Argument passed
if [[ ${TESTED_CONTAINER} != "vector" ]] && [[ ${TESTED_CONTAINER} != "map" ]] && [[ ${TESTED_CONTAINER} != "stack" ]]
then    
    echo -e "ERROR: unkown argument"
    echo -e "USAGE: ./run.sh [stack|vector|map]"
    exit 1
fi
# Creating tests folder
mkdir -p "$TESTED_FILES_FOLDER"


# Copy all tested files and update rights
for folder in ../*/; do
    is_test_folder "$folder"
    is_test=$?
    if [ $is_test -eq 0 ]
    then
    #    echo "copy "$folder" in "$TESTED_FILES_FOLDER""
        cp -r "$folder" "./$TESTED_FILES_FOLDER"
    fi
done
chmod +r ./${TESTED_FILES_FOLDER}
if [[ $1 == "-debug" ]]
then
    exit
fi
# Creating diff and output folder
mkdir -p "$DIFF_FOLDER"
mkdir -p "$YOUR_OUTPUT_FOLDER"
mkdir -p "$STL_OUTPUT_FOLDER"

# Copy tests in active folder
cp -r "$SRC_TESTS_FOLDER" "$TESTED_FILES_FOLDER"

echo -en "TESTED CONTAINER >>>>>> $TESTED_CONTAINER\n"
#Loop through test files with compilation and execution for each test
for test in ./${TESTED_FILES_FOLDER}${TESTED_CONTAINER}_testing/*.cpp; do

    COUNT_TOTAL_TESTS=$((COUNT_TOTAL_TESTS + 1))
	test_name=$(basename ${test} | sed "s'\.cpp''")
    echo -en "${YELLOW}> TEST #${COUNT_TOTAL_TESTS}: ${test_name}${RESET} - "
    c++ ${COMPILATION_FLAGS} ${test} -o ${STL_BIN} -D NAMESPACE="std"
    c++ ${COMPILATION_FLAGS} ${test} -o ${YOUR_BIN} -D NAMESPACE="ft" 2>> ${COMPILATION_ERROR_FILE}
    if [ $? -eq 0 ]
    then
        echo -en "COMPILATION: ${GREEN}SUCCESS${RESET} - "
    else
        echo -en "COMPILATION: ${RED}ERROR${RESET}  - "
        echo -e "EXECUTION: ${RED}ERROR${RESET}"
        continue
    fi
    # STL_START=$(date +.%N)
    if [[ $2 ]] && [[ $2 == "time" ]]
    then
        echo -ne "\nSTL TIMES: "
        time ./${STL_BIN} > "${STL_OUTPUT_FOLDER}${STL_OUTPUT}_${test_name}.log" 2> /dev/null
        # STL_END=$(date +.%N)
        # YOURS_START=$(date +.%N)
        echo -e "------------------"
        echo -ne "YOUR TIMES: "
        time ./${YOUR_BIN} > "${YOUR_OUTPUT_FOLDER}${YOUR_OUTPUT}_${test_name}.log" 2>> ${EXECUTION_ERROR_FILE}
        EXEC_RET=$?
    elif [[ $2 ]] && [[ $2 != "time" ]]
    then
            echo -e "ERROR: unkown argument"
            echo -e "USAGE: ./run.sh [stack|vector|map]"
            exit 1
    else
        ./${STL_BIN} > "${STL_OUTPUT_FOLDER}${STL_OUTPUT}_${test_name}.log" 2> /dev/null
        ./${YOUR_BIN} > "${YOUR_OUTPUT_FOLDER}${YOUR_OUTPUT}_${test_name}.log" 2>> ${EXECUTION_ERROR_FILE}
        EXEC_RET=$?
    fi
    # YOURS_END=$(date +.%N)
    if [ ${EXEC_RET} -ne 0 ]
    then
        echo -e "EXECUTION: ${RED}ERROR${RESET}"
    else
        diff  ${STL_OUTPUT_FOLDER}${STL_OUTPUT}_${test_name}.log ${YOUR_OUTPUT_FOLDER}${YOUR_OUTPUT}_${test_name}.log > ${DIFF_FOLDER}${DIFF_FILE}_${test_name}
        if [ -s "${DIFF_FOLDER}${DIFF_FILE}_${test_name}" ]
        then
            echo -e "EXECUTION: ${RED}FAILED${RESET}"
        else
            echo -e "EXECUTION: ${GREEN}SUCCESS${RESET}"
            # STL_DIFF=$(echo "$STL_END - $STL_START" | bc -l)
            # YOURS_DIFF=$(echo "$YOURS_END - $YOURS_START" | bc -l)
            # EXEC_TIME_MULTIPLE=$(echo "$STL_DIFF/$YOURS_DIFF" | bc -l)
            # echo -e ""STL EXEC TIME / YOUR EXEC TIME": ${EXEC_TIME_MULTIPLE}"
            COUNT_PASSED_TESTS=$((COUNT_PASSED_TESTS + 1))
            rm -f ${DIFF_FOLDER}${DIFF_FILE}_${test_name}
        fi
    fi
    rm -f ${STL_BIN} ${YOUR_BIN}
done

# if [ $? != 0 ]
# thel
#l    echo -e "${RED} >> COMPILATION ERROR FROM ORIGINAL LIB${RESET}"
#     exit 1
# fi
# if [ $? != 0 ]
# then
#     echo -e "${RED} >> COMPILATION ERROR FROM ORIGINAL LIB${RESET}"
#     exit 1
# fi
#echo -e "${YELLOW}STDERROR OUTPUT...${RESET}"
#echo -e "${YELLOW}STL STDERROR: ${RESET}"
# start_stl=`date +%s%N`
# ./stl_vector > stl_${TESTED_CONTAINER}_output.log
# end_stl= `date +%s%N`
# #echo -e "${YELLOW}YOUR STDERROR: ${RESET}"
# start_yours=`date +%s%N`
# ./your_vector > your_${TESTED_CONTAINER}_output.log
# end_yours=`date +%s%N`
# echo -e STL: Execution time was `expr $end_stl - $start_stl` nanoseconds
# echo -e Yours: Execution time was `expr $end_yours - $start_yours` nanoseconds
print_score ${COUNT_PASSED_TESTS} ${COUNT_TOTAL_TESTS}
# rm -rf ${TESTED_FILES_FOLDER}