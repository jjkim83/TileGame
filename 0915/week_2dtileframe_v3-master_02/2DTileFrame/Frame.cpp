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

	_width = width;
	_height = height;

	_scale = scale;
	_width = width * _scale;
	_height=  height * _scale;

}

void Frame::Render()
{

	D3DXVECTOR2 scale = D3DXVECTOR2(_scale, _scale);
	D3DXVECTOR2 rotCenter = D3DXVECTOR2(_width*0.5f, _height*0.5f);
	float rot = 0.0f;

	//이동. 화면가운데출력되게
	D3DXVECTOR2 translate = D3DXVECTOR2(100.0f-_width*0.5f, 100.0f -_height *0.5f);

	D3DXMATRIX matrix;	// 행렬 만듬. 크기, 회전, 회전중심, 회전각도, 이동.
	D3DXMatrixTransformation2D(
		&matrix,	// 연산결과
		NULL,		// 스케일의 중심점 
		0.0f,		// 확대 회전시킬때 , x,y비율이 다를경우 조정값(잘 쓰진않음)
		&scale,		// 확대축소
		&rotCenter, // 회전중심점
		rot,		// 회전각도
		&translate);

	_spriteDX->SetTransform(&matrix);
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
