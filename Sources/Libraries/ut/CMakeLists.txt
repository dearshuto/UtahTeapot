target_sources(ut
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/utah_teapot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility.cpp
)
add_subdirectory(detail)