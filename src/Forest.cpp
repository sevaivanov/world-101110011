/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Forest.cpp
 * Author: sami
 * 
 * Created on April 14, 2017, 12:12 PM
 */

#include "Forest.h"

Forest::Forest(const uint16_t xcells, const uint16_t zcells, Terrain* terrain):
    X_CELLS(xcells), Z_CELLS(zcells), renderMode(GL_TRIANGLES) {
    this->shader = new Shader("src/shaders/objecttest.vs",
                              "src/shaders/objecttest.fs");
    this->build(terrain);
this->rotate(glm::vec3(12.5, 0, 0));
}

Forest::~Forest() {
}

GLenum Forest::getRenderMode() const {
    return this->renderMode;
}

void Forest::setRenderMode(const GLenum renderMode) {
    this->renderMode = renderMode;
}

void Forest::render(const Window* window,
                    const Camera* camera,
                    const glm::mat4 view,
                    const glm::mat4 projection) {
    this->shader->use();
    this->updateMVP(view, projection);
    this->draw();
}

void Forest::rotate(const glm::vec3 spin) {
    this->model = glm::rotate(this->model, spin.x, glm::vec3(1, 0, 0));
    this->model = glm::rotate(this->model, spin.y, glm::vec3(0, 1, 0));
    this->model = glm::rotate(this->model, spin.z, glm::vec3(0, 0, 1));
}

void Forest::build(Terrain* terrain) {
    Point offset(0,0,0,Vector(0,1,0));
    
	PGTree1 tree1 = PGTree1(offset, 0.25f, 0.05f, 1.0f);
    GLObject* myObj1 = new GLObject(tree1.objects);
    
    PGTree2 tree2 = PGTree2(offset, 0.25f, 0.04f, 1.0f);
    GLObject* myObj2 = new GLObject(tree2.objects);
    
    
    // TODO remove
    //glm::vec3 translations1[X_CELLS*Z_CELLS];
    //glm::vec3 translations2[X_CELLS*Z_CELLS];
    
    glm::vec3 translations1[2500];
    glm::vec3 translations2[2500];
    int index1 = 0;
    int index2 = 0;
    for(int c = 0; c < 2; c++) {
        for(GLint x = 5; x < X_CELLS; x += 10)
        {
            for(GLint z = 5 + c * 5; z < Z_CELLS; z += 10)
            {
                float numX = randNum(-2.0f,2.1f);
                float numY = randNum(-2.0f,2.1f);
                
                glm::vec3 translation;
                /*translation.x = (GLfloat)x / 10.0f + offset2;
                translation.y = (GLfloat)y / 10.0f + offset2;*/
                translation.x = (GLfloat)x + numX;
                translation.z = (GLfloat)z + numY;
                translation.y = -(x+z*4)/80;
                if(c == 0)
                    translations1[index1++] = translation;
                else
                    translations2[index2++] = translation;
            }
        }
    }
    
    myObj1->initBuffers(translations1, index1-1);
    myObj2->initBuffers(translations2, index2-1);
    objects.push_back(myObj1);
    objects.push_back(myObj2);
}

void Forest::updateMVP(const glm::mat4 view, const glm::mat4 projection)
{
    // locate in shaders
    GLint modelLoc = glGetUniformLocation(this->shader->programId, "model");
    GLint viewLoc = glGetUniformLocation(this->shader->programId, "view");
    GLint projLoc = glGetUniformLocation(this->shader->programId, "projection");

    // send to shaders
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Forest::draw()
{
    for(int c = 0; c < objects.size(); c++) {
        objects.at(c)->draw();
    }
}

float Forest::randNum(float min, float max) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_real_distribution<float> uni(min,max); // guaranteed unbiased

    return uni(rng);
}
