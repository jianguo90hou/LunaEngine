
#pragma once


#include "LunaEngineDefine.h"


class LunaRenderer;
class ENGINE_EXPORT LunaEngine
{
public:
	LunaEngine();
	~LunaEngine();

public:
	void Init();
	
	void Update();
	void Render();

	void OnPostRenderer();
private:
	LunaRenderer* m_pRenderer;
};




