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
	// ���Ϸκ��� �̹����� �ʺ�� ���̸� ��´�
	hr = D3DXGetImageInfoFromFile(fileName.c_str(), &_texInfo);
	if (FAILED(hr))
	{
	return ;
	}
	//�̹��������� �ε�.
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
	//����� ��������
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
	//���� �������� ��µ��� �帥 �ð�
	_frameDuration += deltaTime;

	if (_frameList[_frameIdx]->GetFrameInterval() <=  _frameDuration)

		//if (0.1f <= _frameDuration) // �ʴ�10������ �ִϸ��̼� 
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

	////2D�̹�����°���. Texture(�ؽ���,2d�̹��� ����)
	//_spriteDX->Draw(
	//	_textureDX,		//�׸��ؽ��� ������ ����ִ� �������̽�
	//	&_textureRect,	// �����̹������� �׸� �κ�	
	//	NULL,			
	//	NULL,
	//	_textureColor	//��������Ʈ�� ����� ����ä��
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
	//�ؽ��ĺ���
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




