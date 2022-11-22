#Plantform

# ----- Lib Type -----
if(AE_SHOULD_BUILD_STATIC_LIB)
	set(AE_LIB_TYPE STATIC)
else()
	set(AE_LIB_TYPE SHARED)
endif()

# ----- Link Dir -------
if(WIN32)
	link_directories(ArrowEngine ${ARROW_SOURCE_DIR}/ArrowEngine/External/glfw/lib-vc2022)
	link_directories(ArrowEngine ${ARROW_SOURCE_DIR}/ArrowEngine/External/Imgui)
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

# ----- Include Dir -----
#ThirdParty Dir
include_directories(AFTER "${MQ_SOURCE_DIR}/ThridParty/spdlog/include")
include_directories(AFTER "${MQ_SOURCE_DIR}/ThridParty/glfw/include")
# include_directories(AFTER "${MQ_SOURCE_DIR}/ArrowEngine/External/imgui")
#Arrow Engine Source Dir
include_directories(AFTER "${MQ_SOURCE_DIR}/Source")
