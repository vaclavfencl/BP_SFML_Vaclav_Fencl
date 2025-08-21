add_executable(APP5 transformace.cpp)

target_link_libraries(APP5 PRIVATE SFML::Graphics SFML::Window SFML::System)

if (WIN32)
  add_custom_command(TARGET APP5 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP5> $<TARGET_FILE_DIR:APP5>
    COMMAND_EXPAND_LISTS)
  set_property(TARGET APP5 PROPERTY ENABLE_EXPORTS ON)
endif()
