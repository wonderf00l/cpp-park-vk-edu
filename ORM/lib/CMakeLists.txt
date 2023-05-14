add_library(ORM src/ORM.cpp)
add_library(ORMGenerator src/ORMGenerator.cpp)
add_library(IModelManager src/IModelManager.cpp)
target_include_directories(ORM PUBLIC include)
target_include_directories(ORMGenerator PUBLIC include)
target_include_directories(IModelManager PUBLIC include)

add_subdirectory(tests)