add_executable(APP2 smycka.cpp)

target_link_libraries(APP2 PRIVATE SFML::Graphics SFML::Window SFML::System)

if(WIN32)
  add_custom_command(TARGET APP2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP2> $<TARGET_FILE_DIR:APP2>
    COMMAND_EXPAND_LISTS)
  set_property(TARGET APP2 PROPERTY ENABLE_EXPORTS ON)
endif()
