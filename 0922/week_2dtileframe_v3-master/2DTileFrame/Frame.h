#pragma once

#include <d3dx9.h>

class Frame
{
private:
	ID3DXSprite * _spriteDX;
	IDirect3DTexture9* _textureDX;

	RECT _textureRect;
	D3DCOLOR _textureColor;

	float _frameInterval;
	int _width;
	int _height;
	float _scale;

public:
	Frame();
	~Frame();

	void Init(ID3DXSprite* spriteDX, IDirect3DTexture9* textureDX,
		int left, int top, int right, int bottom,
		float frameInterval, D3DCOLOR textureColor,
		float scale);
	void Render();
	void Reset();

	float GetFrameInterval()
	{
		return _frameInterval;
	}
};
