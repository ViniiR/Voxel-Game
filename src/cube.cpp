#include "cube.hpp"
#include <iostream>
#include <vector>
#include "glad.h"

GLuint cube_specification(GLuint VAO, GLuint VBO, GLuint EBO) {
    static const std::vector<GLfloat> vertices = {
        // Positions         // Colors
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  // Vertex 0
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Vertex 1
        0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 1.0f,  // Vertex 2
        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 0.0f,  // Vertex 3
        -0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 1.0f,  // Vertex 4
        0.5f,  -0.5f, 0.5f,  0.0f, 1.0f, 1.0f,  // Vertex 5
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Vertex 6
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, 0.0f   // Vertex 7
    };
    static const std::vector<GLuint> indices = {// Front face
                                                0, 1, 2, 2, 3, 0,

                                                // Back face
                                                4, 5, 6, 6, 7, 4,

                                                // Left face
                                                0, 3, 7, 7, 4, 0,

                                                // Right face
                                                1, 5, 6, 6, 2, 1,

                                                // Top face
                                                3, 2, 6, 6, 7, 3,

                                                // Bottom face
                                                0, 1, 5, 5, 4, 0};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,                    //
                 vertices.size() * sizeof(GLfloat),  //
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           //
                 indices.size() * sizeof(GLfloat),  //
                 indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    return VAO;
}

