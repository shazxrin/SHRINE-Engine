#include "Renderer.hpp"

void Renderer::RenderModel(
	std::shared_ptr<Light> light,
	std::shared_ptr<Camera> camera, 
	std::shared_ptr<Entity> entity,
	std::shared_ptr<ShaderProgram> shaderProgram
)
{
	shaderProgram->Start();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entity->GetModel()->GetTexture()->GetTextureId());

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

	shaderProgram->SetVec3(Uniform::LIGHT_POSITION.data(), light->position);
	shaderProgram->SetVec3(Uniform::LIGHT_COLOR.data(), light->colour);
	shaderProgram->SetVec3(Uniform::CAMERA_POSITION.data(), camera->position);
	// TODO: Create Material class defining how shiny a model should be.
	shaderProgram->SetFloat(Uniform::SHININESS.data(), 75.0f);

	glBindVertexArray(entity->GetModel()->GetVAOId());

	glEnableVertexAttribArray(Attribute::POSITION_LOCATION);
	glEnableVertexAttribArray(Attribute::NORMAL_LOCATION);
	glEnableVertexAttribArray(Attribute::UV_COORDS_LOCATION);

	glDrawElements(GL_TRIANGLES, entity->GetModel()->GetVerticesCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(Attribute::POSITION_LOCATION);
	glDisableVertexAttribArray(Attribute::NORMAL_LOCATION);
	glDisableVertexAttribArray(Attribute::UV_COORDS_LOCATION);
	glBindVertexArray(0);
	
	shaderProgram->Stop();
}
