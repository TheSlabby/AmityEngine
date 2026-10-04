#include "Shader.hpp"
#include "Log.hpp"
#include <vector>

namespace Core {

Shader::Shader() {
	
}

Shader::~Shader() {
	if (ID != 0) {
		glDeleteProgram(ID);
	}
}

Shader::Shader(Shader&& other) noexcept : ID(other.ID) {
	other.ID = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
	if (this != &other) {
		if (ID != 0) {
			glDeleteProgram(ID);
		}
		ID = other.ID;
		other.ID = 0;
	}
	return *this;
}

void Shader::setShader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (const std::ifstream::failure&) {
		Log::render().error("Failed to read shader files '{}' / '{}'", vertexPath, fragmentPath);
	}

	// Prevent segmentation faults in headless environments (like unit tests running without an OpenGL context)
	if (glCreateShader == nullptr) {
		Log::render().debug("No OpenGL context, skipping shader compilation for '{}' / '{}'", vertexPath, fragmentPath);
		return;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//next, compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	//vertex
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//vertex errors
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		Log::render().error("Vertex shader '{}' failed to compile:\n{}", vertexPath, infoLog);
	}

	//fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//fragment compile errors
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		Log::render().error("Fragment shader '{}' failed to compile:\n{}", fragmentPath, infoLog);
	}

	//setup shader program
	if (ID != 0) glDeleteProgram(ID);
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//shader program linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		Log::render().error("Shader program '{}' + '{}' failed to link:\n{}", vertexPath, fragmentPath, infoLog);
	}

	//cleanup
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}



//enable this shader
void Shader::use() const {
	glUseProgram(ID);
}

//uniform set functions
void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setMat3(const std::string& name, glm::mat3 value) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setVec2(const std::string& name, glm::vec2 value) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec3(const std::string& name, glm::vec3 value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec4(const std::string& name, glm::vec4 value) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

} // Core namespace