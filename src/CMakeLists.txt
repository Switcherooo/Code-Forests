set(FILES main.cpp)
set(SUBDIRECTORIES structures application clickable gui dependencies)

foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()
if(FILES)
	target_sources(${PROJECT_LIB} PUBLIC ${FILES})
endif()
