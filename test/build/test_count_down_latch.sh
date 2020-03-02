#!/bin/bash
set -e
set -x
CUDA_BASE_DIR=/usr/local/cuda
DEMO_BASE=~/rmms
SRC=${DEMO_BASE}/interface/src
DEMO_INC=${DEMO_BASE}/interface/src/include
DEMO_OUT_INC=${DEMO_BASE}/demo/include
DEMO_FILE=${DEMO_BASE}/interface/src/base

GENERAL_FILE="${DEMO_FILE}/thread.c \
              ${DEMO_FILE}/mutex.c \
              ${DEMO_FILE}/test/test_count_down_latch.c \
	          ${SRC}/current_thread.c \
	          ${DEMO_FILE}/condition.c \
              ${DEMO_FILE}/count_down_latch.c \
              ${DEMO_BASE}/interface/src/log.c"

INCLUDE="-I${UCX_BASE}/include \
         -I ${DEMO_INC} \
         -I ${SRC}/base/include \
         -I ${DEMO_OUT_INC}"

LIBRARY="-L ${CUDA_BASE_DIR}/lib64 -L ${UCX_BASE}/lib"
C_COMPILER=gcc
C_SUFFIX="-lucp  -lucs -luct -lucm    -lpthread -pthread -lcudart"
GCC_COMPILER="g++ -g -pthread"

${C_COMPILER} -O0 -g   ${GENERAL_FILE} \
 ${INCLUDE} \
 -L ${UCX_BASE}/lib/   \
 -o test_count_down_latch  -lucp  -lucs -luct -lucm    -lpthread   -Wl,-rpath=${UCX_BASE}/lib/


