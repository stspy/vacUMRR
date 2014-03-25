set(FOO_SRCS
	main.cpp
	server.cpp
	server.h
	)

QT4_WRAP_CPP(FOO_MOC_H server.h)

ADD_EXECUTABLE(ServerTest_01 
		${FOO_SRCS} 
		${FOO_MOC_H}
)
		
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
TARGET_LINK_LIBRARIES(ServerTest_01 ${QT_LIBRARIES} lib_json vacNetSend  ws2_32 vacDataParse_d ${LIB_MYSQL})
SET_TARGET_PROPERTIES(ServerTest_01 PROPERTIES FOLDER "Apps")
INSTALL_TARGETS(/bin ServerTest_01)
