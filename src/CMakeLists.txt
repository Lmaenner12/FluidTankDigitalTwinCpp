# Sources and Headers
set(LIBRARY_SOURCES
    "Render.cpp"
    "Controller.cpp"
    "PIController.cpp"
    "main.cpp"
    "Pump.cpp"
    "Render.cpp"
    "Sensor.cpp"
    "Tank.cpp")

# Library
add_library(${ADAS_LIB} ${LIBRARY_SOURCES})
target_include_directories(${IMPLOT_LIB} PUBLIC "./")
target_link_libraries(${ADAS_LIB} PUBLIC ${IMGUI_LIB})
target_link_libraries(${ADAS_LIB} PUBLIC ${IMPLOT_LIB})
target_link_libraries(${ADAS_LIB} PUBLIC ${JSON_LIB})
target_set_warnings(TARGET ${ADAS_LIB} ENABLE ON AS_ERROR OFF)
