# Minimum CMake version required
cmake_minimum_required(VERSION 3.1)

# Specify compiler features
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

# Clang++
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")  # -Weverything equivalent to g++ -pedantic, -Werror and -Wall
else()
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror")  # -Wsuggest-override")
endif()

# Nice name for the IDEs
project(HelloGMlib VERSION 1.0.1 LANGUAGES C CXX)



################################
# Find the required Qt libraries
find_package(Qt5Core 5.7)
find_package(Qt5Quick 5.7)
find_package(Qt5Gui 5.7)

################################
# Find GMlib
find_package(
  GMlib 0.6.0 EXACT
  PATHS ${GMLIB_DIR}
  NO_DEFAULT_PATH
)

include_directories( ${GMlib_INCLUDE_DIRS} )
link_directories(    ${GMlib_LINK_DIRS}    )
add_definitions(     ${GMlib_DEFINITIONS}  )

include_directories( ${GLEW_INCLUDE_DIRS} )
if(WIN32)
  add_definitions(-DGLEW_STATIC)
endif(WIN32)




#######
# Files

set( HDRS
  gmlibscenequickfbo.h
  gmlibscenequickfborenderer.h
  guiapplication.h
  inlinefborendertarget.h
  scenario.h
  testtorus.h
  window.h

  )

set( SRCS
  gmlibscenequickfbo.cpp
  gmlibscenequickfborenderer.cpp
  guiapplication.cpp
  inlinefborendertarget.cpp
  scenario.cpp
  testtorus.cpp
  window.cpp

  main.cpp
  )

#########
# Moc'ing
QT5_WRAP_CPP( HDRS_MOC
  gmlibscenequickfbo.h
  scenario.h
  guiapplication.h
  window.h
  )

set( RCCS
 application.qrc
)

QT5_ADD_RESOURCES( RCCS_MOC ${RCCS} )




#########
# Compile
add_executable( ${CMAKE_PROJECT_NAME} ${HDRS} ${SRCS} ${HDRS_MOC} ${FORM_HDRS} ${RCCS_MOC} )

######
# Link
target_link_libraries( ${CMAKE_PROJECT_NAME}
  ${GMlib_LIBRARIES}
  Qt5::Core
  Qt5::Quick
  Qt5::Gui
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  )

#set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 98)
#set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 14)

