/*
Mostly taken from learnopengl.com/Model-loading/Model
*/


#include <ignition/common.hh> //Common
#include <ignition/common/MeshManager.hh> //Mesh Manager

#include <ignition/common/Mesh.hh> // Mesh
#include <ignition/common/SubMesh.hh> // Submesh
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags




using namespace ignition;
using namespace common;

class Assimp2Gazebo
{
  public:

    Assimp2Gazebo(const std::string& path)
    {
      Mesh *mesh = new Mesh();
      std::unique_ptr<SubMesh> subMesh(new SubMesh()); //Another way of initialization.
      LoadModel(path);
    }

  private:

    SubMesh * assimp2GazeboMesh(aiMesh * mesh, SubMesh * gazeboMesh)
    {
       return gazeboMesh;
    }

    void processNode(aiNode * node, const aiScene *scene, SubMesh * gazeboMesh)
    {
      // process all the node's meshes (if any)
      for(unsigned int i = 0; i < node->mNumMeshes; i++)
      {
          aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
          assimp2GazeboMesh(mesh, gazeboMesh);
      }
      // then do the same for each of its children
      for(unsigned int i = 0; i < node->mNumChildren; i++)
      {

          std::unique_ptr<SubMesh> gazeboSubMesh(new SubMesh()); //Another way of initialization.
          processNode(node->mChildren[i], scene, gazeboSubMesh);
          gazeboMesh->AddSubMesh(std::move(gazeboSubMesh))
      }
      return;
    }

    void LoadModel( const std::string& pFile)
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


      if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
      {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
      }

      std::cout << "Succesfully loaded the scene." << std::endl ;

      processNode(scene->mRootNode, scene, this->subMesh);
      this->mesh->AddSubMesh(std::move(this->subMesh))
      // We're done. Everything will be cleaned up by the importer destructor
      return;
    }
};

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



int main() {

  std::string file_path = "/home/otore19/Desktop/projects/assimp_analysis/step2/mesh_files/animated_cube/AnimatedCube.gltf";
  if (FileExists(file_path))
  {
    std::cout << "Mesh file exists." << std::endl;
    Assimp2Gazebo Assimp2Gazebo(file_path);

  }
}