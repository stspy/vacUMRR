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
ADD_LIBRARY (vacNetRec ${ALL_SRCS})


TARGET_LINK_LIBRARIES(vacNetRec)

SET_TARGET_PROPERTIES(vacNetRec PROPERTIES FOLDER "VAClass")
SET_TARGET_PROPERTIES(vacNetRec PROPERTIES
                      DEBUG_POSTFIX ${VAC_DEBUG_PREFIX})

# The installation path for the link-library
INSTALL_TARGETS( /lib vacNetRec )

# The installation path for the include-files
INSTALL( FILES ${ALL_INCLUDES} DESTINATION include )
