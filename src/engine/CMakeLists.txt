set(SOURCES 
    window.cpp
)

add_library(cartesian_combat_engine STATIC ${SOURCES})
add_library(ccb::engine ALIAS cartesian_combat_engine)

find_package(imgui CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

target_link_libraries(cartesian_combat_engine PRIVATE
    SDL3::SDL3
    imgui::imgui
)