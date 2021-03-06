# Source files and their filters
include(CMakeSources.cmake)

# Packages
if(AUDIO_MODULE MATCHES "FMOD")
	find_package(FMOD)
endif()

# Includes
set(BansheeFMOD_INC 
	"Include" 
	"../BansheeUtility/Include" 
	"../BansheeCore/Include"
	"../BansheeOpenAudio/Include"
	${FMOD_INCLUDE_DIRS}
	"../../Dependencies/libogg/include"
	"../../Dependencies/libvorbis/include")

include_directories(${BansheeFMOD_INC})	
	
# Target
add_library(BansheeFMOD SHARED ${BS_BANSHEEFMOD_SRC})

# Defines
target_compile_definitions(BansheeFMOD PRIVATE -DBS_FMOD_EXPORTS)

# Libraries
## External libs: FMOD, Vorbis, Ogg
target_link_libraries(BansheeFMOD PRIVATE ${FMOD_LIBRARIES})	

add_library_per_config_multi(BansheeFMOD libvorbis libvorbis libvorbis libvorbis)
add_library_per_config_multi(BansheeFMOD libvorbisfile libvorbis libvorbisfile libvorbisfile)
add_library_per_config(BansheeFMOD libogg Release/libogg Debug/libogg)

## Local libs
target_link_libraries(BansheeFMOD PUBLIC BansheeUtility BansheeCore)

# IDE specific
set_property(TARGET BansheeFMOD PROPERTY FOLDER Plugins)