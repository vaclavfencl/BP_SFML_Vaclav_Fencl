add_executable(APP4 kolize.cpp)

target_link_libraries(APP4 PRIVATE SFML::Graphics SFML::Window SFML::System)

if (WIN32)
  add_custom_command(TARGET APP4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP4> $<TARGET_FILE_DIR:APP4>
    COMMAND_EXPAND_LISTS)
  set_property(TARGET APP4 PROPERTY ENABLE_EXPORTS ON)
endif()
