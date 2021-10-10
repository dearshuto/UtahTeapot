PROJECT(UtahTeapod)
cmake_minimum_required(VERSION 3.10)

## 実行ファイルの出力ディレクトリの設定
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

## ライブラリファイルの出力ディレクトリの設定
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# C++17を有効にする
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(utah_teapod
# 	${ALL_FILES}
# )

add_library(ut)
target_include_directories(ut
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include
)
add_subdirectory(Include)
add_subdirectory(Sources)
add_subdirectory(Examples)