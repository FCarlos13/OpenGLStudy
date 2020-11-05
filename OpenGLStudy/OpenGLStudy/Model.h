#pragma once
#ifndef MODEL_H
#define MODEL_H

#include"glheader.h"
#include "Mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
public:
	/*  函数   */
	Model(string const &path, bool gamma = false) : gammaCorrection(gamma) { loadModel(path); }
	void Draw(Shader shader);
private:
	/*  模型数据  */
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	/*  函数   */
	void loadModel(string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);
};

void Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}

void Model::loadModel(string const &path)
{
	//导入模型数据，readfile第二个参数为导入模型时的一些设置
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));//保存文件路径 方便后面使用

	processNode(scene->mRootNode, scene); //迭代处理子节点
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
	// 处理节点所有的网格（如果有的话）
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// 接下来对它的子节点重复这一过程
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

 Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	 vector<Vertex> vertices;
	 vector<unsigned int> indices;
	 vector<Texture> textures;

	 // 处理顶点位置、法线和纹理坐标
	 for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	 {
		 Vertex vertex;
		 glm::vec3 vector;
		 vector.x = mesh->mVertices[i].x;
		 vector.y = mesh->mVertices[i].y;
		 vector.z = mesh->mVertices[i].z;
		 vertex.Position = vector;
		 
		 if (mesh->HasNormals())
		 {
			 vector.x = mesh->mNormals[i].x;
			 vector.y = mesh->mNormals[i].y;
			 vector.z = mesh->mNormals[i].z;
			 vertex.Normal = vector;
		 }

		 if (mesh->mTextureCoords[0])
		 {
			 glm::vec2 vec;
			 // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			 // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			 vec.x = mesh->mTextureCoords[0][i].x;
			 vec.y = mesh->mTextureCoords[0][i].y;
			 vertex.TexCoords = vec;
		 }
		 else
			 vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		 vertices.push_back(vertex);
	 }

	 // 处理索引
	 for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	 {
		 aiFace face = mesh->mFaces[i];
		 // retrieve all indices of the face and store them in the indices vector
		 for (unsigned int j = 0; j < face.mNumIndices; j++)
			 indices.push_back(face.mIndices[j]);
	 }

	// 处理材质
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// 1. diffuse maps
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	}
	 return Mesh(vertices, indices, textures);
}

 //loadMaterialTextures函数遍历了给定纹理类型的所有纹理位置，获取了纹理的文件位置，并加载并和生成了纹理
vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
 {
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
 }

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
	string filename = string(path);
	filename = directory + "\\" + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

#endif // !MODEL_H



