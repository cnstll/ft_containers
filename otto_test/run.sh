#!/bin/bash

source sub_scripts/colors.sh

ROOT_DIR="../"
TESTED_CONTAINER="vector"
DIFF_FILE="diff_${TESTED_CONTAINER}.log"

rm -f ${DIFF_FILE}
rm -f your_${TESTED_CONTAINER}_output.log your_${TESTED_CONTAINER} stl_${TESTED_CONTAINER}_output.log stl_${TESTED_CONTAINER}

cp ./${ROOT_DIR}${TESTED_CONTAINER}.hpp .
cp ./${ROOT_DIR}test_${TESTED_CONTAINER}.cpp .
cp ./${ROOT_DIR}iterator.hpp .

#c++ -DACTIVE_NAMESPACE="ft" -g -fsanitize=address -Wall -Wextra -Werror -std=c++98 test_${TESTED_CONTAINER}.cpp -o your_vector
c++ -Wall -Wextra -Werror -g3 -fsanitize=address test_${TESTED_CONTAINER}.cpp -o your_vector -D NAMESPACE="ft" 
#c++ -DACTIVE_NAMESPACE="ft" -Wall -Wextra -Werror test_${TESTED_CONTAINER}.cpp -o your_vector
if [ $? != 0 ]
then
    echo -e "${RED} >> COMPILATION ERROR FROM ORIGINAL LIB${RESET}"
    exit 1
fi
#c++ -DACTIVE_NAMESPACE="std" -g -fsanitize=address -Wall -Wextra -Werror -std=c++98 test_${TESTED_CONTAINER}.cpp -o stl_vector
c++ -Wall -Wextra -Werror -g3 -fsanitize=address test_${TESTED_CONTAINER}.cpp -o stl_vector -D NAMESPACE="std" 
#c++ -DACTIVE_NAMESPACE="std" -Wall -Wextra -Werror test_${TESTED_CONTAINER}.cpp -o stl_vector
if [ $? != 0 ]
then
    echo -e "${RED} >> COMPILATION ERROR FROM ORIGINAL LIB${RESET}"
    exit 1
fi

#echo -e "${YELLOW}STDERROR OUTPUT...${RESET}"
#echo -e "${YELLOW}STL STDERROR: ${RESET}"
./stl_vector > stl_${TESTED_CONTAINER}_output.log
#echo -e "${YELLOW}YOUR STDERROR: ${RESET}"
./your_vector > your_${TESTED_CONTAINER}_output.log

#echo
diff  stl_${TESTED_CONTAINER}_output.log your_${TESTED_CONTAINER}_output.log > ${DIFF_FILE}

if [ -s "$DIFF_FILE" ]
then
    echo -e "${RED} ✖ AT LEAST 1 TEST FAILED - CHECK DIFF${RESET}"
else
    echo -e "${GREEN} ✔ TESTS PASSED${RESET}"
    rm -f ${DIFF_FILE}
fi

rm -f your_${TESTED_CONTAINER} stl_${TESTED_CONTAINER}
#rm -f your_${TESTED_CONTAINER}_output.log stl_${TESTED_CONTAINER}_output.log
rm -f *.hpp *.cpp
