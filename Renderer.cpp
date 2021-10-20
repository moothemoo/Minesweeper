#include"Renderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader, GLfloat* vertices, unsigned int vertSizeBytes, GLuint* indices, unsigned int indexSizeBytes)
    : _Shader(shader), 
    indSize(indexSizeBytes/sizeof(GLfloat)), 
    _VBO(vertices, vertSizeBytes),
    _EBO(indices, indexSizeBytes)
{
	_VAO.Bind();
    _VBO.Bind();
    _EBO.Bind();

    _VAO.LinkAttrib(_VBO, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);

    _VAO.Unbind();
    _VBO.Unbind();
    _EBO.Unbind();
}


void SpriteRenderer::drawSprite(Texture2D& tex, glm::vec2 loc, float angle, glm::vec2 scale, glm::vec3 color)
{
    _Shader.Use();
    _VAO.Bind();
    tex.Bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(loc, 0.0f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scale, 1.0f));
    
    _Shader.SetMatrix4("model", model);
    _Shader.SetVector3f("color", color);

    glDrawElements(GL_TRIANGLES, indSize, GL_UNSIGNED_INT, 0);
}

