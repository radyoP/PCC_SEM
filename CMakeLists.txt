cmake_minimum_required(VERSION 3.7)
project(PCC_SEM)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)

add_executable(PCC_SEM src/main.cpp src/MainWindow.cpp src/MainWindow.h src/DragLabel.h src/DragLabel.cpp src/MainFrame.h src/MainFrame.cpp src/utils.h src/NetworkChecker.cpp src/NetworkChecker.h src/Configuration.cpp src/Configuration.h src/SunriseSunsetChecker.cpp src/SunriseSunsetChecker.h sunset_lib/src/SunSet.h sunset_lib/src/SunSet.cpp)


find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Gui)

qt5_use_modules( PCC_SEM Core Widgets Gui)

target_link_libraries(PCC_SEM ${QT_LIBRARIES})
