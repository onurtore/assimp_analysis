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
    Mesh *mesh = new Mesh();

    Assimp2Gazebo(const std::string& path)
    {
      LoadModel(path);
    }

  private:

    void assimp2GazeboMesh(aiMesh * mesh, SubMesh& gazeboMesh)
    {
      // Retrieve all the vertex data;
      for(unsigned int i = 0; i < mesh->mNumVertices; i++)
      {
        //Process vertex positions
        ignition::math::Vector3d vertex;
        vertex.X(mesh->mVertices[i].x);
        vertex.Y(mesh->mVertices[i].y);
        vertex.Z(mesh->mVertices[i].z);

        //Process vertex normals
        ignition::math::Vector3d normal;
        normal.X(mesh->mNormals[i].x);
        normal.Y(mesh->mNormals[i].y);
        normal.Z(mesh->mNormals[i].z);

        //Process texture coordinates
          //TO-DO: Implement this later...

        gazeboMesh.AddVertex(vertex);
        gazeboMesh.AddNormal(normal);
      }

      // Retrieve all the mesh's indices
      for(unsigned int i = 0; i < mesh->mNumFaces; i++)
      {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
          gazeboMesh.AddIndex(face.mIndices[j]);
      }
      // Retrieve material data
        //TO-DO: Implement this later...
    }

    void processNode(aiNode * node, const aiScene *scene)
    {
      // process all the node's meshes (if any)

      for(unsigned int i = 0; i < node->mNumMeshes; i++)
      {
          SubMesh subMesh;
          aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
          assimp2GazeboMesh(mesh, subMesh);
          this->mesh->AddSubMesh(subMesh);

      }
      // then do the same for each of its children
      for(unsigned int i = 0; i < node->mNumChildren; i++)
      {
          processNode(node->mChildren[i], scene);
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

      processNode(scene->mRootNode, scene);
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