#include "glad.h"

void create_vertex_array_object(GLuint VAO) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void create_vertex_buffer_object(GLuint VBO, int size, const float *data) {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void enable_vertex_attribute_pointers(unsigned int index) {
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(index);
}
