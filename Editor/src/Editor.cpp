#include "Editor.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace Caramel;

Editor::Editor()
{

}

Editor::~Editor()
{
}

bool Editor::OnCreate()
{
	m_frameBuffer = std::make_shared<Caramel::Framebuffer>();

	const GLfloat vertices[] = {
		//  Position	Texcoords
		 1.0f, -1.0f,	1.0f, 0.0f, // Bottom-right
		 1.0f,  1.0f,	1.0f, 1.0f, // Top-right
		-1.0f,  1.0f,	0.0f, 1.0f, // Top-left
		-1.0f, -1.0f,	0.0f, 0.0f  // Bottom-left
	};
	const GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Create Vertex Array Object
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Specify the layout of the vertex data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	Caramel::Utility::GetGLErrors();

	m_shaders["Default"] = Shader::CreateShader(Utility::GetWorkingDir() + "resources/shaders/defaultShader.glsl");
	//m_shaders["B&W"] = Shader::CreateShader("resources/shaders/B&WShader");


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	m_texture = Texture::CreateTexture("resources/textures/empty.png");
	if (m_shaders["Default"]->Bind())
	{
		m_shaders["Default"]->SetInt("gTexture", 0, true);
	}

	

	return true;
}

void Editor::Update(float a_deltaTime)
{
	// Test if any shaders need to filter the image
	if ((uint8_t)(m_commands & DrawCommands::BNW) != 0)
	{
		// bind bw shader and draw
	}
}

void Editor::ImDraw()
{
	// Draw ImGui on the backbuffer as we're drawing the scene as a texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	static bool p_open = true;

	static bool opt_fullscreen_persistant = true;
	static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
	bool opt_fullscreen = opt_fullscreen_persistant;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", &p_open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Dockspace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Viewport");
	auto viewportSize = ImGui::GetContentRegionAvail();
	m_portSize = { viewportSize.x, viewportSize.y };
	m_frameBuffer->ResizeFBO(viewportSize.x, viewportSize.y); // Resize the fbo to match the viewport size
	//cam->SetProjectionMatrix(glm::perspective(glm::radians(50.0f), viewportSize.x / viewportSize.y, 0.1f, 5000.0f));
	ImTextureID texID = (void*)(intptr_t)m_frameBuffer->m_colourTex;
	ImGui::Image(texID, viewportSize, { 0, 1 }, { 1, 0 });
	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::Begin("Settings");
	Utility::TextureButton("Image", m_texture);
	ImGui::ColorPicker3("Brush Colour", glm::value_ptr(m_brushColour));
	if (ImGui::Button("Save"))
	{

	}
	ImGui::End();
	ImGui::End();
}

void Editor::Draw()
{
	m_frameBuffer->Bind();

	if (m_shaders["Default"]->Bind())
	{
		m_texture->Bind(GL_TEXTURE0);
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Editor::Destroy()
{
	const GLuint buffers[2] = { m_vbo, m_ibo };
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(2, buffers);
}
