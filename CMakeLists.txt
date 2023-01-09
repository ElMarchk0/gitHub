cmake_minimum_required(VERSION 3.23)
project(Lab8)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab8 main.cpp TestSuite.h TestSuite.cpp Point.cpp Point.h Gameboard.cpp Gameboard.h GridTetromino.cpp GridTetromino.h TetrisGame.h TetrisGame.cpp Tetromino.cpp Tetromino.h images)
set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

# Detect and add SFML

# SFML version >= 2.5
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
# ex) If you are using debian10, 11, ubuntu20.24, 22.04 and installed with apt package manager, set the values below.
# set(SFML_DIR "/usr/local/vcpkg/ports/sfml/SFML")
# ex) If you are using Windows, manually set the location where you installed SFML.
# set(SFML_DIR "C:/Users/yourname/library/frameworks/SFML-2.5.1/lib/cmake/SFML")
# ex) If you are using MacOS and installed with homebrew, set the values as shown below.
# set(SFML_DIR "/usr/local/Cellar/sfml/2.5.1_1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    # SFML version >= 2.5
    #In SFML Version 2.5 or later, ${SFML_LIBRARIES}, ${SFML_DEPENDENCIES}, ${SFML_INCLUDE_DIR} no longer exist. Specify libraries individually.
    target_link_libraries(${PROJECT_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
