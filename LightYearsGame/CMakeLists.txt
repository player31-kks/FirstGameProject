# CMakeList.txt: LightYearsGame에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (${LIGHT_YEARS_GAME_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
)
target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC 
	"./include"
)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${LIGHT_YEARS_GAME_TARGET_NAME} PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME})

#dll 추가해주는것
function(CopyLibDirToTarget LIB_NAME TARGET_NAME)
	add_custom_command(
		TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND} -E copy_directory
		$<TARGET_FILE_DIR:${LIB_NAME}>
		$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

CopyLibtoTarget(${LIGHT_YEARS_GAME_TARGET_NAME} ${LIGHT_YEARS_GAME_TARGET_NAME})
