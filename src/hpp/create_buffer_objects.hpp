#pragma once

#include "glad.h"

void create_vertex_buffer_object(GLuint VBO, int size, const float *data);

void enable_vertex_attribute_pointers(unsigned int index);

void create_vertex_array_object(GLuint VAO);
