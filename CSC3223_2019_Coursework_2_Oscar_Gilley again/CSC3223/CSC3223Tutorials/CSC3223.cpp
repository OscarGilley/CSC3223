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
#include "RasterisationMesh.h"

using namespace NCL;
using namespace CSC3223;

void Tutorial1(Renderer* renderer) {
	OGLMesh* points = new OGLMesh();
	points->SetVertexPositions({ Vector3(50, 50, 0),
		Vector3(30, 10, 0), Vector3(200, 70, 0) });
	points->SetPrimitiveType(GeometryPrimitive::Points);
	points->UploadToGPU();
	renderer->AddRenderObject(new RenderObject(points));

	//defining a mesh for lines
	OGLMesh* lines = new OGLMesh();

	lines->SetVertexPositions({ Vector3(600, 50, 0),
		Vector3(680, 180, 0), Vector3(680, 50, 0), Vector3(600, 180, 0) });
	lines->SetPrimitiveType(GeometryPrimitive::Lines);
	lines->UploadToGPU();

	renderer->AddRenderObject(new RenderObject(lines));

	//defining a mesh for tris
	OGLMesh* tris = new OGLMesh();
	
	tris->SetVertexPositions({ Vector3(50, 450, 0),
		Vector3(250, 450, 0), Vector3(150, 350, 0) });
	tris->SetPrimitiveType(GeometryPrimitive::Triangles);
	tris->UploadToGPU();

	renderer->AddRenderObject(new RenderObject(tris));

	//defining a mesh for tri strip

	OGLMesh* triStrip = new OGLMesh();

	triStrip->SetVertexPositions({ Vector3(600, 450, 0),
		Vector3(700, 450, 0), Vector3(650, 350, 0), Vector3(750, 350, 0) });
	triStrip->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	triStrip->UploadToGPU();

	renderer->AddRenderObject(new RenderObject(triStrip));

}

void Tutorial2(Renderer* renderer) {
	//Normal OpenGL mesh in top left
	OGLMesh* lines = new OGLMesh();
	lines->SetVertexPositions({ Vector3(150, 50, 0),
		Vector3(180, 80, 0), Vector3(100, 200, 0), Vector3(150, 150, 0) });

	lines->SetVertexColours({ Vector4(1,0,0,1),
		Vector4(0,1,0,1), Vector4(0,0,1,1), Vector4(1,0,1,1) });

	lines->SetPrimitiveType(GeometryPrimitive::Lines);
	lines->UploadToGPU();
	renderer->AddRenderObject(new RenderObject(lines));

	OGLMesh* tris = new OGLMesh();
	tris->SetVertexPositions({ Vector3(550, 200, 0),
		Vector3(750, 200, 0), Vector3(650, 100, 0) });

	tris->SetVertexColours({ Vector4(1 ,0 ,0 ,1) ,
		Vector4(0 ,1 ,0 ,1) , Vector4(0 ,0 ,1 ,1) });

	tris->SetPrimitiveType(GeometryPrimitive::Triangles);
	tris->UploadToGPU();
	renderer->AddRenderObject(new RenderObject(tris));

	OGLMesh* rasterLine =
		(OGLMesh*)RasterisationMesh::CreateLineFromPoints(
			{ Vector3(150, 350, 0), Vector3(180, 380, 0), 
			Vector3(100, 500, 0), Vector3(150, 450, 0) }, 
			{ Vector4(1 , 0 , 0 , 1) , Vector4(0 , 1 , 0 , 1) ,
			Vector4(0 , 0 , 1 , 1) , Vector4(1 , 0 , 1 ,1) },
			false);
	renderer->AddRenderObject(new RenderObject(rasterLine));

	OGLMesh* rasterTri =
		(OGLMesh*)RasterisationMesh::CreateTriangleFromPoints(
		{ Vector3(550, 400, 0), Vector3(750, 380, 0), Vector3(650, 300, 0) },
		{ Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) });
		renderer->AddRenderObject(new RenderObject(rasterTri));

}

