project(tut04)

file(GLOB FILES data/*)

add_executable(OrthoCube OrthoCube.cpp ${FILES})
target_link_libraries(OrthoCube ${LIBS})

add_executable(ShaderPerspective ShaderPerspective.cpp ${FILES})
target_link_libraries(ShaderPerspective ${LIBS})

add_executable(MatrixPerspective MatrixPerspective.cpp ${FILES})
target_link_libraries(MatrixPerspective ${LIBS})

add_executable(AspectRatio AspectRatio.cpp ${FILES})
target_link_libraries(AspectRatio ${LIBS})
