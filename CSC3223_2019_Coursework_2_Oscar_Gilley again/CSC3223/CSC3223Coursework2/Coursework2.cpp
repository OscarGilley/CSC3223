#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"

using namespace NCL;
using namespace CSC3223;

RenderObject* CreateCube(Renderer* renderer) {

	OGLShader* lightingShader = new OGLShader("LightingVertex.glsl", "LightingFragment.glsl");


	OGLMesh* m = new OGLMesh("Cube.msh");
	m->SetPrimitiveType(GeometryPrimitive::Triangles);
	
	std::vector<Vector4> vertexColours;
	for (int i = 0; i < 155; i++) {
		vertexColours.push_back(Vector4(1, 1, 1, 1));
	}

	m->SetVertexColours(vertexColours);
	m->UploadToGPU();

	Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -30));
	RenderObject* object = new RenderObject(m);
	

	TextureBase* destruction = OGLTexture::RGBATextureFromFilename("angerdoge.PNG");
	TextureBase* doge = OGLTexture::RGBATextureFromFilename("doge.PNG");
	object->SetBaseTexture(doge);
	object->SetSecondTexture(destruction);

	object->SetShader(lightingShader);
	

	renderer->AddRenderObject(object);

	renderer->SetLightProperties(Vector3(0, 0, 0),
		Vector3(0.831f, 0.686f, 0.216f), 100.0f);
	
	

	return object;
}

void ShrinkCube(RenderObject* cube) {
	OGLShader* shrinkShader = new OGLShader("VertexLightShrink.glsl", "RasterisationFragLight.glsl");
	cube->SetShader(shrinkShader);
	
}

void BlendTexture(RenderObject* cube) {
	OGLShader* blendShader = new OGLShader("RasterisationVertLight.glsl", "FragBlend.glsl");
	cube->SetShader(blendShader);
}

void FadeCube(RenderObject* cube) {
	OGLShader* fader = new OGLShader("RasterisationVertLight.glsl", "FragFade.glsl");
	cube->SetShader(fader);
}

RenderObject* AdvancedShader1(Renderer* renderer) {

	RenderObject* cube = CreateCube(renderer);

	OGLShader* newShader = new OGLShader(
		"VertexFocus.glsl",
		"FragFadeReverse.glsl",
		"GeometryPieces.glsl");

	

	cube->SetShader(newShader);

	return cube;
}

void AdvancedShader2(RenderObject* cube) {
	OGLShader* tessShader =
		new OGLShader("tessVert.glsl", "displaceFrag.glsl",
			"GeometrySwirl.glsl", "displaceTCSCW.glsl", "displaceTESCW.glsl");

	cube->SetShader(tessShader);
	
}

void AdvancedShader3(RenderObject* cube) {
	OGLShader* newShader = new OGLShader(
		"VertFallApart.glsl",
		"FragTexture.glsl",
		"GeometryFallApart.glsl");
	cube->SetShader(newShader);
}

int main() {
	Window* w = Window::CreateGameWindow("CSC3223 Coursework 2!");

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);
	glClearColor(0.99, 0.46, 0.32, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	RenderObject* cube = CreateCube(renderer);
	Vector3 viewPosition(0, 0, 0);

	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

	float rotation = 0.0f;

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();
		rotation += time * 30;
		renderer->Update(time);
		

		Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -10));

		modelMat = modelMat * Matrix4::Rotation(rotation, Vector3(1, 1, 1));

		cube->SetTransform(modelMat);

		renderer->DrawString("Press F1 to reset scene!", Vector2(10, 55));
		renderer->DrawString("Press F2, F3 and F4 for basic shaders!", Vector2(10, 40));
		renderer->DrawString("Press F5, F6 and F7 for advanced shaders!", Vector2(10, 25));
		renderer->DrawString("Reset after using advanced shaders! :)", Vector2(10, 10));

		renderer->EnableDepthBuffer(true);
		renderer->EnableAlphaBlending(true);
		renderer->SetBlendToLinear();
		renderer->Render();


		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
			viewPosition.x += 0.1f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			viewPosition.x -= 0.1f;
		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			viewPosition.y -= 0.1f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			viewPosition.y += 0.1f;

		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_Q)) {
			viewPosition.z -= 0.1f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_E)) {
			viewPosition.z += 0.1f;

		}


		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F1)) {
			renderer->DeleteAllRenderObjects();
			cube = CreateCube(renderer);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F2) || Window::GetKeyboard()->KeyPressed(KEYBOARD_Z)) {
			renderer->SetTime();
			ShrinkCube(cube);
			
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F3)) {
			renderer->SetTime();
			BlendTexture(cube);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F4)) {
			renderer->SetTime();
			FadeCube(cube);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F5)) {
			renderer->SetTime();
			renderer->DeleteAllRenderObjects();
			RenderObject* manyCubes = AdvancedShader1(renderer);
			
			modelMat = Matrix4::Translation(Vector3(0, 0, -6));
			manyCubes->SetTransform(modelMat);
			renderer->SetLightProperties(Vector3(0, 0, 0),
				Vector3(1.0f, 0.3f, 0.2f), 200.0f);
			
			
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F6)) {

			renderer->SetTime();
		
			renderer->DeleteAllRenderObjects();

			OGLShader* lightingShader = new OGLShader("LightingVertex.glsl", "LightingFragment.glsl");


			OGLMesh* m = new OGLMesh("Cube.msh");
			m->SetPrimitiveType(GeometryPrimitive::Patches);

			std::vector<Vector4> vertexColours;
			for (int i = 0; i < 155; i++) {
				vertexColours.push_back(Vector4(1, 1, 1, 1));
			}

			m->SetVertexColours(vertexColours);
			m->UploadToGPU();

			Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -10));
			RenderObject* patchCube = new RenderObject(m);
			patchCube->SetTransform(modelMat);


			TextureBase* destruction = OGLTexture::RGBATextureFromFilename("angerdoge.PNG");
			TextureBase* doge = OGLTexture::RGBATextureFromFilename("doge.PNG");
			patchCube->SetBaseTexture(doge);
			patchCube->SetSecondTexture(destruction);

			patchCube->SetShader(lightingShader);


			renderer->AddRenderObject(patchCube);

			renderer->SetLightProperties(Vector3(0, 0, 0),
				Vector3(1.0f, 0.3f, 0.2f), 200.0f);
			
			AdvancedShader2(patchCube);


		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F7)) {
			renderer->SetTime();
			AdvancedShader3(cube);
		}


		renderer->SetViewMatrix(Matrix4::Translation(viewPosition));
		w->SetTitle(std::to_string(time));
	}

	delete renderer;

	Window::DestroyGameWindow();
}