#pragma once

#include "glad.h"

void pre_draw(Camera *camera, const ScreenSize &screen,
              GLuint graphicsPipelineShaderProgram);

void draw(GLuint VAO);
