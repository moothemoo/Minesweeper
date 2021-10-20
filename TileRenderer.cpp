#include"TileRenderer.h"

TileRenderer::TileRenderer(Shader& shader, const VAO& vaoIn)
    : _Shader(&shader),
    _VAO(&vaoIn)
{
}

void TileRenderer::drawTile(const Texture2D& tex, glm::vec2 loc) const
{
    (*_Shader).Use();
    (*_VAO).Bind();
    tex.Bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(loc, 0.0f));

    (*_Shader).SetMatrix4("model", model);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}