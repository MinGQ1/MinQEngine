# Platform preprocessor defination
IF(WIN32)
    target_compile_definitions(MinQEngine PUBLIC MQ_PLATFORM_WINDOWS)
ENDIF(WIN32)

IF(WIN32)
	target_compile_definitions(MinQEngine PRIVATE 
	MQ_BUILD_DLL
	)
ENDIF(WIN32)