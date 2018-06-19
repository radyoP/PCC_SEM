cmake_minimum_required(VERSION 3.7)
project(PCC_SEM)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)

add_executable(PCC_SEM main.cpp MainWindow.cpp MainWindow.h DragLabel.h DragLabel.cpp MainFrame.h MainFrame.cpp utils.h NetworkChecker.cpp NetworkChecker.h Configuration.cpp Configuration.h SunriseSunsetChecker.cpp SunriseSunsetChecker.h sunset/src/SunSet.h sunset/src/SunSet.cpp)


find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Gui)

qt5_use_modules( PCC_SEM Core Widgets Gui)

target_link_libraries(PCC_SEM ${QT_LIBRARIES})
