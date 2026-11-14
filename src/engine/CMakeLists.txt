set(SOURCES 
	"window.cpp"
 "window.h"
 "renderer.cpp"
 "renderer.h"
)

add_library(cartesian_combat_engine STATIC ${SOURCES})
add_library(ccb::engine ALIAS cartesian_combat_engine)

find_package(imgui CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

target_include_directories(cartesian_combat_engine PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/..
) 

target_link_libraries(cartesian_combat_engine PUBLIC
	SDL3::SDL3
	imgui::imgui
	d3d11
	dxgi
	d3dcompiler
)