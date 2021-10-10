add_executable(hello_utah_teapot ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_include_directories(hello_utah_teapot
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Include/ut
)
target_link_libraries(hello_utah_teapot ut)