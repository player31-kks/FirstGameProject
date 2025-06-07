# CMakeList.txt: LightYearsGame에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_library (${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
	"src/framework/Application.cpp"
	"include/framework/Application.h"
	"include/EntryPoint.h" 
	"src/EntryPoint.cpp" 
	"include/framework/Core.h" 
	"src/framework/Core.cpp" 
	"src/framework/World.cpp" 
	"src/framework/Actor.cpp" 
	"include/framework/Actor.h"

	"include/framework/Object.h" 
	"src/framework/Object.cpp"
 "include/framework/AssetManager.h" "src/framework/AssetManager.cpp" "include/framework/MathUtil.h" "src/framework/MathUtil.cpp")
target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC 
	"./include"
)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${LIGHT_YEARS_ENGINE_TARGET_NAME} PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-audio)

#dll 추가해주는것
function(CopyLibtoTarget LIB_NAME TARGET_NAME)
	add_custom_command(
		TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:${LIB_NAME}>
		$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

CopyLibtoTarget(sfml-graphics ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibtoTarget(sfml-window ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibtoTarget(sfml-system ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibtoTarget(sfml-audio ${LIGHT_YEARS_ENGINE_TARGET_NAME})
# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.
