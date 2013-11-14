project(tut03)

file(GLOB FILES data/*)

add_executable(cpuPositionOffset cpuPositionOffset.cpp ${FILES})
target_link_libraries(cpuPositionOffset ${LIBS})

add_executable(vertPositionOffset vertPositionOffset.cpp ${FILES})
target_link_libraries(vertPositionOffset ${LIBS})

add_executable(vertCalcOffset vertCalcOffset.cpp ${FILES})
target_link_libraries(vertCalcOffset ${LIBS})

add_executable(fragChangeColor fragChangeColor.cpp ${FILES})
target_link_libraries(fragChangeColor ${LIBS})
