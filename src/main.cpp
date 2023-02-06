#include "Window.h"
#include "Events.h"
#include "OpenGL.h"
#include "Camera.h"

void drawGrid(Camera* camera, Shader* shader, VertexArray* vao, VertexBuffer* vbo)
{
    glm::mat4 cameraTransform = camera->GetPerspectiveMatrix() * camera->GetLookAtMatrix();
    
    vao->Bind();
    vbo->Bind();
    shader->Use();

    glm::vec3 center = camera->GetPosition();
    center.x = floor(center.x);
    center.z = floor(center.z);

    for (int i = -150; i <= 150; i++)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(center.x + i, 0.0f, center.z + i));
        glm::mat4 transform = cameraTransform * model;
        shader->UniformMat4f("uTransform", transform);

        glDrawArrays(GL_LINES, 0, 4);
    }
}

int main()
{
    Events::Init();
    Window::Init("best graphics engine", 1280, 840, glm::vec3(0.3f, 0.3f, 0.3f));
    
    Shader* lineShader = load_shader("res/line.vertex", "res/line.fragment");

    float gridVertices[] = {
        0.0f, 0.0f, -1000.0f,
        0.0f, 0.0f, 1000.0f,
        -1000.0f, 0.0f, 0.0f,
        1000.0f, 0.0f, 0.0f
    };

    VertexArray* gridVao = new VertexArray();
    gridVao->Bind();
    VertexBuffer* gridVbo = new VertexBuffer(Type::LINES, gridVertices, sizeof(gridVertices));
    gridVbo->Bind();

    float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    Camera* camera = new Camera();

    Texture* crateTexture = new Texture("res/container.png");
    Texture* crateSpecularTexture = new Texture("res/container_specular.png");
    Shader* cubeShader = load_shader("res/basic.vertex", "res/basic.fragment");
    cubeShader->Use();
    cubeShader->UniformVec3f("uLight.ambient", glm::vec3(0.4f, 0.4f, 0.4f));
    cubeShader->UniformVec3f("uLight.diffuse", glm::vec3(0.7f, 0.7f, 0.7f));
    cubeShader->UniformVec3f("uLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    cubeShader->UniformFloat("uLight.constant", 1.0f);
    cubeShader->UniformFloat("uLight.linear", 0.0014);
    cubeShader->UniformFloat("uLight.quadratic", 0.000007);
    cubeShader->UniformFloat("uLight.innerCutoff", glm::cos(glm::radians(12.5f)));
    cubeShader->UniformFloat("uLight.outerCutoff", glm::cos(glm::radians(15.0f)));

    crateTexture->Bind();
    cubeShader->UniformInt("uMaterial.diffuse", crateTexture->GetTextureNumber());
    crateSpecularTexture->Bind();
    cubeShader->UniformInt("uMaterial.specular", crateSpecularTexture->GetTextureNumber());
    cubeShader->UniformFloat("uMaterial.shininess", 35.0f);

    glm::vec3 cubePos = glm::vec3(1.0f, 1.0f, -5.0f);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePos);

    VertexArray* cubeVao = new VertexArray();
    cubeVao->Bind();
    VertexBuffer* cubeVbo = new VertexBuffer(Type::MESH, cubeVertices, sizeof(cubeVertices));
    cubeVbo->Bind();

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    while (Window::Opened())
    {
        Window::Clear();

        if (Events::GetMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            glfwSetInputMode(Window::Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            camera->EnableRotation();
        }
        else if (Events::GetMouseButtonUp(MOUSE_BUTTON_RIGHT))
        {
            glfwSetInputMode(Window::Get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            camera->DisableRotation();
        }

        if (Events::GetKeyDown(KEY_ESCAPE))
            Window::Close();

        camera->Rotate();
        camera->Move();
        
        glEnable(GL_DEPTH_TEST);
        drawGrid(camera, lineShader, gridVao, gridVbo);

        cubeVao->Bind();
        cubeVbo->Bind();

        cubeShader->Use();
        cubeShader->UniformVec3f("uLight.position", camera->GetPosition());
        cubeShader->UniformVec3f("uLight.direction", camera->GetFront());
        cubeShader->UniformVec3f("uViewPosition", camera->GetPosition());
        cubeShader->UniformMat4f("uModel", model);
        cubeShader->UniformMat4f("uView", camera->GetLookAtMatrix());
        cubeShader->UniformMat4f("uPerspective", camera->GetPerspectiveMatrix());

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisable(GL_DEPTH_TEST);

        Events::OnUpdate();
        Window::OnUpdate();
    }
 
    delete cubeVbo;
    delete cubeVao;
    delete camera;
    delete crateTexture;
    delete cubeShader;  
    delete lineShader;
    delete gridVbo;
    delete gridVao;

    glfwTerminate();
}