void Tutorial4(Renderer* r) {
	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(
		{ Vector3(-1 , 0 , 0) , Vector3(1 , 0 , 0) , Vector3(0 , 1 , 0) });
	tri->SetVertexColours(
		{ Vector4(1 ,0 ,0 ,1) , Vector4(0 ,1 ,0 ,1) , Vector4(0 ,0 ,1 ,1) });
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 5; ++x) {
			Matrix4 translate = Matrix4::Translation(
				Vector3((x + 1) * 130, (y + 1) * 120, 0));
			Matrix4 rotate = Matrix4::Rotation(((y * 5) + x) * 10, Vector3(0, 0, 1));
			Matrix4 scale = Matrix4::Scale(Vector3(50, 50, 50) / (1 + y));
			Matrix4 modelMat = translate * rotate * scale;
			r->AddRenderObject(new RenderObject(tri, modelMat));
		}
	}
}

void Tutorial5(Renderer* renderer){
	OGLMesh* tri = new OGLMesh("Cube.msh");
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	for (int y = -4; y < 3; ++y){
		for (int x = -4; x < 3; ++x) {
			float zAmount = rand() % 30;
			float scaleAmount = ((rand() % 3) + 1);

			Matrix4 translate = Matrix4::Translation(
				Vector3((x + 1) * 10, (y + 1) * 10, -50 - zAmount));
			Matrix4 rotate = Matrix4::Rotation(
				((y * 5) + x) * 10, Vector3(0, 0, 1));

			Matrix4 scale = Matrix4::Scale(
				Vector3(scaleAmount, scaleAmount, scaleAmount));

			renderer->AddRenderObject(new RenderObject(tri,
				translate * rotate * scale));
			
		}
	}
}

void Tutorial6(Renderer* renderer) {
	std::vector<Vector4> red =
	{ Vector4(1,0,0,1), Vector4(1,0,0,1), Vector4(1,0,0,1) };
	std::vector<Vector4> blue =
	{ Vector4(0,0,1,1), Vector4(0,0,1,1), Vector4(0,0,1,1) };

	std::vector<Vector3> verts =
	{ Vector3(-1,-1,0), Vector3(1, -1, 0), Vector3(0,1,0) };

	OGLMesh* redTri = new OGLMesh();
	redTri->SetVertexPositions(verts);
	redTri->SetVertexColours(red);
	redTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	redTri->UploadToGPU();

	OGLMesh* blueTri = new OGLMesh();
	blueTri->SetVertexPositions(verts);
	blueTri->SetVertexColours(blue);
	blueTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	blueTri->UploadToGPU();

	Matrix4 redModelMat = Matrix4::Translation(Vector3(0, 0, -30)) *
		Matrix4::Scale(Vector3(5, 5, 5));

	Matrix4 blueModelMat = Matrix4::Translation(Vector3(0, 0, -70)) *
		Matrix4::Scale(Vector3(15, 15, 15));

	renderer->AddRenderObject(new RenderObject(redTri, redModelMat));
	renderer->AddRenderObject(new RenderObject(blueTri, blueModelMat));

	
}

void Tutorial7(Renderer* renderer) {
	std::vector<Vector3> verts = {
		Vector3(-1,-1,0), Vector3(1,-1,0), Vector3(0,1,0) };

	std::vector<Vector4> white = {
		Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) };

	std::vector<Vector2> texCoords = {
		Vector2(0,0), Vector2(10, 0), Vector2(5, 10) };

	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(verts);
	tri->SetVertexColours(white);
	tri->SetVertexTextureCoords(texCoords);
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -70)) *
		Matrix4::Rotation(45.0f, Vector3(1,0,0)) *
		Matrix4::Scale(Vector3(15, 15, 15));

	RenderObject* renderObj = new RenderObject(tri, modelMat);
	TextureBase* newTex = OGLTexture::RGBATextureFromFilename("NCL.PNG");
	renderer->EnableBilinearFiltering(*(OGLTexture*)newTex);
	renderer->EnableTextureRepeating(*(OGLTexture*)newTex, false, false);

	renderObj->SetBaseTexture(newTex);
	renderer->AddRenderObject(renderObj);
}

