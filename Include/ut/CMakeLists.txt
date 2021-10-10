target_sources(ut
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ut_CompileTimeUtahTeapot.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mesh_type.h
    ${CMAKE_CURRENT_SOURCE_DIR}/utah_teapot.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility.hpp
)

add_subdirectory(detail)