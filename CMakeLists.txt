cmake_minimum_required(VERSION 3.14)
project(GC2ER)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    src/main.cpp
    src/ArgumentParser.cpp
    src/FileReader.cpp
    src/PostProcess.cpp
    src/GcodeProcess.cpp
    src/FileWriter.cpp
)

# Add header files
set(HEADERS
  src/ArgumentParser.hpp
  src/FileReader.hpp
  src/PostProcess.hpp
  src/GcodeProcess.hpp
  src/FileWriter.hpp
)

# wxWidgets library
# find_package(wxWidgets)

# wxWidgets include
# include(${wxWidgets_USE_FILE})

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Debug and release configuration settings
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Release configuration
    message("Building Release configuration")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2") # Adds optimization

    # Set specific properties for GUI application on macOS
    if(WIN32)
        # Windows
        set(CMAKE_GENERATOR_PLATFORM x64)
        set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
    elseif(APPLE)
        # macOS
        set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE FALSE
            # MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist
        )
        # Icon path definition
        # set(MACOSX_ICON_FILE ${CMAKE_SOURCE_DIR}/AppIcon.icns)

        # Copying an icon to an application package
        # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        #     COMMAND ${CMAKE_COMMAND} -E copy_if_different
        #         ${MACOSX_ICON_FILE}
        #         $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Resources/AppIcon.icns
        #     COMMENT "Copying AppIcon.icns to the app bundle"
        # )
    else()
        # Linux and other systems
        # No special settings needed here
    endif()
else()
    # Debug configuration
    message("Building Debug configuration")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # Adds debugging information
endif()

# wxWidgets knihovny
# target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# Copy directories
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/in $<TARGET_FILE_DIR:${PROJECT_NAME}>/in
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/out $<TARGET_FILE_DIR:${PROJECT_NAME}>/out
)