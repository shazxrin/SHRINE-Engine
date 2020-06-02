#include "Renderer.hpp"
#include "Attribute.hpp"


void Renderer::RenderModel(Model* model, ShaderProgram* shaderProgram)
{
	shaderProgram->Start();
	glBindVertexArray(model->GetVAOId());
	glEnableVertexAttribArray(Attribute::VERTEX_POS_LOCATION);
	glDrawElements(GL_TRIANGLES, model->GetVerticesCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(Attribute::VERTEX_POS_LOCATION);
	glBindVertexArray(0);
	shaderProgram->Stop();
}
