project(tut06)

file(GLOB FILES data/*)

add_executable(Translation Translation.cpp ${FILES})
target_link_libraries(Translation ${LIBS})

add_executable(Scale Scale.cpp ${FILES})
target_link_libraries(Scale ${LIBS})

add_executable(Rotations Rotations.cpp ${FILES})
target_link_libraries(Rotations ${LIBS})

add_executable(Hierarchy Hierarchy.cpp ${FILES})
target_link_libraries(Hierarchy ${LIBS})
