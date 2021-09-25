file(GLOB_RECURSE CPPS  ./*.cpp )

qt_add_resources(RESOURCES ./resources/fxflow.qrc)

add_executable(fxflow ${CPPS} ${RESOURCES} BlurEffectDataModel.cpp BlurEffectDataModel.hpp AlphaBlendEffectDataModel.cpp AlphaBlendEffectDataModel.hpp)

target_link_libraries(fxflow nodes)
