#ifndef __GAME_H__
#define __GAME_H__
#include "Caramel.h"

#include <memory>
#include <glm/glm.hpp>

// Why not:) 8bit field 
enum class DrawCommands : uint8_t
{
	BNW = 1 << 0,
	SAVE = 1 << 1,

};
inline DrawCommands operator|(DrawCommands a, DrawCommands b)
{
	return static_cast<DrawCommands>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}
inline DrawCommands operator|=(DrawCommands a, DrawCommands b)
{
	a = a | b;
	return a;
}
inline DrawCommands operator&(DrawCommands a, DrawCommands b)
{
	return static_cast<DrawCommands>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}


class Editor : public Caramel::Application
{
public:
	Editor();
	~Editor();

	bool OnCreate() override;
	void Update(float a_deltaTime) override;
	void ImDraw() override;
	void Draw() override;
	void Destroy() override;

private:

	void Save(std::string a_outDir);
	void Discard();
	bool LoadTexture();
	

private:
	std::shared_ptr<Caramel::Framebuffer> m_frameBuffer;
	std::shared_ptr<Caramel::Texture> m_texture;
	unsigned int m_vao, m_vbo, m_ibo;

	std::unordered_map<std::string, std::shared_ptr<Caramel::Shader>> m_shaders;

	std::string m_textureLocation;
	glm::vec3 m_brushColour;
	DrawCommands m_commands;

	glm::vec2 m_portSize;

};

#endif