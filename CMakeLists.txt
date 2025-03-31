cmake_minimum_required(VERSION 3.16)

project(comm2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_PREFIX_PATH "C:/Qt/StaticQt")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)


add_executable(comm2
  main.cpp
  mainwindow.cpp
  Graph.cpp
  clickablescene.cpp
  mainwindow.h
  clickablescene.h
  Graph.h
  mainwindow.ui
  resources.qrc
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")


target_link_libraries(comm2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)


include(GNUInstallDirs)
install(TARGETS comm2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
