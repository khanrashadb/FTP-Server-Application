#Makefile for CSCI 460 Project 2


CC = g++
WFLAG = -Wall
DFLAG = -ggdb
CFLAG = -c


SOURCES = src
INCLUDES = include
BUILDS = build
BINARY = bin
TESTS = test
EXAMPLE = example



all: ${BINARY}/ftpserver  ${TESTS}/${BINARY}/ftpservertest



${BINARY}/ftpserver: ${BUILDS}/ftp_server.o ${BUILDS}/ftp_server_connection_listener.o \
		${BUILDS}/ftp_server_net_util.o	${BUILDS}/ftp_server_string_util.o ${BUILDS}/ftp_server_connection.o \
		${BUILDS}/ftp_server_session.o ${BUILDS}/ftp_server_request.o ${BUILDS}/ftp_server_passive.o \
		${BUILDS}/ftp_server_nlist.o ${BUILDS}/ftp_server_retrieve.o
	${CC} ${WFLAG} ${DFLAG} -o ${BINARY}/ftpserver ${BUILDS}/ftp_server.o ${BUILDS}/ftp_server_connection_listener.o \
	${BUILDS}/ftp_server_net_util.o	${BUILDS}/ftp_server_string_util.o ${BUILDS}/ftp_server_connection.o \
	${BUILDS}/ftp_server_session.o ${BUILDS}/ftp_server_request.o ${BUILDS}/ftp_server_passive.o \
	${BUILDS}/ftp_server_nlist.o ${BUILDS}/ftp_server_retrieve.o



${TESTS}/${BINARY}/ftpservertest: ${TESTS}/${BUILDS}/ftp_server_test.o ${TESTS}/${BUILDS}/ftp_server_test_net_util.o \
		${BUILDS}/ftp_server_string_util.o \
		${BUILDS}/ftp_server_net_util.o \
		${BUILDS}/ftp_server_connection_listener.o \
		${BUILDS}/ftp_server_connection.o \
		${BUILDS}/ftp_server_passive.o \
		${BUILDS}/ftp_server_session.o \
		${BUILDS}/ftp_server_request.o \
		${BUILDS}/ftp_server_nlist.o \
		${BUILDS}/ftp_server_retrieve.o \
		${TESTS}/${BUILDS}/ftp_client_test_connection.o \
		${TESTS}/${BUILDS}/ftp_client_test_control.o \
		${TESTS}/${BUILDS}/ftp_client_test_command.o
	${CC} ${WFLAG} -lboost_unit_test_framework -o ${TESTS}/${BINARY}/ftpservertest \
	${BUILDS}/ftp_server_string_util.o \
	${BUILDS}/ftp_server_net_util.o \
	${BUILDS}/ftp_server_connection_listener.o \
	${BUILDS}/ftp_server_connection.o \
	${BUILDS}/ftp_server_passive.o \
	${BUILDS}/ftp_server_session.o \
	${BUILDS}/ftp_server_request.o \
	${BUILDS}/ftp_server_nlist.o \
	${BUILDS}/ftp_server_retrieve.o \
	${TESTS}/${BUILDS}/ftp_server_test.o \
	${TESTS}/${BUILDS}/ftp_server_test_net_util.o \
	${TESTS}/${BUILDS}/ftp_client_test_connection.o \
	${TESTS}/${BUILDS}/ftp_client_test_control.o \
	${TESTS}/${BUILDS}/ftp_client_test_command.o


${BUILDS}/ftp_server.o: ${SOURCES}/ftp_server.cpp ${INCLUDES}/ftp_server_connection_listener.h \
			${INCLUDES}/ftp_server_session.h ${INCLUDES}/ftp_server_net_util.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server.o ${SOURCES}/ftp_server.cpp

${BUILDS}/ftp_server_connection_listener.o: ${SOURCES}/ftp_server_connection_listener.cpp \
					${INCLUDES}/ftp_server_connection_listener.h \
					${INCLUDES}/ftp_server_net_util.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_connection_listener.o \
	${SOURCES}/ftp_server_connection_listener.cpp

${BUILDS}/ftp_server_connection.o: ${SOURCES}/ftp_server_connection.cpp \
				   ${INCLUDES}/ftp_server_connection.h ${INCLUDES}/ftp_server_net_util.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_connection.o ${SOURCES}/ftp_server_connection.cpp

${BUILDS}/ftp_server_session.o: ${SOURCES}/ftp_server_session.cpp \
				${INCLUDES}/ftp_server_session.h ${INCLUDES}/ftp_server_connection.h \
				${INCLUDES}/ftp_server_request.h ${INCLUDES}/ftp_server_response.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_session.o ${SOURCES}/ftp_server_session.cpp

${BUILDS}/ftp_server_net_util.o: ${SOURCES}/ftp_server_net_util.cpp ${INCLUDES}/ftp_server_net_util.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_net_util.o ${SOURCES}/ftp_server_net_util.cpp

