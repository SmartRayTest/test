cmake_minimum_required( VERSION 3.10 )

project( "sr_api_cpp_sample_03_live_image" LANGUAGES CXX )

find_package( SmartRaySdk REQUIRED )

add_executable( ${PROJECT_NAME} "03_live_image.cpp" )

target_link_libraries( ${PROJECT_NAME} PUBLIC SmartRaySdk  )

# use Multi-threaded static run-time libraries (/MT )
target_compile_options( ${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/MT> )

# create binaries into separate _deploy directory
set_target_properties( ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_deploy/$<CONFIG>" )

# copy shared libs
add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_if_different ${SmartRaySdk_RUNTIME_LIBRARY_FILES} $<TARGET_FILE_DIR:${PROJECT_NAME}> )
