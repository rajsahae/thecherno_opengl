// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

#define ASSERT(x) if (!(x)) assert(false)

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError()
{
    while (GLenum error = glGetError())
    {
        
        std::cout << "[OpenGL Error] ";
          switch(error) {
              case GL_INVALID_ENUM :
                  std::cout << "GL_INVALID_ENUM : An unacceptable value is specified for an enumerated argument.";
                  break;
              case GL_INVALID_VALUE :
                  std::cout << "GL_INVALID_OPERATION : A numeric argument is out of range.";
                  break;
              case GL_INVALID_OPERATION :
                  std::cout << "GL_INVALID_OPERATION : The specified operation is not allowed in the current state.";
                  break;
              case GL_INVALID_FRAMEBUFFER_OPERATION :
                  std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION : The framebuffer object is not complete.";
                  break;
              case GL_OUT_OF_MEMORY :
                  std::cout << "GL_OUT_OF_MEMORY : There is not enough memory left to execute the command.";
                  break;
              case GL_STACK_UNDERFLOW :
                  std::cout << "GL_STACK_UNDERFLOW : An attempt has been made to perform an operation that would cause an internal stack to underflow.";
                  break;
              case GL_STACK_OVERFLOW :
                  std::cout << "GL_STACK_OVERFLOW : An attempt has been made to perform an operation that would cause an internal stack to overflow.";
                  break;
              default :
                  std::cout << "Unrecognized error" << error;
          }
          std::cout << std::endl;
          return false;
    }
    return true;
}

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static struct ShaderProgramSource ParseShader(const std::string& filepath)
{
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    GLCall( unsigned int id = glCreateShader(type) );
    const char* src = source.c_str();
    GLCall( glShaderSource(id, 1, &src, nullptr) );
    GLCall( glCompileShader(id) );

    // Error handling
    int result;
    GLCall( glGetShaderiv(id, GL_COMPILE_STATUS, &result) );
    std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader compile status: " << result << std::endl;
    if ( result == GL_FALSE )
    {
        int length;
        GLCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length) );
        char* message = (char*) alloca(length * sizeof(char));
        GLCall( glGetShaderInfoLog(id, length, &length, message) );
        std::cout 
            << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << "shader"
            << std::endl;
        std::cout << message << std::endl;
        GLCall( glDeleteShader(id) );
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // create a shader program
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall( glAttachShader(program, vs) );
    GLCall( glAttachShader(program, fs) );

    GLCall( glLinkProgram(program) );

    GLint program_linked;

    GLCall( glGetProgramiv(program, GL_LINK_STATUS, &program_linked) );
    std::cout << "Program link status: " << program_linked << std::endl;
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        GLCall( glGetProgramInfoLog(program, 1024, &log_length, message) );
        std::cout << "Failed to link program" << std::endl;
        std::cout << message << std::endl;
    }

    GLCall( glValidateProgram(program) );

    GLCall( glDeleteShader(vs) );
    GLCall( glDeleteShader(fs) );

    return program;
}

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
        GLFWwindow* window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

        std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        float positions[] = {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f,  0.5f, // 2
            -0.5f,  0.5f  // 3
        };

        unsigned int indices[] = {
          0, 1, 2,
          2, 3, 0
        };

        // Have to set VAO before binding attrbutes
	unsigned int vao;
	GLCall( glGenVertexArrays(1, &vao) );
	GLCall( glBindVertexArray(vao) );

        // Create vertex buffer and copy data
        unsigned int buffer;
        GLCall( glGenBuffers(1, &buffer) );
        GLCall( glBindBuffer(GL_ARRAY_BUFFER, buffer) );
        GLCall( glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW) );

        // define vertex layout
        // This links the attrib pointer wih the buffer at index 0 in the vertex array object
        GLCall( glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0) );
        GLCall( glEnableVertexAttribArray(0) );

        // Create index buffer
        unsigned int ibo;
        GLCall( glGenBuffers(1, &ibo) );
        GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo) );
        GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW) );

        ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

        std::cout << "VERTEX" << std::endl << source.VertexSource << std::endl;
        std::cout << "FRAGMENT" << std::endl << source.FragmentSource << std::endl;

        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        GLCall( glUseProgram(shader) );

        GLCall( unsigned int u_Color = glGetUniformLocation(shader, "u_Color") );
        ASSERT(u_Color != -1);

        float red = 0.0f;
        float step = 0.05f;

        GLCall( glUseProgram(0) );
        GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
        GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
        GLCall( glBindVertexArray(0) );

	do{
		// Clear the screen
		GLCall( glClear( GL_COLOR_BUFFER_BIT );

                // set shader and set uniform color
                GLCall( glUseProgram(shader) );
                GLCall( glUniform4f(u_Color, red, 0.3, 0.8, 1.0) );

                // Bind vertex buffer and attribute layout
                // GLCall( glBindBuffer(GL_ARRAY_BUFFER, buffer) );
                // GLCall( glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0) );
                // GLCall( glEnableVertexAttribArray(0) );

                // Instead of binding vertex buffer, attrib pointer, just bind Vertex Array Object
                GLCall( glBindVertexArray(vao) );

                // Bind index buffer
                GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo) );

		// Draw
		GLCall( glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)) );

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

                // increment red
                if (red < 0.0f || red > 1.0f)
                    step *= -1.0;
                red += step;

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	GLCall( glDeleteBuffers(1, &buffer) );
	GLCall( glDeleteVertexArrays(1, &vao) );
	GLCall( glDeleteProgram(shader) );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

