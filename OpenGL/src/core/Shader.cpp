#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../debug/GLCall.h"

namespace Engine {

	Shader::Shader(const std::string& filepath) :sFilePath(filepath), n_RenderID(0) {
		ShaderProgrammSource source = ParseShader(filepath);
		n_RenderID = CreateShader(source.VertexSource, source.FragmentSource);
	}
	Shader::~Shader() {
		GLCall(glDeleteProgram(n_RenderID));
	}


	ShaderProgrammSource Shader::ParseShader(const std::string& filepath) {
		std::ifstream stream(filepath);
		enum class ShaderType {
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1
		};

		std::string sLine;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, sLine)) {
			if (sLine.find("#shader") != std::string::npos) {
				if (sLine.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (sLine.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else {
				ss[(int)type] << sLine << "\n";
			}
		}

		return{ ss[0].str(),ss[1].str() };
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
		GLCall(unsigned int id = glCreateShader(type));
		const char* src = source.c_str();
		GLCall(glShaderSource(id, 1, &src, nullptr));
		GLCall(glCompileShader(id));

		int iResult;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &iResult));
		if (iResult == GL_FALSE) {
			int iLength;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &iLength));
			char* message = (char*)alloca(iLength * sizeof(char));
			GLCall(glGetShaderInfoLog(id, iLength, &iLength, message));
			std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
			std::cout << message << std::endl;
			GLCall(glDeleteShader(id));
			return 0;
		}

		return id;
	}

	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
		GLCall(unsigned int program = glCreateProgram());
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		GLCall(glAttachShader(program, vs));
		GLCall(glAttachShader(program, fs));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

		return program;
	}

	void Shader::Bind() const {
		GLCall(glUseProgram(n_RenderID));
	}
	void Shader::Unbind() const {
		GLCall(glUseProgram(0));
	}

	void Shader::SetUniform1i(const std::string& name, int value) {
		GLCall(glUniform1i(GetUniformLocation(name), value));
	}

	void Shader::SetUniform1iv(const std::string& name, int count, int* sampler) {
		GLCall(glUniform1iv(GetUniformLocation(name), count, sampler));
	}

	void Shader::SetUniform1f(const std::string& name, float value) {
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
		GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	}

	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}

	int Shader::GetUniformLocation(const std::string& name) {
		if (n_UniformLocationCache.find(name) != n_UniformLocationCache.end())
			return n_UniformLocationCache[name];

		GLCall(int location = glGetUniformLocation(n_RenderID, name.c_str()));

		if (location == -1)
			std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

		n_UniformLocationCache[name] = location;

		return location;
	}
}