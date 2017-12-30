PROJECT(UtahTeapod)
cmake_minimum_required(VERSION 3.0)

## 実行ファイルの出力ディレクトリの設定
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

## ライブラリファイルの出力ディレクトリの設定
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib)


## プロジェクトに含むソースコードのトラッキング
FILE(GLOB_RECURSE ALL_FILES
	RELATIVE ${CMAKE_SOURCE_DIR}
 	UtahTeapot/*.hpp UtahTeapot/*.cpp)

## ディレクトリ構成を保持したままビルドシステムを構築するマクロ
foreach(FILE ${ALL_FILES})
  get_filename_component(PARENT_DIR "${FILE}" PATH)
  # skip src or include and changes /'s to \\'s
  string(REGEX REPLACE "(\\./)?(src|include)/?" "" GROUP "${PARENT_DIR}")
  string(REPLACE "/" "\\" GROUP "${GROUP}")

  # group into "Source Files" and "Header Files"
  set(GROUP "Source Files\\${GROUP}")

  source_group("${GROUP}" FILES "${FILE}")
endforeach()


# C++11を有効にする
add_definitions("-Wall -std=c++11")

add_executable(utah_teapod
	${ALL_FILES}
)
