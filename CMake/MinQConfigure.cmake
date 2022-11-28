#Plantform

# ----- Lib Type -----
if(MQ_SHOULD_BUILD_STATIC_LIB)
	set(MQ_LIB_TYPE STATIC)
else()
	set(MQ_LIB_TYPE SHARED)
endif()