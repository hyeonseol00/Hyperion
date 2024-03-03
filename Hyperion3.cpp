//--------------------------------------------------------------------------------------
// File: Hyperion3.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUT.h"
#include "resource.h"
#include "stdafx.h"


//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
	if (pDeviceSettings->ver == DXUT_D3D9_DEVICE)
	{
		IDirect3D9* pD3D = DXUTGetD3D9Object();
		pDeviceSettings->d3d9.pp.FullScreen_RefreshRateInHz = 60;
	}

    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
	srand((unsigned)time(NULL));

	OBJMAN()->Init();
	FONMAN()->Init();
	SNDMAN()->Init();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	switch (GAAPP()->GetGameMode())
	{
	case GaApplication::INTRO:
		OBJMAN()->IntroUpdate();
		break;
	case GaApplication::MENU:
		OBJMAN()->MenuUpdate();
		break;
	case GaApplication::STAGE1:
		OBJMAN()->Stage1Update();
		break;
	case GaApplication::STAGE2:
		OBJMAN()->Stage2Update();
		break;
	case GaApplication::PAUSE:
		if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
		{
			switch (OBJMAN()->stagestate)
			{
			case ObjectManager::STAGE1:
				GAAPP()->SetGameMode(GaApplication::STAGE1);
				break;
			case ObjectManager::STAGE2:
				GAAPP()->SetGameMode(GaApplication::STAGE2);
				break;
			}
		}
	case GaApplication::GAMEOVER:
	case GaApplication::ENDING:
		OBJMAN()->InputInitial();
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			OBJMAN()->SetRanking();
			OBJMAN()->Release();
			OBJMAN()->Init();
			OBJMAN()->stagephase = ObjectManager::PHASE1;
			OBJMAN()->stagestate = ObjectManager::STAGE1;
			GAAPP()->SetGameMode(GaApplication::MENU);
			SNDMAN()->StopBGM();
		}
		break;
	}

	//		CHEAT KEY		//
	if (GetAsyncKeyState(VK_F4) & 0x0001)
	{
		OBJMAN()->Release();
		OBJMAN()->Init();
		GAAPP()->SetGameMode(GaApplication::MENU);
		SNDMAN()->StopBGM();
	}
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		OBJMAN()->Release();
		OBJMAN()->Init();
		GAAPP()->SetGameMode(GaApplication::STAGE1);
		OBJMAN()->stagestate = ObjectManager::STAGE1;
		SNDMAN()->PlayBGM();
	}
	if (GetAsyncKeyState(VK_F6) & 0x0001)
	{
		OBJMAN()->Release();
		OBJMAN()->Init();
		GAAPP()->SetGameMode(GaApplication::STAGE2);
		OBJMAN()->stagestate = ObjectManager::STAGE2;
		SNDMAN()->PlayBGM();
	}
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		//printf("%f\n", DXUTGetFPS());
		switch (GAAPP()->GetGameMode())
		{
		case GaApplication::INTRO:
			OBJMAN()->IntroRender();
			break;
		case GaApplication::MENU:
			OBJMAN()->MenuRender();
			break;
		case GaApplication::STAGE1:
			OBJMAN()->Stage1Render();
			break;
		case GaApplication::STAGE2:
			OBJMAN()->Stage2Render();
			break;
		case GaApplication::PAUSE:
		case GaApplication::GAMEOVER:
		case GaApplication::ENDING:
			switch (OBJMAN()->stagestate)
			{
			case ObjectManager::STAGE1:
				OBJMAN()->Stage1Render();
				break;
			case ObjectManager::STAGE2:
				OBJMAN()->Stage2Render();
				break;
			}
			break;
		}

        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
    return 0;
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
	OBJMAN()->Release();
	FONMAN()->Release();
}

void CALLBACK MouseProc(bool bM1Down, bool bM2Down,
						bool bM3Down, bool bM4Down,
						bool bM5Down, int iWhillDelta,
						int x, int y, void* pUserContext)
{
	if (GAAPP()->GetGameMode() == GaApplication::MENU)
		OBJMAN()->MenuMouseSate(bM1Down, x, y);
}

//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set the callback functions
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );
	DXUTSetCallbackMouse(MouseProc);

    // TODO: Perform any application-level initialization here

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
    DXUTInit( true, true ); // Parse the command line and show msgboxes
    DXUTSetHotkeyHandling( true, false, true );  // handle the default hotkeys
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"Hyperion3" );
    DXUTCreateDevice( false, SCREEN_WIDTH, SCREEN_HEIGHT );

	//PlaySound(L"Data\\ComputerVirusBattle.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);

    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here

    return DXUTGetExitCode();
}


