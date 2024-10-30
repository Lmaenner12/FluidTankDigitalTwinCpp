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
add_library(${DIGITAL_TWIN_LIB} ${LIBRARY_SOURCES})
target_include_directories(${IMPLOT_LIB} PUBLIC "./")
target_link_libraries(${DIGITAL_TWIN_LIB} PUBLIC ${IMGUI_LIB})
target_link_libraries(${DIGITAL_TWIN_LIB} PUBLIC ${IMPLOT_LIB})
target_link_libraries(${DIGITAL_TWIN_LIB} PUBLIC ${JSON_LIB})
target_set_warnings(TARGET ${DIGITAL_TWIN_LIB} ENABLE ON AS_ERROR OFF)
