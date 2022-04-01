cmake_minimum_required( VERSION 3.10 )

project( "sr_api_c_sample_11_start_trigger" LANGUAGES C )

find_package( SmartRaySDK REQUIRED )

add_executable( ${PROJECT_NAME} "11_start_trigger.c" "../util/util.h" )

target_link_libraries( ${PROJECT_NAME} PUBLIC SmartRaySDK  )

# create binaries into separate _deploy directory
set_target_properties( ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_deploy/$<CONFIG>" )

# copy shared libs
#add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD COMMAND
#    ${CMAKE_COMMAND} -E copy_if_different ${SmartRaySDK_RUNTIME_LIBRARY_FILES} $<TARGET_FILE_DIR:${PROJECT_NAME}> )
