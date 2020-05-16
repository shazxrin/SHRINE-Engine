#include "Renderer.hpp"


void Renderer::RenderModel(Model* model, ShaderProgram* shaderProgram)
{
	shaderProgram->Start();
	glBindVertexArray(model->GetVAOId());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, model->GetVerticesCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shaderProgram->Stop();
}
