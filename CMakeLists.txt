cmake_minimum_required(VERSION 3.30)
project(Task4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(Task4 main.cpp
        MainWindow.h
        MainWindow.cpp
        TextProcessor.h
        TextProcessor.cpp
        Logger.h
        Logger.cpp
        main.cpp
)
target_link_libraries(Task4
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

# Enable testing
enable_testing()

# Add test executable
add_executable(Task4_tests TextProcessorTests.cpp TextProcessor.cpp TextProcessor.h)
target_link_libraries(Task4_tests PRIVATE ${GTEST_BOTH_LIBRARIES} pthread)


