#include "../headers/Mesh.h"

const int width = 1920;
const int height = 1080;

Vertex vertices[] =
        { //               COORDINATES           /            COLORS          /           TexCoord         /       NORMALS         //
                Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
                Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
                Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
                Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
        };

GLuint indices[] =
        {
                0, 1, 2,
                0, 2, 3
        };

Vertex lightVertices[] = {
        Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
        Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
        Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
        {
                0, 1, 2,
                0, 2, 3,
                0, 4, 7,
                0, 7, 3,
                3, 7, 6,
                3, 6, 2,
                2, 6, 5,
                2, 5, 1,
                1, 5, 4,
                1, 4, 0,
                4, 5, 6,
                4, 6, 7
        };

int main(){

    // Opening the window part ---------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(width, height, "Renderer", nullptr, nullptr);
    if(window==nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, width, height);

    //----------------------------------------------------------------------------------
    // Texture -------------------------------------------------------------------------
    Texture textures[]
            {
                    Texture("../resources/Textures/meme_cat.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
            };

    //----------------------------------------------------------------------------------
    // link shaders to shader program
    Shader shaderProgram("../resources/default.vert", "../resources/default.frag");
    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));


    GLint scaleID = glGetUniformLocation(shaderProgram.ID, "scale");
    // Create floor mesh
    Mesh floor(verts, ind, tex);

    // Light Data-----------------------------------------------------------------------
    Shader lightShader("../resources/light.vert", "../resources/light.frag");
    std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

    // Crate light mesh
    Mesh light(lightVerts, lightInd, tex);
    // --------------------------------------------------------------------------------

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3 (0.0f, 1.3f, 0.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 objPos = glm::vec3 (0.0f, 0.0f, 0.0f);
    glm::mat4 objModel = glm::mat4 (1.0f);
    objModel = glm::translate(objModel, objPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



    // Fix for the Texture glitch
    glEnable(GL_DEPTH_TEST);

    // --------------------------------------------------------------------------------
    // Camera--------------------------------------------------------------------------
    // create the Camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.5f, 2.5f));
    float fov = 85.0f;
    // Scrolling Callback (todo: to be implemented)
    glfwSetScrollCallback(window, Camera::ScrollCallback);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera Handling
        camera.KeyInputs(window);
        camera.MouseInputs(window);
        camera.UpdateMatrix(fov, 0.1f, 100.0f);

        // Scaling the geometry
        glUniform1f(scaleID, 0.5);

        // Draws different meshes
        floor.Draw(shaderProgram, camera);
        light.Draw(lightShader, camera);

        // Swap back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events (resize, refreshing, etc)
        glfwPollEvents();
    }

    shaderProgram.Delete();
    lightShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}