void Tutorial8(Renderer* renderer) {
	std::vector<Vector4> red =
	{ Vector4(1,0,0,0.25), Vector4(1,0,0,0.33), Vector4(1,0,0,0.5) };
	std::vector<Vector4> blue =
	{ Vector4(0,0,1,0.75), Vector4(0,0,1,0.75), Vector4(0,0,1,0.75) };

	std::vector<Vector3> verts =
	{ Vector3(-1,-1,0), Vector3(1, -1, 0), Vector3(0,1,0) };

	OGLMesh* redTri = new OGLMesh();
	redTri->SetVertexPositions(verts);
	redTri->SetVertexColours(red);
	redTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	redTri->UploadToGPU();

	OGLMesh* blueTri = new OGLMesh();
	blueTri->SetVertexPositions(verts);
	blueTri->SetVertexColours(blue);
	blueTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	blueTri->UploadToGPU();

	Matrix4 redModelMat = Matrix4::Translation(Vector3(0, 0, -30)) *
		Matrix4::Scale(Vector3(5, 5, 5));

	Matrix4 blueModelMat = Matrix4::Translation(Vector3(0, 0, -70)) *
		Matrix4::Scale(Vector3(15, 15, 15));

	renderer->AddRenderObject(new RenderObject(blueTri, blueModelMat));
	renderer->AddRenderObject(new RenderObject(redTri, redModelMat));
	

}

void Tutorial9(Renderer* renderer) {
	std::vector<Vector4> rgb = {
		Vector4(1,0,0,1), Vector4(0,1,0,1), Vector4(0,0,1,1) };

	std::vector<Vector3> verts = {
		Vector3(-1,-1,0), Vector3(1,-1,0), Vector3(0,1,0) };

	OGLMesh* triMesh = new OGLMesh();
	triMesh->SetVertexPositions(verts);
	triMesh->SetVertexColours(rgb);
	triMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	triMesh->UploadToGPU();

	Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -30)) *
		Matrix4::Scale(Vector3(5, 5, 5));

	OGLShader* newShader = new OGLShader("VertexFocus.glsl",
		"RasterisationFrag.glsl");

	RenderObject* object = new RenderObject(triMesh, modelMat);

	object->SetShader(newShader);
	renderer->AddRenderObject(object);
}

void Tutorial10(Renderer* renderer) {

	std::vector<Vector4> rgb = {
		Vector4(1,0,0,1), Vector4(0,1,0,1), Vector4(0,0,1,1) };

	std::vector<Vector3> verts = {
		Vector3(-1,-1,0), Vector3(1,-1,0), Vector3(0,1,0) };

	OGLMesh* triMesh = new OGLMesh();
	triMesh->SetVertexPositions(verts);
	triMesh->SetVertexColours(rgb);
	triMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	triMesh->UploadToGPU();

	Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -30)) *
		Matrix4::Scale(Vector3(5, 5, 5));

	OGLShader* newShader = new OGLShader("VertexFocus.glsl", "ScreenColourFrag.glsl");

	RenderObject* object = new RenderObject(triMesh, modelMat);

	object->SetShader(newShader);
	renderer->AddRenderObject(object);

	std::vector<Vector3> smileyVerts = {
		Vector3(1,1,0), Vector3(-1,-1,0), Vector3(1,-1,0),
		Vector3(1,1,0), Vector3(-1,1,0), Vector3(-1,-1,0) };

	std::vector<Vector2> smileyTexCoords = {
		Vector2(1,1), Vector2(0,0), Vector2(1,0),
		Vector2(1,1), Vector2(0,1), Vector2(0,0) };

	OGLMesh* squareMesh = new OGLMesh();
	squareMesh->SetVertexPositions(smileyVerts);
	squareMesh->SetVertexTextureCoords(smileyTexCoords);

	squareMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	squareMesh->UploadToGPU();

	Matrix4 smileyModel = Matrix4::Translation(Vector3(0, 0, -30)) *
		Matrix4::Scale(Vector3(5, 5, 5));

	OGLShader* smileyShader = new OGLShader("RasterisationVert.glsl",
		"SmileyStaticFrag.glsl");

	RenderObject* smileyObject = new RenderObject(squareMesh, smileyModel);

	smileyObject->SetBaseTexture(
		OGLTexture::RGBATextureFromFilename("smileyface.png"));
	smileyObject->SetSecondTexture(
		OGLTexture::RGBATextureFromFilename("Static.png"));
	smileyObject->SetShader(smileyShader);

	renderer->AddRenderObject(smileyObject);

}

