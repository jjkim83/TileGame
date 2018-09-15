#pragma once

#include <string>
#include <vector>
#include <d3dx9.h>

class Frame;

class Sprite
{
private:
	LPDIRECT3DDEVICE9 _dxDevice;
	ID3DXSprite * _spriteDX;

	IDirect3DTexture9* _textureDX;
	
	std::wstring _fileName;
	D3DXIMAGE_INFO _texInfo;

	//Frame* _frame;
	std::vector<Frame*> _frameList;
	int _frameIdx;
	float _frameDuration;

public:
	Sprite();	// 생성자 (Constructor)
	~Sprite();	// 해제자 (파괴자)(Destructor)

	void Init(std::wstring fileName,
		LPDIRECT3DDEVICE9 dxDevice,
		ID3DXSprite * spriteDX);
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
};
