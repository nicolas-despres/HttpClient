set(target testHttp)

# Create library
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(${target} WIN32 main.cpp)
set_target_properties(${target} PROPERTIES FOLDER "Exe")

# Set link properties
target_link_libraries(${target} PUBLIC wininet)

target_link_options(${target} PRIVATE /SUBSYSTEM:CONSOLE)
