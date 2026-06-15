set(TARGET_NAME main)
set(SOURCES main.cpp
        Window/Window.cpp
        UI/UiController.cpp
        Objects/LogoObject.cpp
        Objects/PauseTextObject.cpp
        ConfigReader/ConfigReader.cpp
        ConfigReader/ConfigReader.h
        AppState/AppState.h
        UI/UiController.h
        Objects/LogoObject.h
        Objects/PauseTextObject.h
        RenderableObject/RenderableObject.h)


add_executable(${TARGET_NAME}
        ${SOURCES})

#target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_link_libraries(${TARGET_NAME} PUBLIC
        ImGui-SFML::ImGui-SFML
        nlohmann_json::nlohmann_json
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.json
        $<TARGET_FILE_DIR:${TARGET_NAME}>/config.json
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/fonts
        $<TARGET_FILE_DIR:${TARGET_NAME}>/fonts
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/images
        $<TARGET_FILE_DIR:${TARGET_NAME}>/images
)
