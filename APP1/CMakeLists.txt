add_executable(APP1 okno.cpp)
target_link_libraries(APP1 PRIVATE SFML::Graphics SFML::Window SFML::System)

if(WIN32)
  add_custom_command(TARGET APP1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:APP1> $<TARGET_FILE_DIR:APP1>
    COMMAND_EXPAND_LISTS)  
  set_property(TARGET APP1 PROPERTY ENABLE_EXPORTS ON)
endif()
