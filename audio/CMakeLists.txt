add_library(audio STATIC AudioListener.cpp AudioSource.cpp AudioManager.cpp)
target_link_libraries(audio PUBLIC OpenAL filesystem)
target_include_directories(audio PUBLIC ./)
