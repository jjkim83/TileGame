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
	float frameInterval, D3DCOLOR textureColor,
	float scale)
{
	_spriteDX = spriteDX;
	_textureDX = textureDX;
	_frameInterval = frameInterval;

	// 출력할 영역 지정
	_textureRect.left = left;
	_textureRect.right = _textureRect.left + width;
	_textureRect.top = top;
	_textureRect.bottom = _textureRect.top + height;

	_textureColor = textureColor;

	_scale = scale;
	_width = width * _scale;
	_height = height * _scale;
}

void Frame::Render()
{
	D3DXVECTOR2 scale = D3DXVECTOR2(_scale, _scale);	// 확대 축소
	D3DXVECTOR2 rotCenter = D3DXVECTOR2(_width*0.5f, _height*0.5f);	// 회전 중심
	float rot = 0.0f;	// 회전 각도
	D3DXVECTOR2 translate = D3DXVECTOR2(100.0f-_width*0.5f, 100.0f-_height*0.5f);	// 이동

	D3DXMATRIX matrix;	// 크기, 회전, 회전 중심, 회전 각도, 이동
	D3DXMatrixTransformation2D(
		&matrix,		// 연산 결과
		NULL,		// 스케일의 중심점
		0.0f,		// 확대 회전 시킬 때, x,y의 비율이 다를 경우 조정 값
		&scale,		// 확대/축소
		&rotCenter,	// 회전 중심점
		rot,	// 회전 각도
		&translate);

	_spriteDX->SetTransform(&matrix);
	_spriteDX->Draw(_textureDX, &_textureRect, NULL, NULL,_textureColor);	// 2D 이미지 출력 공간. Texture(텍스쳐)
}

void Frame::Reset()
{
}
