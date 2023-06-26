//
// Created by madre on 3/12/2022.
//

#include "ParticleSystem.h"
#include "PureParticle.h"
#include "src/project/Scene.h"

#include <shaders/particle_vert_glsl.h>
#include <shaders/particle_frag_glsl.h>

void logVec3(glm::vec3 vector){
    std::cout << vector.x << "/" << vector.y << "/" << vector.z << std::endl;
}
void logVec2(glm::vec2 vector){
    std::cout << vector.x << "/" << vector.y << std::endl;
}

void ParticleSystem::render(Scene &scene) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_CULL_FACE);
    shader->use();
    for (PureParticle particle : this->particles)
    {
        if (particle.Life > 0.0f)
        {
            shader->setUniform("offset", particle.Position);
            shader->setUniform("color", particle.Color);
            shader->setUniform("sprite", *texture);
            shader->setUniform("projection", scene.camera->projectionMatrix);
            shader->setUniform("view", scene.camera->viewMatrix);
            shader->setUniform("model", particle.ModelMatrix);


            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool ParticleSystem::update(Scene &scene, float dt) {
    int newParticles = this->amount / 10;

    for (unsigned int i = 0; i < newParticles; ++i){
        int unusedParticle = this->firstUnusedParticle();
        this->respawnParticle(this->particles[unusedParticle], glm::vec3{0.5,0.5,0.5});
//        this->particles[unusedParticle].update(scene, dt);
    }

    for (unsigned int i = 0; i < this->amount; ++i){
        PureParticle &temp = this->particles[i];
        temp.Life -= dt;
        if (temp.Life > 0.0f){
            temp.Position += temp.Velocity * dt;
            temp.Color.a -= dt;
            temp.Velocity.y += dragPower * dt;
        }
        temp.update(scene, dt);
    }

    return true;
}

ParticleSystem::ParticleSystem() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(particle_vert_glsl, particle_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("explosion.bmp"));

    float quadSize = 0.3;
    float particle_quad[] = {
            0.0f, quadSize, 0.0f, quadSize,
            quadSize, 0.0f, quadSize, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, quadSize, 0.0f, quadSize,
            quadSize, quadSize, quadSize, 1.0f,
            quadSize, 0.0f, quadSize, 0.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    //prebind should not be needed here
    glBindVertexArray(this->VAO);
    // fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    // create this->amount default particle instances
    for (unsigned int i = 0; i < this->amount; ++i)
        particles.emplace_back(PureParticle());

    std::cout << "DONE" << particles.size() << std::endl;
}

void ParticleSystem::respawnParticle(PureParticle &particle, glm::vec3 offset) {
    //Random is used to define the starting position near the Particle systems coordinate system
    int maxRandom = 2;
    int minRandom = -1;
    float randomX = minRandom + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxRandom-minRandom)));
    float randomY = minRandom + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxRandom-minRandom)));
    float randomZ = minRandom + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxRandom-minRandom)));

    float randomLife = (rand() % 2);

    int maxVelocity = 2;
    int minVelocity = -2;
    float randomVelocityX = minVelocity + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxVelocity-minVelocity)));
    float randomVelocityY = 2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5-2)));
    float randomVelocityZ = minVelocity + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxVelocity-minVelocity)));

    //float rColor = 0.5f + ((rand() % 100) / 100.0f);

    int maxRotation = 6;
    int minRotation = 0;
    float randomRotationX = ((rand() % maxRotation) + minRotation);
    float randomRotationY = ((rand() % maxRotation) + minRotation);
    float randomRotationZ = ((rand() % maxRotation) + minRotation);

    randomRotationX = 0;
    randomRotationY = 0;
    randomRotationZ = minRotation + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxRotation-minRotation)));

    particle.Color = glm::vec4(1, 1, 1, 1.0f);
    particle.Life = randomLife;
    particle.Velocity = {randomVelocityX, randomVelocityY, randomVelocityZ};
    particle.rotation = {randomRotationX, randomRotationY, randomRotationZ};

    particle.Position.x = this->position.x + randomX + offset.x;
    particle.Position.y = this->position.y + randomY + offset.y;
    particle.Position.z = this->position.z + randomZ + offset.z;
    //logVec3(particle.Color);
}

unsigned int lastUsedParticle = 0;
unsigned int ParticleSystem::firstUnusedParticle(){
    for (unsigned int i = lastUsedParticle; i < this->amount; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    for (unsigned int i = 0; i < lastUsedParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }

    lastUsedParticle = 0;

    return 0;
}