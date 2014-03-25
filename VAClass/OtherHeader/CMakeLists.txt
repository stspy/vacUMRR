#
# Source files
#
# Here is where you can add the name of your local Transform classes.
#
FILE( GLOB ALL_INCLUDES "*.hpp" "*.h" )

SET( ALL_SRCS 
	${ALL_INCLUDES}
)
 
# The installation path for the include-files
INSTALL( FILES ${ALL_INCLUDES} DESTINATION include )
