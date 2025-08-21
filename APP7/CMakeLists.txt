add_executable(APP7 obrazky.cpp)

target_link_libraries(APP7 PRIVATE SFML::Graphics SFML::Window SFML::System)

if (WIN32)
  add_custom_command(TARGET APP7 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP7> $<TARGET_FILE_DIR:APP7>
    COMMAND_EXPAND_LISTS)
  set_property(TARGET APP7 PROPERTY ENABLE_EXPORTS ON)
endif()
