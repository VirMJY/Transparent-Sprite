#include "MyDirectX.h"
const string APPTITLE = "Animate Sprite Demo";
const int SCREENW = 1440;
const int SCREENH = 900;

LPDIRECT3DTEXTURE9 explosion = NULL;
int frame = 0;
int starttime = 0;

bool Game_Init(HWND window)
{
	//initialize Direct3D
	if (!Direct3D_Init(window, SCREENW, SCREENH, false))
	{
		MessageBox(0, "Error initializing Direct3D", "Error", NULL);
		return false;
	}
	//initialize DirectInput
	if (!DirectInput_Init(window))
	{
		MessageBox(0, "Error initializing DirectInput", "Error", NULL);
		return false;
	}
	//load explosion sprite
	explosion = LoadTexture("explosion_30_128.tga");
	if (!explosion)	return false;

	return true;
}

void Game_Run(HWND window)
{
	//make sure the Direct3D device is vaild
	if (!d3ddev)	return;
	//update input devices
	DirectInput_Update();

	//clear the backbuffer
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);
	//start rendering
	if (d3ddev->BeginScene())
	{
		//start drawing
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
		//animate and draw the sprite
		Sprite_Animate(frame, 0, 29, 1, starttime, 30);
		Sprite_Draw_Frame(explosion, 200, 200, frame, 128, 128, 6);
		//stop rendering
		spriteobj->End();

		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}

	//escape key exits
	if (Key_Down(DIK_SPACE) || Key_Down(DIK_ESCAPE))
		gameover = true;
	//controller back button also exits
	if (controllers[0].wButtons & XINPUT_GAMEPAD_BACK)
		gameover = true;
}

void Game_End()
{
	DirectInput_Shutdown();
	Direct3D_ShutDown();
	explosion->Release();
}