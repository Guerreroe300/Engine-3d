#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//Funcion para manejar el resize
void processInput(GLFWwindow* window); //PRocesa los inputs, va en render loop


int main(void)
{
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width, height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}