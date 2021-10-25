#include"Camera2D.h"

Camera2D::Camera2D(float width, float height, glm::vec2 position)
	:width(width),
	height(height),
	Position(position),
	projection(glm::mat4(1.0f)),
	regenProj(false)
{
	this->RegenProj();
}


void Camera2D::Matrix(Shader& shader, const char* uniform)
{
	shader.SetMatrix4(uniform, projection);
}

void Camera2D::SetPosition(glm::vec2 position)
{
	Position = position;
	regenProj = true;
}

void Camera2D::Move(glm::vec2 vector)
{
	Position += vector;
	regenProj = true;
}

void Camera2D::SetDimensions(glm::vec2 dimensions)
{
	height = dimensions[1];
	width = dimensions[0];
}

void Camera2D::RegenProj()
{
	if (regenProj)
	{
		projection = glm::ortho(
			(float)(Position[0] - width / 2),  //left
			(float)(Position[0] + width / 2),  //right
			(float)(Position[1] - height / 2), //bottom
			(float)(Position[1] + height / 2)  //top
		);
	}
}

glm::vec2 Camera2D::GetPosition() const
{
	return Position;
}

glm::mat4 Camera2D::GetProjection() const
{
	return projection;
}