/*GLuint cube_specification(GLuint vertices_VBO, GLuint VAO, GLuint color_VBO) {*/
/*    static const std::vector<GLfloat> vertices_buffer_data = {*/
/*        -1.0f, -1.0f, -1.0f,  //*/
/*        -1.0f, -1.0f, 1.0f,   //*/
/*        -1.0f, 1.0f,  1.0f,   //*/
/*        1.0f,  1.0f,  -1.0f,  //*/
/*        -1.0f, -1.0f, -1.0f,  //*/
/*        -1.0f, 1.0f,  -1.0f,  //*/
/*        1.0f,  -1.0f, 1.0f,   //*/
/*        -1.0f, -1.0f, -1.0f,  //*/
/*        1.0f,  -1.0f, -1.0f,  //*/
/*        1.0f,  1.0f,  -1.0f,  //*/
/*        1.0f,  -1.0f, -1.0f,  //*/
/*        -1.0f, -1.0f, -1.0f,  //*/
/*        -1.0f, -1.0f, -1.0f,  //*/
/*        -1.0f, 1.0f,  1.0f,   //*/
/*        -1.0f, 1.0f,  -1.0f,  //*/
/*        1.0f,  -1.0f, 1.0f,   //*/
/*        -1.0f, -1.0f, 1.0f,   //*/
/*        -1.0f, -1.0f, -1.0f,  //*/
/*        -1.0f, 1.0f,  1.0f,   //*/
/*        -1.0f, -1.0f, 1.0f,   //*/
/*        1.0f,  -1.0f, 1.0f,   //*/
/*        1.0f,  1.0f,  1.0f,   //*/
/*        1.0f,  -1.0f, -1.0f,  //*/
/*        1.0f,  1.0f,  -1.0f,  //*/
/*        1.0f,  -1.0f, -1.0f,  //*/
/*        1.0f,  1.0f,  1.0f,   //*/
/*        1.0f,  -1.0f, 1.0f,   //*/
/*        1.0f,  1.0f,  1.0f,   //*/
/*        1.0f,  1.0f,  -1.0f,  //*/
/*        -1.0f, 1.0f,  -1.0f,  //*/
/*        1.0f,  1.0f,  1.0f,   //*/
/*        -1.0f, 1.0f,  -1.0f,  //*/
/*        -1.0f, 1.0f,  1.0f,   //*/
/*        1.0f,  1.0f,  1.0f,   //*/
/*        -1.0f, 1.0f,  1.0f,   //*/
/*        1.0f,  -1.0f, 1.0f    //*/
/*    };*/
/**/
/*    static const std::vector<GLfloat> color_buffer_data = {*/
/*        0.583f, 0.771f, 0.014f,  //*/
/*        0.609f, 0.115f, 0.436f,  //*/
/*        0.327f, 0.483f, 0.844f,  //*/
/*        0.822f, 0.569f, 0.201f,  //*/
/*        0.435f, 0.602f, 0.223f,  //*/
/*        0.310f, 0.747f, 0.185f,  //*/
/*        0.597f, 0.770f, 0.761f,  //*/
/*        0.559f, 0.436f, 0.730f,  //*/
/*        0.359f, 0.583f, 0.152f,  //*/
/*        0.483f, 0.596f, 0.789f,  //*/
/*        0.559f, 0.861f, 0.639f,  //*/
/*        0.195f, 0.548f, 0.859f,  //*/
/*        0.014f, 0.184f, 0.576f,  //*/
/*        0.771f, 0.328f, 0.970f,  //*/
/*        0.406f, 0.615f, 0.116f,  //*/
/*        0.676f, 0.977f, 0.133f,  //*/
/*        0.971f, 0.572f, 0.833f,  //*/
/*        0.140f, 0.616f, 0.489f,  //*/
/*        0.997f, 0.513f, 0.064f,  //*/
/*        0.945f, 0.719f, 0.592f,  //*/
/*        0.543f, 0.021f, 0.978f,  //*/
/*        0.279f, 0.317f, 0.505f,  //*/
/*        0.167f, 0.620f, 0.077f,  //*/
/*        0.347f, 0.857f, 0.137f,  //*/
/*        0.055f, 0.953f, 0.042f,  //*/
/*        0.714f, 0.505f, 0.345f,  //*/
/*        0.783f, 0.290f, 0.734f,  //*/
/*        0.722f, 0.645f, 0.174f,  //*/
/*        0.302f, 0.455f, 0.848f,  //*/
/*        0.225f, 0.587f, 0.040f,  //*/
/*        0.517f, 0.713f, 0.338f,  //*/
/*        0.053f, 0.959f, 0.120f,  //*/
/*        0.393f, 0.621f, 0.362f,  //*/
/*        0.673f, 0.211f, 0.457f,  //*/
/*        0.820f, 0.883f, 0.371f,  //*/
/*        0.982f, 0.099f, 0.879f   //*/
/*    };*/
/**/
/*    // Generates and binds vertex Vertex Array Object*/
/*    glGenVertexArrays(1, &VAO);*/
/*    glBindVertexArray(VAO);*/
/**/
/*    // Generates and binds vertex Vertex Buffer Object*/
/*    glGenBuffers(1, &vertices_VBO);*/
/*    glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);*/
/*    glBufferData(GL_ARRAY_BUFFER, vertices_buffer_data.size() * sizeof(GLfloat),*/
/*                 vertices_buffer_data.data(), GL_STATIC_DRAW);*/
/**/
/*    // Sets vertex attribute pointers*/
/*    glEnableVertexAttribArray(0);*/
/*    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);*/
/**/
/*    // Generates and binds color Vertex Buffer Object*/
/*    glGenBuffers(1, &color_VBO);*/
/*    glBindBuffer(GL_ARRAY_BUFFER, color_VBO);*/
/*    glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(GLfloat),*/
/*                 color_buffer_data.data(), GL_STATIC_DRAW);*/
/**/
/*    // Sets color attribute pointers*/
/*    glEnableVertexAttribArray(1);*/
/*    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);*/
/**/
/*    // unbinds current VAO to prevent accidental modifications*/
/*    glBindVertexArray(0);*/
/**/
/*    GLenum err = glGetError();*/
/*    if (err != GL_NO_ERROR) {*/
/*        std::cerr << "cube spec OpenGL error: " << err << std::endl;*/
/*    }*/
/**/
/*    return VAO;*/
/*}*/
