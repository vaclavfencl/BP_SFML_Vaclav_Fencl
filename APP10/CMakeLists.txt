add_executable(APP10 view.cpp)

target_link_libraries(APP10 PRIVATE SFML::Graphics SFML::Window SFML::System)

if (WIN32)
  add_custom_command(TARGET APP10 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP10> $<TARGET_FILE_DIR:APP10>
    COMMAND_EXPAND_LISTS)
  set_property(TARGET APP10 PROPERTY ENABLE_EXPORTS ON)
endif()
