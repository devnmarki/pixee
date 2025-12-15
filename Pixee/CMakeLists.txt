file(GLOB_RECURSE PIXEE_SRC CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_executable(Pixee ${PIXEE_SRC})

set_target_properties(Pixee PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED ON)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Pixee PROPERTY CXX_STANDARD 23)
endif()

target_include_directories(
	Pixee PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/vendor/SDL2/include
	${CMAKE_SOURCE_DIR}/vendor/glm/glm
)

target_link_libraries(Pixee  
	PUBLIC  
	Core
	SDL2
	SDL2main
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)