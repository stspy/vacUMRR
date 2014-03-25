#
# Source files
#
# Here is where you can add the name of your local Transform classes.
#
FILE( GLOB ALL_SOURCES "*.cpp" "*.c" )
FILE( GLOB ALL_INCLUDES "*.hpp" "*.h" )

SET( ALL_SRCS 
	${ALL_SOURCES}
	${ALL_INCLUDES}
)
 
# Create the minimal path C++ library
ADD_LIBRARY (vacNetSend ${ALL_SRCS})


TARGET_LINK_LIBRARIES(vacNetSend)

SET_TARGET_PROPERTIES(vacNetSend PROPERTIES FOLDER "VAClass")
SET_TARGET_PROPERTIES(vacNetSend PROPERTIES
                      DEBUG_POSTFIX ${VAC_DEBUG_PREFIX})

# The installation path for the link-library
INSTALL_TARGETS( /lib vacNetSend )

# The installation path for the include-files
INSTALL( FILES ${ALL_INCLUDES} DESTINATION include )
