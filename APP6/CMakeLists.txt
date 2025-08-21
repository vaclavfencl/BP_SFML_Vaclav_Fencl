add_executable(APP6 text.cpp)

target_link_libraries(APP6 PRIVATE SFML::Graphics SFML::Window SFML::System)

if (WIN32)
  add_custom_command(TARGET APP6 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP6> $<TARGET_FILE_DIR:APP6>
    COMMAND_EXPAND_LISTS)
  set_property(TARGET APP6 PROPERTY ENABLE_EXPORTS ON)
endif()
