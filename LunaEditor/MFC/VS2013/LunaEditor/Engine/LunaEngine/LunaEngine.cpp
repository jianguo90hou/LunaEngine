
#include "LunaEngine.h"
#include <Renderer/LunaRenderer.h>

LunaEngine::LunaEngine()
{
}

LunaEngine::~LunaEngine()
{
}

void LunaEngine::Init()
{
	m_pRenderer = LunaRenderer::Instance();
	m_pRenderer->Init();
}

void LunaEngine::Update()
{
	
}

void LunaEngine::Render()
{
	m_pRenderer->Render();
}

void LunaEngine::OnPostRenderer()
{

}