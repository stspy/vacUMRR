FILE(GLOB src_files "*.*")

SET (ALL_SRCS ${src_files})

ADD_EXECUTABLE (JasonTest_01 ${ALL_SRCS})

TARGET_LINK_LIBRARIES (JasonTest_01 lib_json) 

SET_TARGET_PROPERTIES(JasonTest_01 PROPERTIES FOLDER "Apps")

INSTALL_TARGETS (/bin JasonTest_01)