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
	add_filtered_h("${PROJECT_NAME}\\${filterPart}" "${CMAKE_CURRENT_SOURCE_DIR}/${relativePath}/*.h")
	set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
	add_filtered_src("${PROJECT_NAME}\\${filterPart}" "${CMAKE_CURRENT_SOURCE_DIR}/${relativePath}/*.cpp")
	add_filtered_src("${PROJECT_NAME}\\${filterPart}" "${CMAKE_CURRENT_SOURCE_DIR}/${relativePath}/*.c")
	set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
endfunction( add_filtered_std )

set(MQ_SOURCE_DIR "${CMAKE_SOURCE_DIR}/MinQEngine")

# ----- Include Dir -----
#ThirdParty Dir
include_directories(AFTER "${MQ_SOURCE_DIR}/ThirdParty/spdlog/include")
include_directories(AFTER "${MQ_SOURCE_DIR}/ThirdParty/glfw/include")
include_directories(AFTER "${MQ_SOURCE_DIR}/ThirdParty/imgui")
#Arrow Engine Source Dir
include_directories(AFTER "${MQ_SOURCE_DIR}/Source")

# ----- Link Dir -------¡¤
if(WIN32)
	link_directories(MinQEngine ${MQ_SOURCE_DIR}/ThirdParty/glfw/lib)
	link_directories(MinQEngine ${MQ_SOURCE_DIR}/ThirdParty/External/Imgui)
endif()

#----- Vulkan -----
find_package(Vulkan)
if(NOT Vulkan_FOUND)
	message(FATAL_ERROR "Error: Vulkan Not Found")
endif()

add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)

if(NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
	include_directories(AFTER "${Vulkan_INCLUDE_DIRS}")
	set(VULKAN_LIB_DIRS ${Vulkan_INCLUDE_DIRS})
	STRING(REGEX REPLACE "/Include" "/Lib" VULKAN_LIB_DIRS 
	${VULKAN_LIB_DIRS})
endif()

if(EXISTS "${VULKAN_LIB_DIRS}")
	link_directories(MinQEngine ${VULKAN_LIB_DIRS})
	link_directories(Imgui ${VULKAN_LIB_DIRS})
else()
	message(FATAL_ERROR "Error: Vulkan Lib Dir Not Found")
endif()
