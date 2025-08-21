add_executable(APP8 animace.cpp)

target_link_libraries(APP8 PRIVATE SFML::Graphics SFML::Window SFML::System)

if (WIN32)
  add_custom_command(TARGET APP8 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP8> $<TARGET_FILE_DIR:APP8>
    COMMAND_EXPAND_LISTS)
  set_property(TARGET APP8 PROPERTY ENABLE_EXPORTS ON)
endif()
