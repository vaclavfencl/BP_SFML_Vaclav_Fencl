add_executable(APP9 zvuk.cpp)

target_link_libraries(APP9 PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)

if (WIN32)
  add_custom_command(TARGET APP9 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP9> $<TARGET_FILE_DIR:APP9>
    COMMAND_EXPAND_LISTS)
  set_property(TARGET APP9 PROPERTY ENABLE_EXPORTS ON)
endif()
