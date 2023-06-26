//
// Created by madre on 5/12/2022.
//

#include "Floor.h"

#include <shaders/phong_vert_glsl_glsl.h>
#include <shaders/phong_frag_glsl_glsl.h>

Floor::Floor(const std::string &modelName, const std::string &textureName) : Model(modelName, textureName) {
    if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl_glsl, phong_frag_glsl_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("pavingStoneLong.bmp"));
}
