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
 
# Create the jason C++ library
ADD_LIBRARY (lib_json ${ALL_SRCS})

SET_TARGET_PROPERTIES(lib_json PROPERTIES FOLDER "ExtLibs")
SET_TARGET_PROPERTIES(lib_json PROPERTIES
                      DEBUG_POSTFIX ${VAC_DEBUG_PREFIX})

INSTALL_TARGETS(/lib lib_json)

INSTALL( FILES ${ALL_INCLUDES} DESTINATION include/json )
