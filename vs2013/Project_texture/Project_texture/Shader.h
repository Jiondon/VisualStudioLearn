
#include <glad\glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

	//���첢��ȡ��ɫ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		//��֤ifstream��������׳��쳣
		vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		try{
			//���ļ�
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			//��ȡ�ļ��Ļ������ݵ���������
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			//�ر��ļ�������
			vShaderFile.close();
			fShaderFile.close();

			//ת����������string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e){
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//������ɫ��
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		//������ɫ��
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR" << infoLog << std::endl;
		}

		//Ƭ����ɫ��
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR" << infoLog << std::endl;
		}

		//��ɫ������
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);

		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success){
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR:" << infoLog << std::endl;
		}

		//ɾ����ɫ���� ��ɫ���Ѿ����ӵ��������ˣ��Ѿ�������Ҫ��
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	//�������
	void use(){
		glUseProgram(ID);
	}
	//uniform���ߺ���
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}


	//����id
	unsigned int ID;
};