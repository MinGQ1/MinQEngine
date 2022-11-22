######################################
# MinQEngine DLL
######################################
project(MinQEngine)

set(MQ_SOURCE_DIR ${PROJECT_SOURCE_DIR})

function( add_filtered_src filterName fileString )
	file(GLOB TMP_FILES ${fileString})
	set(SOURCE_FILES ${SOURCE_FILES} ${TMP_FILES} PARENT_SCOPE)
	source_group(${filterName} FILES ${TMP_FILES})
endfunction( add_filtered_src )

function( add_filtered_h filterName fileString )
	file(GLOB TMP_FILES ${fileString})
	set(HEADER_FILES ${HEADER_FILES} ${TMP_FILES} PARENT_SCOPE)
	source_group(${filterName} FILES ${TMP_FILES})
endfunction( add_filtered_h )

function( add_filtered_std relativePath )
	string(REPLACE "/" "\\" filterPart ${relativePath})
	add_filtered_h("MinQEngine\\${filterPart}" "${MQ_SOURCE_DIR}/${relativePath}/*.h")
	set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
	add_filtered_src("MinQEngine\\${filterPart}" "${MQ_SOURCE_DIR}/${relativePath}/*.cpp")
	add_filtered_src("MinQEngine\\${filterPart}" "${MQ_SOURCE_DIR}/${relativePath}/*.c")
	set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
endfunction( add_filtered_std )

set(HEADER_FILES)
set(SOURCE_FILES)

include(MinQConfigure)
add_subdirectory(Source)

add_library(MinQEngine ${AE_LIB_TYPE}
	${HEADER_FILES}
	${SOURCE_FILES}
)

include(MinQDefines)

target_link_libraries(MinQEngine glfw3)
target_link_libraries(MinQEngine Imgui)
target_link_libraries(MinQEngine vulkan-1)