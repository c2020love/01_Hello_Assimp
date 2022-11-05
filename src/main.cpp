#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Tool/Shader.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Tool/Camera.h>
#include <string>
#include<Tool/mesh.h>
#include<Tool/model.h>
#define STB_IMAGE_IMPLEMENTATION
#include <Tool/stb_image.h>
void frambuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);        // xpos,ypos 为鼠标当前的位置
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset); // xoffset 与yoffset为当前帧和上一帧的偏移量
void processInput(GLFWwindow *window);
unsigned int loadTexture(char *str);

GLFWwindow *viewportInit();

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; //  上一帧的时间
bool firstMouse = true;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

const float SWIDTH = 800.0f;
const float SHEIGHT = 600.0f;

float lastX = SWIDTH / 2.0f; // 鼠标上一帧的位置
float lastY = SHEIGHT / 2.0f;

float fov = 45.0f; //视角极限
glm::vec3 lightPos(2.0f , 10.0f , 10.0f);

using namespace std;
int main()
{
    GLFWwindow *window = viewportInit();
    //@定义顶点数组，添加颜

    Shader modelShader("D:\\opengl\\code\\AssimpCode\\01_Hello_Assimp\\src\\shader\\cubevertex.glsl", "D:\\opengl\\code\\AssimpCode\\01_Hello_Assimp\\src\\shader\\cubefragement.glsl");
    Shader lightShader("D:\\opengl\\code\\AssimpCode\\01_Hello_Assimp\\src\\shader\\lightvetex.glsl" , "D:\\opengl\\code\\AssimpCode\\01_Hello_Assimp\\src\\shader\\lightfragment.glsl");
    Model ourModel("D:\\opengl\\code\\AssimpCode\\01_Hello_Assimp\\src\\sources\\obj\\nanosuit.obj");
    
    
    float vertices1[] = {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
       };


    unsigned int VBO , lightVAO;
    glGenBuffers(1 , &VBO);
    glGenVertexArrays(1 , &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER , VBO);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices1), vertices1, GL_STATIC_DRAW); 
    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 6*sizeof(float) , (void*)0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    while (!glfwWindowShouldClose(window)) //检查用户是否需要退出
    {

        //在每一帧中我们计算出新的deltaTime以备后用。
        float iTime = glfwGetTime();
        deltaTime = lastFrame - iTime;
        lastFrame = iTime;
        //输入
        processInput(window);
        //渲染指令
        glm::vec3 dir = glm::vec3(1.0f);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);                       //清除颜色缓冲，其他的还有深度缓冲盒模板缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除Z-Buffer缓冲
        lightPos.x = sin(iTime) * 5.0f;
        lightPos.y = cos(iTime) * 10.0f;
        modelShader.use();
        modelShader.setVec3("light.direction",-lightPos);
        modelShader.setVec3("viewPos", camera.Position);
        modelShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        modelShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
        modelShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        modelShader.setFloat("light.constant" , 1.0f);

        


        glm::mat4 project = glm::mat4(1.0f);
        project = glm::perspective(glm::radians(camera.Fov), (float)SWIDTH / (float)SHEIGHT, 0.1f, 100.0f);
        modelShader.setMat4("project", project);

        glm::mat4 view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        modelShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        
        model = glm::translate(model , glm::vec3(0.0f , 0.0f , 0.0f));
        model = glm::scale(model , glm::vec3(1.0f , 1.0f , 1.0f));
        modelShader.setMat4("model", model);

        ourModel.Draw(modelShader);

        lightShader.use();
        lightShader.setMat4("project", project);
        lightShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(1.0f)); // a smaller cube
        lightShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //检查并调用事件，交换缓冲
        glfwSwapBuffers(window); //对这个窗口进行一个颜色的双缓冲，避免单缓冲造成照片闪烁
        glfwPollEvents();        //监听窗口是否发生事件，若发生，则会调用相应的回调函数
    }
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1 , &lightVAO);
    //@结束渲染
    glfwTerminate();
    return 0;
}

//回调函数
//用户调整窗口大小时，会调整视口，这个函数就可以重新调整视口大小为需要的大小
void frambuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//输入的回调函数
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) //如果按下SPACE，退出渲染
        glfwSetWindowShouldClose(window, true);           //给ShouleCLose传true值，并在渲染循环中更新
    float cameraSpeed = 10.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Backward,cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Forward,cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Right, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Left, cameraSpeed);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false; // reversed since y-coordinates go from bottom to top
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char *str)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(str, &width, &height, &nrChannels, 0);
    std::cout << width << " " << height << " " << nrChannels << " " << std::endl;
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
        {
            format = GL_RED;
        }
        else if (nrChannels == 3)
        {
            format = GL_RGB;
        }
        else if (nrChannels == 4)
        {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, texture);
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
        std::cout << "Fail to load" << std::endl;
        stbi_image_free(data);
    }

    return texture;
}

GLFWwindow *viewportInit()
{
    glfwInit();                                    //初始化
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //设置主要版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //设置次要版本

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置OpenGL模式为核心模式

    //@创建窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Shader", NULL, NULL); //创建窗口宽高，名字
    if (window == NULL)                                                          //如果未创建成功，则打印失败，结束窗口并返回
    {
        std::cout << "Fail" << std::endl;
        glfwTerminate();
        return window;
    }

    //创建各种摄像机回调函数的对象
    glfwMakeContextCurrent(window); //创建成功，得到一个窗口对象
    glfwSetFramebufferSizeCallback(window, frambuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //@初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //由于glad管理OpenGL函数指针，使用使用前都需要初始化一遍
    {
        std::cout << "Fail to init GLAD" << std::endl; //如果初始化失败，就打印并退出
        return window;
    }

    //@调整视口大小,这样OpenGL才只能知道怎样将位置坐标转化为屏幕坐标
    glViewport(0, 0, 800, 600); //调整窗口维度
    //前面两个参数表示的是窗口左下角的位置，后两个是宽和高

    glEnable(GL_PROGRAM_POINT_SIZE);
    //@注册窗口监听函数，当窗口大小发生变换时，会调用这个函数，也就调用回调函数
    glfwSetFramebufferSizeCallback(window, frambuffer_size_callback);

    glEnable(GL_DEPTH_TEST); // Z-Buffer缓冲

    return window;
}