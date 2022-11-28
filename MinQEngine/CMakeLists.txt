######################################
# MinQEngine DLL
######################################
project(MinQEngine)

set(HEADER_FILES)
set(SOURCE_FILES)

add_filtered_std("Source/Core")
add_filtered_std("Source/Events")
add_filtered_std("Source/Imgui")
add_filtered_std("Source/Input")
add_filtered_std("Source/Logger")
add_filtered_std("Source/Memory")
add_filtered_std("Source/Utilities")
add_filtered_std("Source/Platform")
add_filtered_std("Source/Configuration")
add_filtered_std("Source/RenderSystems")
add_filtered_std("Source/RenderSystems/vulkan")

IF(WIN32)
add_filtered_std("Source/Platform/Windows")
ENDIF(WIN32)

include(MinQConfigure)
add_subdirectory(Source)
add_subdirectory(ThirdParty/Imgui)

add_library(MinQEngine ${MQ_LIB_TYPE}
	${HEADER_FILES}
	${SOURCE_FILES}
)

include(MinQDefines)

target_link_libraries(MinQEngine glfw3)
target_link_libraries(MinQEngine Imgui)
target_link_libraries(MinQEngine vulkan-1)

add_dependencies(MinQEngine Imgui)