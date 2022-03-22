cmake_minimum_required( VERSION 3.10 )

project( "sr_api_c_sample_09_multiexposure" LANGUAGES C )

find_package( SmartRaySdk REQUIRED )

add_executable( ${PROJECT_NAME} "09_multiexposure.c" )

target_link_libraries( ${PROJECT_NAME} PUBLIC SmartRaySdk  )
target_compile_definitions( ${PROJECT_NAME} PUBLIC -D_CRT_SECURE_NO_WARNINGS )

# create binaries into separate _deploy directory
set_target_properties( ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_deploy/$<CONFIG>/bin" )

# copy shared libs
add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_if_different ${SmartRaySdk_RUNTIME_LIBRARY_FILES} $<TARGET_FILE_DIR:${PROJECT_NAME}> )
