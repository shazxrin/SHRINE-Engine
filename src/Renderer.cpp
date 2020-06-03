#include <memory>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.hpp"
#include "shader/Attribute.hpp"
#include "shader/Uniform.hpp"

void Renderer::RenderModel(std::shared_ptr<Camera> camera, std::shared_ptr<Entity> entity, std::shared_ptr<ShaderProgram> shaderProgram)
{
	shaderProgram->Start();

	// TODO: Remove this 'wireframe' rendering mode.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, entity->position);
	// TODO: Find a better way to rotate.
	transform = glm::rotate(transform, glm::radians(entity->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(entity->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(entity->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, entity->scale);
	shaderProgram->SetMatrix4(Uniform::TRANSFORM.data(), transform);

	glm::mat4 view = glm::lookAt(camera->position, camera->target, camera->up);
	shaderProgram->SetMatrix4(Uniform::VIEW.data(), view);

	glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	shaderProgram->SetMatrix4(Uniform::PROJECTION.data(), projection);

	glBindVertexArray(entity->GetModel()->GetVAOId());
	glEnableVertexAttribArray(Attribute::POSITION_LOCATION);
	glDrawElements(GL_TRIANGLES, entity->GetModel()->GetVerticesCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(Attribute::POSITION_LOCATION);
	glBindVertexArray(0);
	
	shaderProgram->Stop();
}
