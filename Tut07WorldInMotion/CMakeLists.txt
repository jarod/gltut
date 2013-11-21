project(tut07)

file(GLOB FILES data/*)

add_executable(WorldScene WorldScene.cpp ${FILES})
target_link_libraries(WorldScene ${LIBS})

add_executable(WorldWithUBO WorldWithUBO.cpp ${FILES})
target_link_libraries(WorldWithUBO ${LIBS})
