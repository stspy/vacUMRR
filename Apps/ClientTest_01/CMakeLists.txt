set(FOO_SRCS
	main.cpp
	client.cpp
	client.h
	)

QT4_WRAP_CPP(FOO_MOC_H client.h)

ADD_EXECUTABLE(ClientTest_01 
		${FOO_SRCS} 
		${FOO_MOC_H}
)
		
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
TARGET_LINK_LIBRARIES(ClientTest_01 ${QT_LIBRARIES} lib_json vacNetRec ws2_32)
SET_TARGET_PROPERTIES(ClientTest_01 PROPERTIES FOLDER "Apps")
INSTALL_TARGETS(/bin ClientTest_01)
