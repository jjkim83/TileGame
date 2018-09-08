#include <d3dx9.h>
#include "Sprite.h"


Sprite::Sprite()
{

}
Sprite::~Sprite()
{

}
void Sprite::Init(std::wstring fileName,
	LPDIRECT3DDEVICE9 dxDevice,
	ID3DXSprite * spriteDX)

{

	_dxDevice = dxDevice;
	_spriteDX = spriteDX;

	HRESULT hr;

	D3DXIMAGE_INFO texInfo;
	{
	// 파일로부터 이미지의 너비와 높이를 얻는다
	hr = D3DXGetImageInfoFromFile(fileName.c_str(), &texInfo);
	if (FAILED(hr))
	{
	return ;
	}
	//이미지데이터 로드.
	hr = D3DXCreateTextureFromFileEx(dxDevice,
	fileName.c_str(),
	texInfo.Width, texInfo.Height,
	1,
	0,
	D3DFMT_UNKNOWN,
	D3DPOOL_DEFAULT,
	D3DX_DEFAULT,
	D3DX_DEFAULT,
	D3DCOLOR_ARGB(255, 255, 255, 255),
	&texInfo,
	NULL,
	&_textureDX);

	if (FAILED(hr))
	{
	return ;
	}

	//출력할 영역지정
	_textureRect.left = 0;
	_textureRect.right = _textureRect.left + texInfo.Width;
	_textureRect.top = 0;
	_textureRect.bottom = _textureRect.top + texInfo.Height;

	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	}

}
void Sprite::Render()
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
void Sprite::Release()
{

}
void Sprite::Reset()
{

}



