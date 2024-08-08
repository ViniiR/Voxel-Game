#pragma once

#include "glad.h"
#include <Camera.hpp>
#include <ScreenSize.hpp>

void pre_draw(Camera *camera, const ScreenSize &screen,
              GLuint graphicsPipelineShaderProgram);

void draw(GLuint VAO, GLuint vertices_VBO);
