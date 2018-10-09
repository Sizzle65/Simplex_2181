#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(1.0f, C_WHITE);
	m_pMesh->GenerateCone(1.0f, 2.0f, 3, C_RED);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	static DWORD DStartingTime = GetTickCount();
	DWORD DCurrentTime = GetTickCount();
	DWORD DDelta = DCurrentTime - DStartingTime;
	float fTimer = static_cast<float>(DDelta / 1000.0f);
	//std::cout << "x : " << b_xSpin << std::endl;
	//std::cout << "y : " << b_ySpin << std::endl;
	//std::cout << "z : " << b_zSpin << "\n" << std::endl;

	float fTotalTime = 5.5f;

	float fPercent = MapValue(fTimer, 0.0f, fTotalTime, 0.0f, 1.0f);

	//static vector3 v3InitialPoint(0.0f, 0.0f, 0.0f);
	//static vector3 v3EndPoint(5.0f, 0.0f, 0.0f);

	//static float fStart = 0.0f;
	//static float fEnd = 180.0f;

	//float fCurrent = glm::lerp(fStart, fEnd, fPercent);
	//vector3 v3Position = glm::lerp(v3InitialPoint, v3EndPoint, fPercent);

	//matrix4 m4Rotation = glm::rotate(IDENTITY_M4, glm::radians(fCurrent), AXIS_Z);
	//matrix4 m4Position = glm::translate(m4Rotation, v3EndPoint);

	//New matrix transformation
	/*matrix4 m4RotX = glm::rotate(IDENTITY_M4, glm::radians(m_v3Angles.x), AXIS_X);
	matrix4 m4RotY = glm::rotate(IDENTITY_M4, glm::radians(m_v3Angles.y), AXIS_Y);
	matrix4 m4RotZ = glm::rotate(IDENTITY_M4, glm::radians(m_v3Angles.z), AXIS_Z);

	matrix4 m4Transform = m4RotX * m4RotY * m4RotZ;*/
	
	//glm::quat q1;
	quaternion q1 = glm::angleAxis(glm::radians(1.0f), m_v3Quat);
	static quaternion q2;
	q2 = q2 * q1;

	//Render in the new position
	
	//m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m4Transform);
	m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(q2));

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}