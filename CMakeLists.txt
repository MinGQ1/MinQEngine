cmake_minimum_required (VERSION 3.5)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Moudle Path
set (CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/CMake"
)

include(GlobalConfigure)
# Sub dir
add_subdirectory(MinQEngine)

# TODO: remove it
add_subdirectory(TestBed)
#Project dependencies
# add_dependencies(Application MinQEngine)