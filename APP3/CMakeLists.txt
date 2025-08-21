add_executable(APP3 vstupy.cpp)

target_link_libraries(APP3 PRIVATE SFML::Graphics SFML::Window SFML::System)

if(WIN32)
  add_custom_command(TARGET APP3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP3> $<TARGET_FILE_DIR:APP3>
    COMMAND_EXPAND_LISTS)
  set_property(TARGET APP3 PROPERTY ENABLE_EXPORTS ON)
endif()
