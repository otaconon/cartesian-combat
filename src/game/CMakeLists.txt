set(SOURCES 
    game.cpp
)

target_sources(cartesian_combat_game PRIVATE ${SOURCES})

target_link_libraries(cartesian_combat_game PRIVATE
    ccb::engine
)