/****************************************************
*    Author: Tianhao Wang
*    Date:   2015-03-05   
*    Desc:   һ��ʹ��WASD�������ƶ��ķ��飬�޸���
*            һ����DrawLines�Ĵ��룬�������һЩ
*            ��������ڶ���ĺ�����
*****************************************************/  

#include "d3d9App.h"
#include "DirectInput.h"
#include <crtdbg.h>

class DrawLines : public d3d9App {
public:
    DrawLines(HINSTANCE hInstance, std::string winTitle, D3DDEVTYPE devType, DWORD vertexProc);
    ~DrawLines();

    void UpdateScene(float dt);
    void DrawScene();
private:
    ID3DXLine* m_pLine;
    D3DXVECTOR2* m_pLineArr;
    float m_squareSpeed;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, int)
{
    #if defined(DEBUG) | defined(_DEBUG)
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    DrawLines app(hInstance, "DrawLines", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
    g_pd3d9App = &app;
    // DISCL_NONEXCLUSIVE��ʾ�����豸���ᱻ�����ռ
    // DISCL_FOREGROUND��ʾ���ڲ��Ǵ����ö�״̬ʱ�������豸�����ݵ���Ϣ�����ᱻ��ȡ
    DirectInput dxInput(DISCL_NONEXCLUSIVE | DISCL_FOREGROUND,
                        DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    g_pDxInput = &dxInput;

    return g_pd3d9App->MsgLoop();
}

DrawLines::DrawLines(HINSTANCE hInstance, std::string winTitle, D3DDEVTYPE devType, DWORD vertexProc)
: d3d9App(hInstance, winTitle, devType, vertexProc)
{
    HR(D3DXCreateLine(g_pd3dDevice, &m_pLine));

    m_pLineArr = new D3DXVECTOR2[5];
    m_squareSpeed = 100;

    m_pLineArr[0].x = 100; m_pLineArr[0].y = 100;
    m_pLineArr[1].x = 100; m_pLineArr[1].y = 200;
    m_pLineArr[2].x = 200; m_pLineArr[2].y = 200;
    m_pLineArr[3].x = 200; m_pLineArr[3].y = 100;
    m_pLineArr[4].x = 100; m_pLineArr[4].y = 100;
}

DrawLines::~DrawLines()
{
    ReleaseCOM(m_pLine);
    delete m_pLineArr;
}

// ���·����λ��
void DrawLines::UpdateScene(float dt)
{
    g_pDxInput->GetCurState();

    if (g_pDxInput->KeyPress(DIK_A))
        for (int i = 0; i < 5; ++i)
            m_pLineArr[i].x -= 200.0f * dt;
    if (g_pDxInput->KeyPress(DIK_D))
        for (int i = 0; i < 5; ++i)
            m_pLineArr[i].x += 200.0f * dt;
    if (g_pDxInput->KeyPress(DIK_W))
        for (int i = 0; i < 5; ++i)
            m_pLineArr[i].y -= 200.0f * dt;
    if (g_pDxInput->KeyPress(DIK_S))
        for (int i = 0; i < 5; ++i)
            m_pLineArr[i].y += 200.0f * dt;
}

void DrawLines::DrawScene()
{
    HR(g_pd3dDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0));
    HR(g_pd3dDevice->BeginScene());
    HR(m_pLine->Draw(m_pLineArr, 5, D3DCOLOR_XRGB(0, 0, 0)));
    HR(g_pd3dDevice->EndScene());
    HR(g_pd3dDevice->Present(0, 0, 0, 0));
}