#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

GLfloat camX = 0.0f, camY = 0.0f, camZ = 50.0f;
GLfloat angleY = 0.0f;
GLfloat angleX = 0.0f;
GLfloat distance = 50.0f;

struct Vertex { float x, y, z; };
struct Normal { float nx, ny, nz; };
struct TextureCoord { float u, v; };
struct Face {
    std::vector<int> vertexIndices, textureIndices, normalIndices;
};

std::vector<Vertex> vertices;
std::vector<Normal> normals;
std::vector<TextureCoord> textureCoords;
std::vector<Face> faces;
Vertex modelCenter = { 0.0f, 0.0f, 0.0f };

bool loadOBJ(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) { std::cerr << "Failed to open file: " << filename << std::endl; return false; }

    vertices.clear(); normals.clear(); textureCoords.clear(); faces.clear();
    std::string line; float minX = 1e6, minY = 1e6, minZ = 1e6, maxX = -1e6, maxY = -1e6, maxZ = -1e6;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);

            minX = std::min(minX, vertex.x); minY = std::min(minY, vertex.y); minZ = std::min(minZ, vertex.z);
            maxX = std::max(maxX, vertex.x); maxY = std::max(maxY, vertex.y); maxZ = std::max(maxZ, vertex.z);
        }
        else if (prefix == "vn") {
            Normal normal;
            iss >> normal.nx >> normal.ny >> normal.nz;
            normals.push_back(normal);
        }
        else if (prefix == "vt") {
            TextureCoord texCoord;
            iss >> texCoord.u >> texCoord.v;
            textureCoords.push_back(texCoord);
        }
        else if (prefix == "f") {
            Face face;
            std::string vertexData;
            while (iss >> vertexData) {
                std::istringstream viss(vertexData);
                std::string index;
                int vertexIndex, textureIndex = 0, normalIndex = 0;

                std::getline(viss, index, '/');
                vertexIndex = std::stoi(index);
                face.vertexIndices.push_back(vertexIndex);

                if (std::getline(viss, index, '/')) {
                    if (!index.empty()) { textureIndex = std::stoi(index); face.textureIndices.push_back(textureIndex); }
                    if (std::getline(viss, index, '/')) { normalIndex = std::stoi(index); face.normalIndices.push_back(normalIndex); }
                }
            }
            faces.push_back(face);
        }
    }

    file.close();
    modelCenter.x = (minX + maxX) / 2.0f;
    modelCenter.y = (minY + maxY) / 2.0f;
    modelCenter.z = (minZ + maxZ) / 2.0f;

    return true;
}

void updateCameraPosition() {
    camX = modelCenter.x + distance * sin(glm::radians(angleY)) * cos(glm::radians(angleX));
    camY = modelCenter.y + distance * sin(glm::radians(angleX));
    camZ = modelCenter.z + distance * cos(glm::radians(angleY)) * cos(glm::radians(angleX));
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        distance -= 1.0f;  // Acercar
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        distance += 1.0f;  // Alejar
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        angleY -= 5.0f;  // Rotar izquierda
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        angleY += 5.0f;  // Rotar derecha
    }
}

void drawFace(const Face& face) {
    glBegin(face.vertexIndices.size() == 3 ? GL_TRIANGLES : GL_QUADS);
    for (size_t i = 0; i < face.vertexIndices.size(); ++i) {
        if (!face.normalIndices.empty()) {
            const Normal& normal = normals[face.normalIndices[i] - 1];
            glNormal3f(normal.nx, normal.ny, normal.nz);
        }
        if (!face.textureIndices.empty()) {
            const TextureCoord& texCoord = textureCoords[face.textureIndices[i] - 1];
            glTexCoord2f(texCoord.u, texCoord.v);
        }
        const Vertex& vertex = vertices[face.vertexIndices[i] - 1];
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }
    glEnd();
}

void display(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(camX, camY, camZ),
        glm::vec3(modelCenter.x, modelCenter.y, modelCenter.z),
        glm::vec3(0.0, 1.0, 0.0));

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-100.0f, 0.0f, 0.0f); glVertex3f(100.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, -100.0f, 0.0f); glVertex3f(0.0f, 100.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -100.0f); glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    if (loadOBJ("PLACE WHERE THE OBJECT IS LOCATED")) {
        for (const auto& face : faces) {
            drawFace(face);
        }
    }

    glfwSwapBuffers(window);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OBJ Loader", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        updateCameraPosition();
        display(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
