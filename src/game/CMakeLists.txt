set(SOURCES 
    game.cpp
)

target_sources(cartesian_combat_game PRIVATE ${SOURCES})

find_package(SDL3 CONFIG REQUIRED)

target_link_libraries(cartesian_combat_game PRIVATE
    SDL3::SDL3
    ccb::engine
)