cmake_minimum_required(VERSION 3.7)
project(PCC_SEM)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)


find_package(cppzmq)


add_executable(PCC_SEM src/main.cpp include/DragLabel.h src/DragLabel.cpp include/MainFrame.h src/MainFrame.cpp include/utils.h
        src/NetworkChecker.cpp include/NetworkChecker.h src/Configuration.cpp include/Configuration.h
        src/SunriseSunsetChecker.cpp include/SunriseSunsetChecker.h sunset_lib/src/SunSet.h sunset_lib/src/SunSet.cpp src/ArduinoComunicator.cpp include/ArduinoComunicator.h)



find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Gui)

qt5_use_modules( PCC_SEM Core Widgets Gui)

target_link_libraries(PCC_SEM ${QT_LIBRARIES} cppzmq)


