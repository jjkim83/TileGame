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

	//출력할 영역지정
	_textureRect.left = left;
	_textureRect.right = _textureRect.left + width;
	_textureRect.top = top;
	_textureRect.bottom = _textureRect.top + height;

	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);

}

void Frame::Render()
{

	//2D이미지출력공간. Texture(텍스쳐,2d이미지 한장)
	_spriteDX->Draw(
		_textureDX,		//그릴텍스쳐 정보가 들어있는 인터페이스
		&_textureRect,	// 원본이미지에서 그릴 부분	
		NULL,			
		NULL,
		_textureColor	//스프라이트의 색상과 알파채널
	);		

}

void Frame::Reset()
{

}


