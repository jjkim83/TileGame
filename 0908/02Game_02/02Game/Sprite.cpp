#include <d3dx9.h>
#include "Frame.h"
#include "Sprite.h"


Sprite::Sprite()
{

}

Sprite::~Sprite()
{

	/*
	if (NULL != _frame)
	{
		delete _frame;
	}
	*/

	for (int i = 0; i < _frameList.size(); i++)
	{
		delete _frameList[i];
	}

	_frameList.clear();

	if (_textureDX)
	{
		_textureDX->Release();
		_textureDX = NULL;
	}

}

void Sprite::Init(std::wstring fileName,
	LPDIRECT3DDEVICE9 dxDevice,
	ID3DXSprite * spriteDX)

{
	_fileName = fileName;
	_dxDevice = dxDevice;
	_spriteDX = spriteDX;

	HRESULT hr;

	//D3DXIMAGE_INFO texInfo;

	{
	// 파일로부터 이미지의 너비와 높이를 얻는다
	hr = D3DXGetImageInfoFromFile(fileName.c_str(), &_texInfo);
	if (FAILED(hr))
	{
	return ;
	}
	//이미지데이터 로드.
	hr = D3DXCreateTextureFromFileEx(dxDevice,
	fileName.c_str(),
	_texInfo.Width, _texInfo.Height,
	1,
	0,
	D3DFMT_UNKNOWN,
	D3DPOOL_DEFAULT,
	D3DX_DEFAULT,
	D3DX_DEFAULT,
	D3DCOLOR_ARGB(255, 255, 255, 255),
	&_texInfo,
	NULL,
	&_textureDX);

	if (FAILED(hr))
	{
	return ;
	}

/*
	//출력할 영역지정
	_textureRect.left = 0;
	_textureRect.right = _textureRect.left + 48;
	_textureRect.top = 0;
	_textureRect.bottom = _textureRect.top + 48;

	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);

*/
/*
	_frame = new Frame();
	_frame->Init(_spriteDX, _textureDX, 48, 48, 48, 48);
*/
	{
		Frame* frame = new Frame();
		frame->Init(_spriteDX, _textureDX, 0, 0, 48, 48, 0.2f);
		_frameList.push_back(frame);
	}

	{
		Frame* frame = new Frame();
		frame->Init(_spriteDX, _textureDX, 0, 48, 48, 48, 0.2f);
		_frameList.push_back(frame);
	}

	{
		Frame* frame = new Frame();
		frame->Init(_spriteDX, _textureDX, 0, 144, 48, 48, 0.2f);
		_frameList.push_back(frame);
	}


	_frameIdx = 0;
	_frameDuration = 0.0f;

	}

	/*
	_textureRect.left = 0;
	_textureRect.right = _textureRect.left. + _texInfo.Width;
	_textureRect.top = 0;
	_textureRect.bottom = _textureRect.top + _texInfo.Height;
	*/

}

void Sprite::Update(float deltaTime)
{
	//현재 프레임이 출력된후 흐른 시간
	_frameDuration += deltaTime;

	if (_frameList[_frameIdx]->GetFrameInterval() <=  _frameDuration)

		//if (0.1f <= _frameDuration) // 초당10프레임 애니메이션 
	{
		_frameDuration = 0.0f;
		_frameIdx++;
		if (_frameList.size() <= _frameIdx)
		{
			_frameIdx = 0;
		}
	}
}


void Sprite::Render()
{

	////2D이미지출력공간. Texture(텍스쳐,2d이미지 한장)
	//_spriteDX->Draw(
	//	_textureDX,		//그릴텍스쳐 정보가 들어있는 인터페이스
	//	&_textureRect,	// 원본이미지에서 그릴 부분	
	//	NULL,			
	//	NULL,
	//	_textureColor	//스프라이트의 색상과 알파채널
	//);		


	//_frame->Render();

	if (_frameIdx < _frameList.size())
	{
		_frameList[_frameIdx]->Render();
	}


}

void Sprite::Release()
{

}

void Sprite::Reset()
{
	//텍스쳐복구
	HRESULT hr = D3DXCreateTextureFromFileEx(_dxDevice,
		_fileName.c_str(),
		_texInfo.Width, _texInfo.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&_texInfo,
		NULL,
		&_textureDX);

	//_frame->Reset();
	for (int i = 0; i < _frameList.size(); i++)
	{
		_frameList[i]->Reset();
	}


}