void Tutorial11(Renderer* renderer) {
	std::vector<Vector3> verts;
	std::vector<Vector4> colours;
	
	for (int i = 0; i < 100; ++i) {
		float x = (float)(rand() % 100 - 50);
		float y = (float)(rand() % 100 - 50);
		float z = (float)(rand() % 100 - 50);
		Vector4 colour = {1 , 1 , 1 , 1 };
		verts.push_back(Vector3(x, y, z));
		colours.push_back(colour);
	}

	OGLMesh* pointSprites = new OGLMesh();
	pointSprites->SetVertexPositions(verts);
	pointSprites->SetVertexColours(colours);
	pointSprites->SetPrimitiveType(GeometryPrimitive::Points);
	pointSprites->UploadToGPU();

	Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -30));

	OGLShader* newShader = new OGLShader(
		"RasterisationVert.glsl",
		"RasterisationFrag.glsl",
		"GeometryPieces.glsl");
	
	RenderObject* object = new RenderObject(pointSprites, modelMat);

	object->SetBaseTexture(OGLTexture::RGBATextureFromFilename("nyan.png"));
	object->SetShader(newShader);

	renderer->AddRenderObject(object);
}

void Tutorial12(Renderer* renderer) {
	std::vector<Vector3> verts = {
		Vector3(-1.0f, -1.0f, 0.0f), Vector3(-1.0f, 1.0f, 0.0f),
		Vector3(1.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f)
	};
	std::vector<Vector2> texCoords = {
		Vector2(0.0f, 1.0f), Vector2(0.0f, 0.0f),
		Vector2(1.0f, 1.0f), Vector2(1.0f, 0.0f)
	};

	OGLMesh* tessMesh = new OGLMesh();
	tessMesh->SetVertexPositions(verts);
	tessMesh->SetVertexTextureCoords(texCoords);
	tessMesh->SetPrimitiveType(GeometryPrimitive::Patches);
	tessMesh->UploadToGPU();

	TextureBase* noiseTex =
		OGLTexture::RGBATextureFromFilename("perlin_noise.PNG");

	OGLShader* tessShader =
		new OGLShader("tessVert.glsl", "displaceFrag.glsl",
			"", "displaceTCS.glsl", "displaceTES.glsl");

	RenderObject* tessObject = new RenderObject(tessMesh);
	tessObject->SetBaseTexture(noiseTex);
	tessObject->SetShader(tessShader);

	Matrix4 modelMat = Matrix4::Rotation(90, Vector3(1, 0, 0)) *
		Matrix4::Scale(Vector3(20, 20, 20));

	tessObject->SetTransform(modelMat);

	glPatchParameteri(GL_PATCH_VERTICES, 4);

	renderer->AddRenderObject(tessObject);

	renderer->SetViewMatrix(
		Matrix4::Rotation(70.0f, Vector3(1, 0, 0)) *
		Matrix4::Rotation(-225.0f, Vector3(0, 1, 0)) *
		Matrix4::Translation(Vector3(20, -100, 20)));
}

