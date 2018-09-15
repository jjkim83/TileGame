#include "Frame.h"

Frame::Frame()
{
	_frameInterval = 0.2f;
}

Frame::~Frame()
{
}

void Frame::Init(ID3DXSprite* spriteDX, IDirect3DTexture9* textureDX,
	int left, int top, int width, int height,
	float frameInterval)
{
	_spriteDX = spriteDX;
	_textureDX = textureDX;
	_frameInterval = frameInterval;

	// 출력할 영역 지정
	_textureRect.left = left;
	_textureRect.right = _textureRect.left + width;
	_textureRect.top = top;
	_textureRect.bottom = _textureRect.top + height;

	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void Frame::Render()
{
	// 2D 이미지 출력 공간. Texture(텍스쳐)
	_spriteDX->Draw(
		_textureDX,		// 그릴 텍스쳐 정보가 들어있는 인터페이스
		&_textureRect,	// 원본 이미지에서 그릴 부분
		NULL,
		NULL,
		_textureColor	// 스프라이트의 색상과 알파채널
	);
}

void Frame::Reset()
{
}
