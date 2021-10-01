file(GLOB_RECURSE CPPS  ./*.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(UI_HEADERS ./mainwindow.ui)

qt_add_resources(RESOURCES ./resources/fxflow.qrc)

add_executable(fxflow ${CPPS} ${UI_HEADERS} ${RESOURCES})

target_link_libraries(fxflow nodes)