RenderObject* Tutorial13(Renderer* renderer) {
	OGLShader* lightingShader = new OGLShader("LightingVertex.glsl", "LightingFragment.glsl");

	OGLMesh* cubeMesh = new OGLMesh("cube.msh");
	cubeMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	cubeMesh->UploadToGPU();

	RenderObject* cubeObject = new RenderObject(cubeMesh);
	cubeObject->SetShader(lightingShader);

	TextureBase* tex = OGLTexture::RGBATextureFromFilename("doge.PNG");
	cubeObject->SetBaseTexture(tex);
	renderer->AddRenderObject(cubeObject);

	renderer->SetLightProperties(Vector3(0, 0, 0),
		Vector3(1.0f, 0.3f, 0.2f), 200.0f);

	OGLMesh* triMesh = new OGLMesh();

	std::vector<Vector3> verts =
	{ Vector3(-1,-1,0), Vector3(1,-1,0), Vector3(0,1,0) };
	std::vector<Vector3> normals;

	for (int i = 0; i < verts.size(); i += 3) {
		Vector3& a = verts[i];
		Vector3& b = verts[i + 1];
		Vector3& c = verts[i + 2];

		Vector3 normal = Vector3::Cross(b - a, c - a);
		normal.Normalise();

		normals.emplace_back(normal);
		normals.emplace_back(normal);
		normals.emplace_back(normal);

		triMesh->SetVertexPositions(verts);
		triMesh->SetVertexNormals(normals);

		triMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
		triMesh->UploadToGPU();

		Matrix4 triMat = Matrix4::Translation(Vector3(20, 0, -70)) * Matrix4::Rotation(-10.0f, Vector3(1, 0, 0)) *
			Matrix4::Rotation(-15.0f, Vector3(0, 1, 0)) *
			Matrix4::Scale(Vector3(15, 15, 15));

		RenderObject* triObject = new RenderObject(triMesh, triMat);
		triObject->SetShader(lightingShader);

		renderer->AddRenderObject(triObject);
	}

	return cubeObject;
}

int main() {

	Window*w = Window::CreateGameWindow("CSC3223 Tutorials!");

	if (!w->HasInitialised()) {
		return -1;
	}
	
	Renderer* renderer = new Renderer(*w);

	/*
	float currentWidth = Window::GetWindow()->GetScreenSize().x;
	float currentHeight = Window::GetWindow()->GetScreenSize().y;
	Matrix4 mat = Matrix4::Orthographic(-2, -1,
		currentWidth * 0.5f, -currentWidth * 0.5f,
		-currentHeight * 0.5f, currentHeight * 0.5f);

	renderer->SetProjectionMatrix(mat);
	*/

	float aspect = w->GetScreenAspect();
	Matrix4 proj = Matrix4::Perspective(1.0f, 100.0f, aspect, 60.0f);
	renderer->SetProjectionMatrix(proj);
	

	Tutorial11(renderer);
	Vector3 viewPosition(0, 0, 0);
	//RenderObject* litCube = Tutorial13(renderer);

	renderer->SetProjectionMatrix(
		Matrix4::Perspective(1, 100, w->GetScreenAspect(), 45.0f));

	float rotation = 0.0f;

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		renderer->EnableDepthBuffer(true);

		float time = w->GetTimer()->GetTimeDelta();
		
		rotation += time * 0.1f;

		//litCube->SetTransform(
		//	Matrix4::Translation(Vector3(-25, 0, -70)) *
		//	Matrix4::Rotation(rotation, Vector3(1, 1, 1)) *
		//	Matrix4::Scale(Vector3(6, 6, 6))
		//);


		//end of tutorial13

		renderer->Update(time);
		renderer->EnableAlphaBlending(true);
		renderer->SetBlendToLinear();

		renderer->DrawString("can i get a memory fault!", Vector2(10, 10));

		renderer->Render();

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F11)) {
			renderer->WriteDepthBuffer("Depth.png");
		}

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

		if (Window::GetKeyboard() -> KeyDown(KEYBOARD_A)) {
			viewPosition.x += 1.0f;
			
		}
		if (Window::GetKeyboard() -> KeyDown(KEYBOARD_D)) {
			viewPosition.x -= 1.0f;
			
		}
		
		if (Window::GetKeyboard() -> KeyDown(KEYBOARD_W)) {
			viewPosition.y -= 1.0f;
			
		}
		if (Window::GetKeyboard() -> KeyDown(KEYBOARD_S)) {
			viewPosition.y += 1.0f;
			
		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_Q)) {
			viewPosition.z -= 1.0f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_E)) {
			viewPosition.z += 1.0f;

		}
		
		renderer -> SetViewMatrix(Matrix4::Translation(viewPosition));


		w->SetTitle(std::to_string(time));
	}

	delete renderer;

	Window::DestroyGameWindow();
}