#include <ignition/common.hh> //Common
#include <ignition/common/MeshManager.hh> //Mesh Manager
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <iostream>
#include <string>

bool ConvertAssimp2Gazebo(const aiScene* scene)
{
  std::cout<<"Number of meshes loaded is: " << scene->mNumMeshes << "." << std::endl;
  return true;
  // Generate an instance of MeshManager

  // Generate an instance of 
}

bool FileExists(std::string myfile)
{
  bool file_exist = false;
  std::ifstream file(myfile.c_str());
  if (file)
  {
    file_exist = true;
  }
  return file_exist;
}


bool Read( const std::string& pFile) 
{
  // Create an instance of the Importer class
  Assimp::Importer importer;

  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll
  // probably to request more postprocessing than we do in this example.
  const aiScene* scene = importer.ReadFile( pFile,
    aiProcess_CalcTangentSpace       |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType);


  // If the import failed, report it
  if (nullptr == scene) {
    return false;
  }

  std::cout << "Succesfully loaded the scene." << std::endl ;

  // Now we can access the file's contents.
  ConvertAssimp2Gazebo(scene);

  // We're done. Everything will be cleaned up by the importer destructor
  return true;
}

int main() {
    std::string file_path = "/home/otore19/Desktop/projects/assimp_analysis/step2/mesh_files/animated_cube/AnimatedCube.gltf";
    if (FileExists(file_path))
    {
      std::cout << "Mesh file exists." << std::endl;
      Read(file_path);
    }
}