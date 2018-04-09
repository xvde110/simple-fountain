#include "stdafx.h"
#include "shader.h"

#include <fstream>  
#include <sstream>  

//���ַ�����������ɫ������  
GLuint Shader::createShader(GLenum eShaderType, const std::string &strShaderFile)
{
	GLuint shader = glCreateShader(eShaderType);//�������ʹ���shader���������Ƭ����ɫ��  
	const char * strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);//��shader�ַ���, count��shader����θ������������Ӷ�������  
	glCompileShader(shader);//����shader,�õ���̬�Ļ��ָ��󶨵�shader��ʾ����ַ  
							//���shader״̬  
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		const char * strShaderType = NULL;
		switch (eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}
		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}
	return shader;
}
//���ļ�������ɫ������  
GLuint Shader::createShader(GLenum eShaderType, const char* fileName)
{
	std::ifstream infile(fileName);
	if (!infile)
	{
		fprintf(stderr, "Could not open file : %s for reading.", fileName);
		return 0;
	}
	std::stringstream  buffer;
	buffer << infile.rdbuf();
	infile.close();
	return Shader::createShader(eShaderType, buffer.str());
}
//������ɫ���������  
GLuint Shader::createProgram(const std::vector<GLuint> &shaderList)
{
	GLuint programId = glCreateProgram();//����program  
	for (std::vector<GLuint>::size_type iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(programId, shaderList[iLoop]);//��shader,һ����ɫ��������԰󶨶����ɫ������  

	glLinkProgram(programId);//����shader���õ������еĻ�����  
							 //���program״̬������д����ӡ������Ϣ  
	GLint status;
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(programId, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	/*for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
	glDetachShader(programId, shaderList[iLoop]);*/
	return programId;
}