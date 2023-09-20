#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.16...3.21)
project(Brem)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Set DMG4
#
set (DMG4_DIR /cluster/home/ggurung/app/DMG4)
set (DMG4_INCLUDE_DIR ${DMG4_DIR}/include)
set (DMG4_LIBRARY_DIR ${DMG4_DIR}/lib)

#----------------------------------------------------------------------------
# Find GSL
#
find_package(GSL REQUIRED)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${DMG4_INCLUDE_DIR}
	${DMG4_INCLUDE_DIR}/DMG4
	${GSL_INCLUDE_DIR}
	)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
link_directories (
  ${DMG4_LIBRARY_DIR}
  )

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(Brem brem.cc ${sources} ${headers})
target_link_libraries(Brem ${Geant4_LIBRARIES} DarkMatter DMG4 UtilsDM ${GSL_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(Brem_SCRIPTS
  Brem.in
  Brem.out
  init_vis.mac
  vis.mac
  )

foreach(_script ${Brem_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
#add_custom_target(B1 DEPENDS Brem)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS Brem DESTINATION bin)
