project(Testbed)

set(HEADER_FILES)
set(SOURCE_FILES)

add_filtered_std("Source")

add_executable(TestbedApplication ${HEADER_FILES} ${SOURCE_FILES})

#Project dependencies
add_dependencies(TestbedApplication MinQEngine)

target_link_libraries(TestbedApplication MinQEngine)