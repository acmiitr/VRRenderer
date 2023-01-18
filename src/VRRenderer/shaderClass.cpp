#include <VRRenderer/shaderClass.h>

std::string get_file_content(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
   throw (errno);
}

// Shader constructor
Shader::Shader(const char *vertexFile, const char *fragFile)
{
	// std::string vertexCode = get_file_content(vertexFile);
	// std::string fragCode = get_file_content(fragFile);
//****************************************************************
   // 1. retrieve the vertex/fragment source code from filePath
   std::string vertexCode;
   std::string fragmentCode;
   std::ifstream vShaderFile;
   std::ifstream fShaderFile;
   // ensure ifstream objects can throw exceptions:
   vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
   fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
   try
   {
		// open files
		vShaderFile.open(vertexFile);
		fShaderFile.open(fragFile);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
   }
   catch (std::ifstream::failure &e)
   {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
   }

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	// link shaders to shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}
// Reading the shader files