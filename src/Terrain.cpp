/*
 * @file
 * @author Vsevolod (Seva) Ivanov
*/

#include "Terrain.hpp"

Terrain::Terrain():
    renderMode(GL_TRIANGLES)
{
    this->shader = new Shader("src/shaders/terrain.vs",
                              "src/shaders/terrain.fs");
    this->build();
    this->initBuffers();
}

Terrain::~Terrain()
{
    glDeleteVertexArrays(1, &this->vaoId);
    glDeleteBuffers(1, &this->vboId);

    delete this->shader;
}

GLenum Terrain::getRenderMode() const
{
    return this->renderMode;
}

void Terrain::setRenderMode(const GLenum renderMode)
{
    this->renderMode = renderMode;
}

void Terrain::render(const Window* window,
            const Camera* camera,
            const glm::mat4 view,
            const glm::mat4 projection)
{
    this->shader->use();

    this->upload();

    this->updateMVP(view, projection);

    this->draw();
}

void Terrain::updateMVP(const glm::mat4 view, const glm::mat4 projection)
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

// TODO WIP recursive
void Terrain::build()
{
/*
    // square
    this->vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f)); // b-l
    this->vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));  // b-r
    this->vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f)); // t-l
    this->vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));  // t-r

    this->verticesI = {
        0, 1, 2,
        1, 2, 3
    };
*/
    // floor
    uint8_t xcells = 5;
    uint8_t zcells = 5;

    // floor test MOQ
    for (GLfloat x = -1.0f; x < 1.0f; x += (1.0f / xcells))
    {
        for (GLfloat z = -1.0f; z < 1.0f; z += (1.0f / zcells))
        {
            //printf("(%f,%f,%f)\n", x, 0.5f, z);

            this->vertices.push_back(glm::vec3(x, 0.5f, z));
        }
    }

    //printf("-----------vsize: %i\n", this->vertices.size());

    for (uint8_t x = 0; x < xcells * 2; x++)
    {
        for (uint8_t z = 0; z < zcells * 2; z++)
        {
            uint16_t p1 = z + xcells * x;
            uint16_t p2 = z + xcells * (x + 1);

            // Triangle 1
            this->verticesI.push_back(p1);
            this->verticesI.push_back(p1 + 1);
            this->verticesI.push_back(p2);

            // Triangle 2
            this->verticesI.push_back(p1 + 1);
            this->verticesI.push_back(p2);
            this->verticesI.push_back(p2 + 1);
        }
    }
    //printf("-----------visize: %i\n", this->verticesI.size());
}

void Terrain::initBuffers()
{
    glGenBuffers(1, &this->vboId);
    glGenVertexArrays(1, &this->vaoId);
    glGenBuffers(1, &this->eboId);

    glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(glm::vec3) * this->vertices.size(),
                 &this->vertices[0],
                 GL_STATIC_DRAW);

    // has to be before ebo bind
    glBindVertexArray(this->vaoId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(this->verticesI) * this->verticesI.size(),
                 &this->verticesI[0],
                 GL_STATIC_DRAW);

    // enable vao -> vbo pointing
    glEnableVertexAttribArray(0);
    // setup formats of my vao attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);

    // unbind vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // unbind vao
    glBindVertexArray(0);
}

void Terrain::upload()
{
    // TODO send matrices
    //
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboId);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(GLushort) * this->verticesI.size(),
                    &this->verticesI[0],
                    GL_STATIC_DRAW);

    // don't disconnect to draw
}

void Terrain::draw()
{
    glBindVertexArray(this->vaoId);
        glDrawElements(this->renderMode,
                       this->verticesI.size(),
                       GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}