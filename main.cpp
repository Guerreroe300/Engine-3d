#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//Funcion para manejar el resize
void processInput(GLFWwindow* window); //PRocesa los inputs, va en render loop

//REAally simple basic vertex shader
    const char *vertexShaderSource = "#version 330 core\n" 
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" 
    "}\0";
//------------------------

//REAally simple basic fragment shader
    const char *fragmentShaderSource = "#version 330 core\n" 
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" 
    "}\0";
//------------------------

int main(void)
{   
    // Initialize opengl -----------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //opengl version max
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //opengl version minimum
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use the core version
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MAC compatibility


    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL); //WIndow object

    if (window == NULL){
        std::cout << "No se creo bien la window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); //hacemos la window el object actual

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){ //Iniciamos glad dandole el espacio en memria de las funciones
        std::cout << "Failed to initializa GLAD\n";
        return -1;
    }

    glViewport(0,0,800,600); //PAra ver lo que rederizemos?
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//decirle a opengl que use my funcion de resize cuando suceda
    //-------------------------------------------------------------------------------------------

    //doin a triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    }; //vertices for a triangle

    unsigned int VBO; //Id for vertrx buffer object
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //SAY that that when we modify and array buffer itll be that on

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    //create a vertex shader thatll handle the previous shader, souce code at the tops
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //bind source to shader
    glCompileShader(vertexShader); //tell it to use that one

    //CHECK FOR ERROR IN SHADERS----------------------
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //vertex shader end

    //fragmentsshder
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //bind source to shader
    glCompileShader(fragmentShader); //tell it to use that one

    //CHECK FOR ERROR IN SHADERS----------------------
    int success0;
    char infoLog2[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success0);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2); std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //fragmentshader end

    //Linkin both shaders into an shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success1;
    char infoLog3[512];
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success1);

    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog3); std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram); //Actually using it
    //Shader program end

    glDeleteShader(vertexShader); // we delete the shaders since now that they linked theyr not needed
    glDeleteShader(fragmentShader);


    //tell opengl how to interpret vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //VAO gets all the atributes for an object bunched up for ease of use?

    //VAO end

    // triangle end
    while(!glfwWindowShouldClose(window)) //Render LOOP
    {
        //Check key presses
        processInput(window);

        //Render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Usa este color cuando cleareas el buffer
        glClear(GL_COLOR_BUFFER_BIT); //clerea el cuffer de color

        //Check call event and swap buffer
        glfwSwapBuffers(window); //Poner lo del buffer 2d que indica los colores de los pixeles
        glfwPollEvents(); //keyboard y ouse nput y eso
    }

    glfwTerminate();
    return 0;
}



//Function definitions --------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width, height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

/* Interesting resource from the book
/ 0. copy our vertices array in a buffer for OpenGL to use
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 1. then set the vertex attributes pointers
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
// 2. use our shader program when we want to render an object
        glUseProgram(shaderProgram);
// 3. now draw the object
        someOpenGLFunctionThatDrawsOurTriangle();
*/