${BUILDS}/ftp_server_string_util.o: ${SOURCES}/ftp_server_string_util.cpp ${INCLUDES}/ftp_server_string_util.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_string_util.o ${SOURCES}/ftp_server_string_util.cpp

${BUILDS}/ftp_server_request.o: ${SOURCES}/ftp_server_request.cpp \
				${INCLUDES}/ftp_server_request.h ${INCLUDES}/ftp_server_session.h \
				${INCLUDES}/ftp_server_connection.h ${INCLUDES}/ftp_server_response.h \
				${INCLUDES}/ftp_server_passive.h ${INCLUDES}/ftp_server_nlist.h \
				${INCLUDES}/ftp_server_retrieve.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_request.o ${SOURCES}/ftp_server_request.cpp

${BUILDS}/ftp_server_passive.o: ${SOURCES}/ftp_server_passive.cpp \
				${INCLUDES}/ftp_server_passive.h ${INCLUDES}/ftp_server_connection.h \
				${INCLUDES}/ftp_server_connection_listener.h \
				${INCLUDES}/ftp_server_net_util.h ${INCLUDES}/ftp_server_string_util.h \
				${INCLUDES}/ftp_server_request.h ${INCLUDES}/ftp_server_response.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_passive.o ${SOURCES}/ftp_server_passive.cpp

${BUILDS}/ftp_server_nlist.o: ${SOURCES}/ftp_server_nlist.cpp ${INCLUDES}/ftp_server_nlist.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_nlist.o ${SOURCES}/ftp_server_nlist.cpp

${BUILDS}/ftp_server_retrieve.o: ${SOURCES}/ftp_server_retrieve.cpp \
				 ${INCLUDES}/ftp_server_retrieve.h ${INCLUDES}/ftp_server_connection.h \
				 ${INCLUDES}/ftp_server_response.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_retrieve.o ${SOURCES}/ftp_server_retrieve.cpp


.PHONY: clean run-server run-example-server run-example-client \
	test test-deliverable1 test-deliverable2 test-deliverable3 \
	test-example test-example-deliverable1 test-example-deliverable2 test-example-deliverable3 \
	list-server kill-server


clean:
	-rm -rf ${BINARY}/*
	-rm -rf ${TESTS}/${BINARY}/*
	-rm -rf ${BUILDS}/*


list-server:
	@-ps -aux | grep ftpserver | grep -v grep

kill-server:
	@-killall -9 ftpserver


run-server: ${BINARY}/ftpserver
	${BINARY}/ftpserver 2020


run-example-server: ${EXAMPLE}/${BINARY}/ftpserver
	${EXAMPLE}/${BINARY}/ftpserver 2020


run-example-client: ${EXAMPLE}/${BINARY}/ftpclient
	${EXAMPLE}/${BINARY}/ftpclient `hostname -I` 2020



test-deliverable1:   ${BINARY}/ftpserver ${TESTS}/${BINARY}/ftpservertest
	${TESTS}/${BINARY}/ftpservertest --log_level=all --run_test=ftp_server_deliverable1 \
		-- bin/ftpserver


test-deliverable2:   ${BINARY}/ftpserver ${TESTS}/${BINARY}/ftpservertest
	${TESTS}/${BINARY}/ftpservertest --log_level=all --run_test=ftp_server_deliverable2 \
		-- bin/ftpserver


test-deliverable3:   ${BINARY}/ftpserver ${TESTS}/${BINARY}/ftpservertest
	${TESTS}/${BINARY}/ftpservertest --log_level=all --run_test=ftp_server_deliverable3 \
		-- bin/ftpserver


test: test-deliverable1 test-deliverable2 test-deliverable3



test-example-deliverable1: ${EXAMPLE}/${BINARY}/ftpserver ${TESTS}/${EXAMPLE}/${BINARY}/ftpservertest
	${TESTS}/${EXAMPLE}/${BINARY}/ftpservertest --log_level=all --run_test=ftp_server_deliverable1 \
		-- example/bin/ftpserver


test-example-deliverable2: ${EXAMPLE}/${BINARY}/ftpserver ${TESTS}/${EXAMPLE}/${BINARY}/ftpservertest
	${TESTS}/${EXAMPLE}/${BINARY}/ftpservertest --log_level=all --run_test=ftp_server_deliverable2 \
		-- example/bin/ftpserver


test-example-deliverable3: ${EXAMPLE}/${BINARY}/ftpserver ${TESTS}/${EXAMPLE}/${BINARY}/ftpservertest
	${TESTS}/${EXAMPLE}/${BINARY}/ftpservertest --log_level=all --run_test=ftp_server_deliverable3 \
		-- example/bin/ftpserver


test-example: test-example-deliverable1 test-example-deliverable2 test-example-deliverable3





