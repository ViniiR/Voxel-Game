#include "cube.hpp"
#include <string>
#include <vector>
#include "glad.h"
#include <textures.hpp>

void draw_cube_face(GLuint VAO, std::string face_texture_path,
                    CubeFace face_position, GLuint EBO) {
    glBindTexture(GL_TEXTURE_2D, load_texture(face_texture_path.data()));

    std::vector<GLuint> face_indices = {0};

    // I changed the face positions to match the CAMERA's perspective
    // so LEFT == left side of the camera/screen
    switch (face_position) {
        case Front:
            face_indices = std::vector<GLuint>{0, 1, 2, 2, 3, 0};
            break;
        case Back:
            face_indices = std::vector<GLuint>{4, 5, 6, 6, 7, 4};
            break;
        case Right:
            face_indices = std::vector<GLuint>{12, 13, 15, 13, 14, 15};
            break;
        case Left:
            face_indices = std::vector<GLuint>{8, 9, 11, 9, 10, 11};
            break;
        // top originally rendered the bottom of the cube and vice-versa
        case Bottom:
            face_indices = std::vector<GLuint>{20, 21, 23, 21, 22, 23};
            break;
        case Top:
            face_indices = std::vector<GLuint>{16, 17, 19, 17, 18, 19};
            break;
    }

    glBindVertexArray(VAO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,                //
                 face_indices.size() * sizeof(GLfloat),  //
                 face_indices.data(), GL_STATIC_DRAW);

    // drawing
    glDrawElements(GL_TRIANGLES, 36 / 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

GLuint cube_specification(GLuint VAO, GLuint VBO, GLuint EBO) {
    static const std::vector<GLfloat> vertices = {
        // Positions         // Colors         // Texture Coords
        // Front face
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 0
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // 1
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,    // 2
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // 3

        // Back face
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 4
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,   // 5
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,    // 6
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // 7

        // Left face
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // 4
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 0
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // 3
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,    // 7

        // Right face
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 1
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,   // 5
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // 6
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // 2

        // Top face
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 3
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,   // 2
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,    // 6
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // 7

        // Bottom face
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // 0
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,   // 1
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,    // 5
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // 4
    };
    /*static const std::vector<GLfloat> uv_texture_indices = {*/
    /*    0.0f, 0.0f,  //*/
    /*    1.0f, 0.0f,  //*/
    /*    1.0f, 1.0f,  //*/
    /*    0.1f, 1.0f   //*/
    /*};*/
    /*static const std::vector<GLfloat> vertices = {*/
    /*    // Positions         // Colors         // Textures*/
    /*    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // Vertex 0*/
    /*    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Vertex 1*/
    /*    0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // Vertex 2*/
    /*    -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Vertex 3*/
    /*    -0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Vertex 4*/
    /*    0.5f,  -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // Vertex 5*/
    /*    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // Vertex 6*/
    /*    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Vertex 7*/
    /*};*/
    static const std::vector<GLfloat> indices = {
        // front face
        0, 1, 3,  // 1st triangle
        1, 2, 3,  // 2nd triangle

        // back face
        4, 5, 6,  // 3rd triangle
        6, 7, 4,  // 4th triangle

        // left face
        8, 9, 11,   // 5th triangle
        9, 10, 11,  // 6th triangle

        // right face
        12, 13, 15,  // 7th triangle
        13, 14, 15,  // 8th triangle

        // bottom face
        16, 17, 19,  // 9th triangle
        17, 18, 19,  // 10th triangle

        // top face
        20, 21, 23,  // 11th triangle
        21, 22, 23,  // 12th triangle
    };

    /*static const std::vector<GLuint> indices = {// Front face*/
    /*                                            0, 1, 2, 2, 3, 0,*/
    /**/
    /*                                            // Back face*/
    /*                                            4, 5, 6, 6, 7, 4,*/
    /**/
    /*                                            // Left face*/
    /*                                            0, 3, 7, 7, 4, 0,*/
    /**/
    /*                                            // Right face*/
    /*                                            1, 5, 6, 6, 2, 1,*/
    /**/
    /*                                            // Top face*/
    /*                                            3, 2, 6, 6, 7, 3,*/
    /**/
    /*                                            // Bottom face*/
    /*                                            0, 1, 5, 5, 4, 0};*/
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    /*glGenBuffers(1, &EBO);*/

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,                    //
                 vertices.size() * sizeof(GLfloat),  //
                 vertices.data(), GL_STATIC_DRAW);

    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
    /*glBufferData(GL_ELEMENT_ARRAY_BUFFER,           //*/
    /*             indices.size() * sizeof(GLfloat),  //*/
    /*             indices.data(), GL_STATIC_DRAW);*/

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // unbind current VAO
    glBindVertexArray(0);

    return VAO;
}

/*GLuint cube_specification(GLuint vertices_VBO, GLuint VAO, GLuint color_VBO)
 * {*/
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
/*    glBufferData(GL_ARRAY_BUFFER, vertices_buffer_data.size() *
 * sizeof(GLfloat),*/
/*                 vertices_buffer_data.data(), GL_STATIC_DRAW);*/
/**/
/*    // Sets vertex attribute pointers*/
/*    glEnableVertexAttribArray(0);*/
/*    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);*/
/**/
/*    // Generates and binds color Vertex Buffer Object*/
/*    glGenBuffers(1, &color_VBO);*/
/*    glBindBuffer(GL_ARRAY_BUFFER, color_VBO);*/
/*    glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() *
 * sizeof(GLfloat),*/
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
