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

void Starfield(Renderer* r) {

	OGLMesh* points = new OGLMesh;
	points->SetVertexPositions({ Vector3(10,10,-50), Vector3(10,10,-50), Vector3(10,10,-50) });
	points->SetVertexColours({ Vector4(0.6,0.7,1,1), Vector4(0.6,0.7,1,1), Vector4(0.6,0.7,1,1) });
	points->SetPrimitiveType(GeometryPrimitive::Points);
	points->UploadToGPU();

	//points->SetVertexPositions({ Vector3(0,0,0) });
	for (int y = 0; y < 10000; ++y) {
	
			Matrix4 translate = Matrix4::Translation(
				Vector3(rand() % 2000 - 1000, rand() % 2000 - 1000, rand() % 2000 - 1000));
			
			r->AddRenderObject(new RenderObject(points, translate));
		
	}
}

RenderObject* Sphere() {
	
	OGLMesh* sphere = new OGLMesh("Sphere.msh");
	std::vector <Vector4> vertexColours;

	for (int i = 0; i < 100; i++) {
		vertexColours.push_back(Vector4(0, 0, 1, 1));
	}
	
	sphere->SetVertexColours(vertexColours);
	
	sphere->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	sphere->UploadToGPU();
	Matrix4 translate = Matrix4::Translation(
		Vector3(-100, -100, -100));
	Matrix4 rotate = Matrix4::Rotation(
		((3 * 5) + 2) * 10, Vector3(0, 0, 1));

	Matrix4 scale = Matrix4::Scale(
		Vector3(30, 30, 30));

	RenderObject* rsphere = new RenderObject(sphere, translate * rotate * scale);
	return rsphere;
}

void Planetoid(Renderer* r) {
	OGLMesh* planetoid = new OGLMesh();
	planetoid->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	planetoid->SetVertexPositions({ Vector3(85, 90, 55),
		Vector3(70, 70, 70), Vector3(70, 70, 40), Vector3(100, 70, 40), Vector3(100, 70, 70), Vector3(70,70,70), Vector3(70,70,40) });
	
	OGLMesh* planetoidBase = new OGLMesh();
	planetoidBase->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	planetoidBase->SetVertexPositions({ Vector3(85, 50 , 55),
		Vector3(70, 70, 70), Vector3(70, 70, 40), Vector3(100, 70, 40), Vector3(100, 70, 70),
		Vector3(70,70,70), Vector3(70,70,40) });
	
	planetoid->SetVertexColours({ Vector4(1,0,0,0.4), Vector4(0,1,0,0.4), Vector4(0,0,1,0.4), Vector4(0,0,1,0.4), Vector4(0,1,0,0.4), Vector4(1,0,0,0.4), Vector4(0,1,0,0.4) });
	planetoidBase->SetVertexColours({ Vector4(1,0,0,0.6), Vector4(0,1,0,0.6), Vector4(0,0,1,0.6), Vector4(0,0,1,0.6), Vector4(0,1,0,0.6), Vector4(1,0,0,0.6), Vector4(0,1,0,0.6) });

	planetoid->UploadToGPU();
	planetoidBase->UploadToGPU();

	r->AddRenderObject(new RenderObject(planetoid));
	r->AddRenderObject(new RenderObject(planetoidBase));
}

RenderObject* Pyramid() {
	OGLMesh* pyramid = new OGLMesh();
	pyramid->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	pyramid->SetVertexPositions({ Vector3(185, 190, 155),
		Vector3(170, 170, 170), Vector3(170, 170, 140), Vector3(200, 170, 140), Vector3(200, 170, 170), Vector3(170,170,170), Vector3(170,170,140) });

	pyramid->SetVertexColours({ Vector4(1,0,0,0.5), Vector4(0,1,0,0.5), Vector4(0,0,1,0.8), Vector4(0,0,1,0.8), Vector4(0,1,0,0.8), Vector4(1,0,0,0.5), Vector4(0,1,0,0.5) });
	pyramid->UploadToGPU();
	RenderObject* rpyramid = new RenderObject(pyramid);
	return rpyramid;
	
}

//this function is very large since the ufo is made out of normal triangles...
//a fan would make it really efficient!
void Spaceship(Renderer* r) {

	Matrix4 translate = Matrix4::Translation(
		Vector3(200, 200, 200));
	Matrix4 rotate = Matrix4::Rotation(90, Vector3(1, 0, 0));

	Matrix4 scale = Matrix4::Scale(
		Vector3(2, 2, 2));

	std::vector<Vector2> texCoords = {
		Vector2(0,0), Vector2(1,0), Vector2(0.5, 1) };

	TextureBase* nclTex = OGLTexture::RGBATextureFromFilename("NCL.PNG");


	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions({ Vector3(12,12,-50), Vector3(20,20,-45), Vector3(16,8,-50) });
	tri->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri->SetVertexTextureCoords(texCoords);
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();
	RenderObject* rtri = new RenderObject(tri, translate * rotate * scale);
	rtri->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri);

	OGLMesh* tri2 = new OGLMesh();
	tri2->SetVertexPositions({ Vector3(10,18,-50), Vector3(20,20,-45), Vector3(12,12,-50) });
	tri2->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri2->SetVertexTextureCoords(texCoords);
	tri2->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri2->UploadToGPU();
	RenderObject* rtri2 = new RenderObject(tri2, translate * rotate * scale);
	rtri2->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri2);

	OGLMesh* tri3 = new OGLMesh();
	tri3->SetVertexPositions({ Vector3(12,24,-50), Vector3(20,20,-45), Vector3(10,18,-50) });
	tri3->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri3->SetVertexTextureCoords(texCoords);
	tri3->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri3->UploadToGPU();
	RenderObject* rtri3 = new RenderObject(tri3, translate * rotate * scale);
	rtri3->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri3);

	OGLMesh* tri4 = new OGLMesh();
	tri4->SetVertexPositions({ Vector3(16,28,-50), Vector3(20,20,-45), Vector3(12,24,-50) });
	tri4->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri4->SetVertexTextureCoords(texCoords);
	tri4->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri4->UploadToGPU();
	RenderObject* rtri4 = new RenderObject(tri4, translate * rotate * scale);
	rtri4->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri4);

	OGLMesh* tri5 = new OGLMesh();
	tri5->SetVertexPositions({ Vector3(20,30,-50), Vector3(20,20,-45), Vector3(16,28,-50) });
	tri5->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri5->SetVertexTextureCoords(texCoords);
	tri5->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri5->UploadToGPU();
	RenderObject* rtri5 = new RenderObject(tri5, translate * rotate * scale);
	rtri5->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri5);

	OGLMesh* tri6 = new OGLMesh();
	tri6->SetVertexPositions({ Vector3(26,30,-50), Vector3(20,20,-45), Vector3(20,30,-50) });
	tri6->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri6->SetVertexTextureCoords(texCoords);
	tri6->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri6->UploadToGPU();
	RenderObject* rtri6 = new RenderObject(tri6, translate * rotate * scale);
	rtri6->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri6);

	OGLMesh* tri7 = new OGLMesh();
	tri7->SetVertexPositions({ Vector3(30,26,-50), Vector3(20,20,-45), Vector3(26,30,-50) });
	tri7->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri7->SetVertexTextureCoords(texCoords);
	tri7->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri7->UploadToGPU();
	RenderObject* rtri7 = new RenderObject(tri7, translate * rotate * scale);
	rtri7->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri7);

	OGLMesh* tri8 = new OGLMesh();
	tri8->SetVertexPositions({ Vector3(32,20,-50), Vector3(20,20,-45), Vector3(30,26,-50) });
	tri8->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri8->SetVertexTextureCoords(texCoords);
	tri8->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri8->UploadToGPU();
	RenderObject* rtri8 = new RenderObject(tri8, translate * rotate * scale);
	rtri8->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri8);

	OGLMesh* tri9 = new OGLMesh();
	tri9->SetVertexPositions({ Vector3(30,15,-50), Vector3(20,20,-45), Vector3(32,20,-50) });
	tri9->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri9->SetVertexTextureCoords(texCoords);
	tri9->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri9->UploadToGPU();
	RenderObject* rtri9 = new RenderObject(tri9, translate * rotate * scale);
	rtri9->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri9);

	OGLMesh* tri10 = new OGLMesh();
	tri10->SetVertexPositions({ Vector3(28,10,-50), Vector3(20,20,-45), Vector3(30,15,-50) });
	tri10->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri10->SetVertexTextureCoords(texCoords);
	tri10->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri10->UploadToGPU();
	RenderObject* rtri10 = new RenderObject(tri10, translate * rotate * scale);
	rtri10->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri10);

	OGLMesh* tri11 = new OGLMesh();
	tri11->SetVertexPositions({ Vector3(24,8,-50), Vector3(20,20,-45), Vector3(28,10,-50) });
	tri11->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri11->SetVertexTextureCoords(texCoords);
	tri11->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri11->UploadToGPU();
	RenderObject* rtri11 = new RenderObject(tri11, translate * rotate * scale);
	rtri11->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri11);

	OGLMesh* tri12 = new OGLMesh();
	tri12->SetVertexPositions({ Vector3(16,8,-50), Vector3(20,20,-45), Vector3(24,8,-50) });
	tri12->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri12->SetVertexTextureCoords(texCoords);
	tri12->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri12->UploadToGPU();
	RenderObject* rtri12 = new RenderObject(tri12, translate * rotate * scale);
	rtri12->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri12);


	//BOTTOM HALF

	OGLMesh* tri13 = new OGLMesh();
	tri13->SetVertexPositions({ Vector3(12,12,-50), Vector3(20,20,-55), Vector3(16,8,-50) });
	tri13->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri13->SetVertexTextureCoords(texCoords);
	tri13->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri13->UploadToGPU();
	RenderObject* rtri13 = new RenderObject(tri13, translate * rotate * scale);
	rtri13->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri13);

	OGLMesh* tri14 = new OGLMesh();
	tri14->SetVertexPositions({ Vector3(10,18,-50), Vector3(20,20,-55), Vector3(12,12,-50) });
	tri14->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri14->SetVertexTextureCoords(texCoords);
	tri14->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri14->UploadToGPU();
	RenderObject* rtri14 = new RenderObject(tri14, translate * rotate * scale);
	rtri14->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri14);

	OGLMesh* tri15 = new OGLMesh();
	tri15->SetVertexPositions({ Vector3(12,24,-50), Vector3(20,20,-55), Vector3(10,18,-50) });
	tri15->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri15->SetVertexTextureCoords(texCoords);
	tri15->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri15->UploadToGPU();
	RenderObject* rtri15 = new RenderObject(tri15, translate * rotate * scale);
	rtri15->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri15);

	OGLMesh* tri16 = new OGLMesh();
	tri16->SetVertexPositions({ Vector3(16,28,-50), Vector3(20,20,-55), Vector3(12,24,-50) });
	tri16->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri16->SetVertexTextureCoords(texCoords);
	tri16->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri16->UploadToGPU();
	RenderObject* rtri16 = new RenderObject(tri16, translate * rotate * scale);
	rtri16->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri16);

	OGLMesh* tri17 = new OGLMesh();
	tri17->SetVertexPositions({ Vector3(20,30,-50), Vector3(20,20,-55), Vector3(16,28,-50) });
	tri17->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri17->SetVertexTextureCoords(texCoords);
	tri17->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri17->UploadToGPU();
	RenderObject* rtri17 = new RenderObject(tri17, translate * rotate * scale);
	rtri17->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri17);

	OGLMesh* tri18 = new OGLMesh();
	tri18->SetVertexPositions({ Vector3(26,30,-50), Vector3(20,20,-55), Vector3(20,30,-50) });
	tri18->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri18->SetVertexTextureCoords(texCoords);
	tri18->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri18->UploadToGPU();
	RenderObject* rtri18 = new RenderObject(tri18, translate * rotate * scale);
	rtri18->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri18);

	OGLMesh* tri19 = new OGLMesh();
	tri19->SetVertexPositions({ Vector3(30,26,-50), Vector3(20,20,-55), Vector3(26,30,-50) });
	tri19->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri19->SetVertexTextureCoords(texCoords);
	tri19->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri19->UploadToGPU();
	RenderObject* rtri19 = new RenderObject(tri19, translate * rotate * scale);
	rtri19->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri19);

	OGLMesh* tri25 = new OGLMesh();
	tri25->SetVertexPositions({ Vector3(31,23,-50), Vector3(20,20,-55), Vector3(30,26,-50) });
	tri25->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri25->SetVertexTextureCoords(texCoords);
	tri25->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri25->UploadToGPU();
	RenderObject* rtri25 = new RenderObject(tri25, translate * rotate * scale);
	rtri25->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri25);

	OGLMesh* tri20 = new OGLMesh();
	tri20->SetVertexPositions({ Vector3(32,20,-50), Vector3(20,20,-55), Vector3(31,23,-50) });
	tri20->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri20->SetVertexTextureCoords(texCoords);
	tri20->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri20->UploadToGPU();
	RenderObject* rtri20 = new RenderObject(tri20, translate * rotate * scale);
	rtri20->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri20);

	OGLMesh* tri21 = new OGLMesh();
	tri21->SetVertexPositions({ Vector3(30,15,-50), Vector3(20,20,-55), Vector3(32,20,-50) });
	tri21->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri21->SetVertexTextureCoords(texCoords);
	tri21->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri21->UploadToGPU();
	RenderObject* rtri21 = new RenderObject(tri21, translate * rotate * scale);
	rtri21->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri21);

	OGLMesh* tri22 = new OGLMesh();
	tri22->SetVertexPositions({ Vector3(28,10,-50), Vector3(20,20,-55), Vector3(30,15,-50) });
	tri22->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri22->SetVertexTextureCoords(texCoords);
	tri22->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri22->UploadToGPU();
	RenderObject* rtri22 = new RenderObject(tri22, translate * rotate * scale);
	rtri22->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri22);

	OGLMesh* tri23 = new OGLMesh();
	tri23->SetVertexPositions({ Vector3(24,8,-50), Vector3(20,20,-55), Vector3(28,10,-50) });
	tri23->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri23->SetVertexTextureCoords(texCoords);
	tri23->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri23->UploadToGPU();
	RenderObject* rtri23 = new RenderObject(tri23, translate * rotate * scale);
	rtri23->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri23);

	OGLMesh* tri24 = new OGLMesh();
	tri24->SetVertexPositions({ Vector3(16,8,-50), Vector3(20,20,-55), Vector3(24,8,-50) });
	tri24->SetVertexColours({ Vector4(1,1,1,1), Vector4(1,1,1,1), Vector4(1,1,1,1) });
	tri24->SetVertexTextureCoords(texCoords);
	tri24->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri24->UploadToGPU();
	RenderObject* rtri24 = new RenderObject(tri24, translate * rotate * scale);
	rtri24->SetBaseTexture(nclTex);
	r->AddRenderObject(rtri24);

	//ufo dome

	OGLMesh* ufoDome1 = new OGLMesh();
	ufoDome1->SetVertexPositions({ Vector3(17, 17, -52), Vector3(20, 20, -58), Vector3(17, 24, -52) });
	ufoDome1->SetVertexColours({ Vector4(0.5, 0.8, 1, 1), Vector4(0.5, 0.8, 1, 1), Vector4(0.5, 0.8, 1, 1) });
	ufoDome1->SetPrimitiveType(GeometryPrimitive::Triangles);
	ufoDome1->UploadToGPU();
	RenderObject* rufoDome1 = new RenderObject(ufoDome1, translate * rotate * scale);
	r->AddRenderObject(rufoDome1);

	OGLMesh* ufoDome2 = new OGLMesh();
	ufoDome2->SetVertexPositions({ Vector3(17, 24, -52), Vector3(20, 20, -58), Vector3(24, 24, -52) });
	ufoDome2->SetVertexColours({ Vector4(0.5, 0.8, 1, 1), Vector4(0.5, 0.8, 1, 1), Vector4(0.5, 0.8, 1, 1) });
	ufoDome2->SetPrimitiveType(GeometryPrimitive::Triangles);
	ufoDome2->UploadToGPU();
	RenderObject* rufoDome2 = new RenderObject(ufoDome2, translate * rotate * scale);
	r->AddRenderObject(rufoDome2);

	OGLMesh* ufoDome3 = new OGLMesh();
	ufoDome3->SetVertexPositions({ Vector3(24, 24, -52), Vector3(20, 20, -58), Vector3(24, 17, -52) });
	ufoDome3->SetVertexColours({ Vector4(0.5, 0.8, 1, 1), Vector4(0.5, 0.8, 1, 1), Vector4(0.5, 0.8, 1, 1) });
	ufoDome3->SetPrimitiveType(GeometryPrimitive::Triangles);
	ufoDome3->UploadToGPU();
	RenderObject* rufoDome3 = new RenderObject(ufoDome3, translate * rotate * scale);
	r->AddRenderObject(rufoDome3);

	OGLMesh* ufoDome4 = new OGLMesh();
	ufoDome4->SetVertexPositions({ Vector3(24, 17, -52), Vector3(20, 20, -58), Vector3(17, 17, -52) });
	ufoDome4->SetVertexColours({ Vector4(0.5, 0.8, 1, 1), Vector4(0.5, 0.8, 1, 1), Vector4(0.5, 0.8, 1, 1) });
	ufoDome4->SetPrimitiveType(GeometryPrimitive::Triangles);
	ufoDome4->UploadToGPU();
	RenderObject* rufoDome4 = new RenderObject(ufoDome4, translate * rotate * scale);
	r->AddRenderObject(rufoDome4);

	

	
	
}

int main() {

	Window *w = Window::CreateGameWindow("CSC3223 Coursework 1!");

	if (!w->HasInitialised()) {
		return -1;
	}

	w->LockMouseToWindow(true);
	ShowCursor(false);

	Renderer* renderer = new Renderer(*w);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	float aspect = w->GetScreenAspect();
	Matrix4 proj = Matrix4::Perspective(1.0f, 100.0f, aspect, 60.0f);
	renderer->SetProjectionMatrix(proj);

	float yaw = 0; //rotate ABOUT the y axis, left to right
	float pitch = 0; //rotate ABOUT the x axis, up and down
	

	Vector3 viewPosition(-180, -40, -350); //initial position

	renderer->SetProjectionMatrix(
		Matrix4::Perspective(1, 10000, w->GetScreenAspect(), 60.0f));
	
	Starfield(renderer);
	Planetoid(renderer);
	Spaceship(renderer);

	RenderObject* pyramid = Pyramid();
	renderer->AddRenderObject(pyramid);
	bool forwards = true;

	RenderObject* planet = Sphere();
	renderer->AddRenderObject(planet);

	bool depthBuffer = false;
	renderer->EnableDepthBuffer(depthBuffer);
	bool alphaBlending = false;
	renderer->EnableAlphaBlending(alphaBlending);
	string depthState = "Depth Buffer: False!";
	string alphaState = "Alpha Blending: False!";


	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {

		float time = w->GetTimer()->GetTimeDelta();

		yaw -= 0.5 * Window::GetMouse()->GetRelativePosition().x;
		pitch -= 0.5 * Window::GetMouse()->GetRelativePosition().y;

		Matrix4 yawRotate = Matrix4::Rotation(yaw, Vector3(0,1,0));
		Matrix4 pitchRotate = Matrix4::Rotation(pitch , Vector3(1, 0, 0));

		renderer->Update(time);
	

		renderer->DrawString("OpenGL Rendering!", Vector2(10, 10));
		renderer->DrawString(depthState, Vector2(10, 28));
		renderer->DrawString(alphaState, Vector2(10, 46));
		

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
			viewPosition.x += 2.0f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			viewPosition.x -= 2.0f;

		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			viewPosition.y -= 2.0f;
		}
		
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			viewPosition.y += 2.0f;

		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_Q)) {
			viewPosition.z -= 2.0f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_E)) {
			viewPosition.z += 2.0f;

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

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F1)) {
			
			if (!depthBuffer) {
				depthBuffer = true;
				glEnable(GL_DEPTH_TEST);
				depthState = "Depth Buffer: True!";
			}

			else if (depthBuffer) {
				depthBuffer = false;
				glDisable(GL_DEPTH_TEST);
				depthState = "Depth Buffer: False!";

			}
			

		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F2)) {
			if (depthBuffer) {
				glDepthFunc(GL_ALWAYS);
			}
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F3)) {
			if (depthBuffer) {
				glDepthFunc(GL_EQUAL);
			}
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F4)) {
			if (depthBuffer) {
				glDepthFunc(GL_LESS);
			}
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F5)) {

			if (!alphaBlending) {
				alphaBlending = true;
				renderer->EnableAlphaBlending(true);
				alphaState = "Alpha Blending: True!";
			}

			else if (alphaBlending) {
				alphaBlending = false;
				renderer->EnableAlphaBlending(false);
				alphaState = "Alpha Blending: False!";
			}
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F6)) {
			if (alphaBlending) {
				
				renderer->SetBlendToLinear();
			}
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F7)) {
			if (alphaBlending) {
				
				renderer->SetBlendToAdditive();
			}
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F8)) {
			if (alphaBlending) {
				
				renderer->SetBlendToInvert();
			}
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F9)) {
			planet = nullptr;
			pyramid = nullptr;

			viewPosition.x = -180;
			viewPosition.y = -40;
			viewPosition.z = -350;

			//Vector3 viewPosition(-180, -40, -350); //initial position

			yaw = 0;
			pitch = 0;

			renderer->DeleteAllRenderObjects();
			

			OGLMesh* o =
				(OGLMesh*)RasterisationMesh::CreateLineFromPoints(
					{ Vector3(20, 60, -20), Vector3(20, 20, -20),
					Vector3(20, 20,-20), Vector3(30, 10, -20),
					Vector3(30, 10,-20), Vector3(50, 10, -20),
					Vector3(50, 10,-20), Vector3(60, 20, -20),
					Vector3(60, 20,-20), Vector3(60, 60, -20),
					Vector3(60, 60,-20), Vector3(50, 70, -20),
					Vector3(50, 70,-20), Vector3(30, 70, -20),
					Vector3(30, 70,-20), Vector3(20, 60, -20)
					},
					{ Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) 
					 },
					false);
			renderer->AddRenderObject(new RenderObject(o));

			OGLMesh* s =
				(OGLMesh*)RasterisationMesh::CreateLineFromPoints(
					{ Vector3(100, 70, -20), Vector3(80, 70, -20),
					Vector3(80, 70,-20), Vector3(75, 60, -20),
					Vector3(75, 60,-20), Vector3(75, 50, -20),
					Vector3(75, 50,-20), Vector3(80, 40, -20),
					Vector3(80, 40,-20), Vector3(100, 40, -20),
					Vector3(100, 40,-20), Vector3(105, 30, -20),
					Vector3(105, 30,-20), Vector3(105, 20, -20),
					Vector3(105, 20,-20), Vector3(100, 10, -20),
					Vector3(100, 10,-20), Vector3(80, 10, -20)
					},
					{ Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1),
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1)
					
					},
					false);
			renderer->AddRenderObject(new RenderObject(s));

			OGLMesh* c =
				(OGLMesh*)RasterisationMesh::CreateLineFromPoints(
					{ Vector3(145, 70, -20), Vector3(125, 70, -20),
					Vector3(125, 70,-20), Vector3(120, 65, -20),
					Vector3(120, 65,-20), Vector3(120, 15, -20),
					Vector3(120, 15,-20), Vector3(125, 10, -20),
					Vector3(125, 10,-20), Vector3(145, 10, -20),
				
					},
					{ Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1),
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1)

					},
					false);
			renderer->AddRenderObject(new RenderObject(c));


			OGLMesh* a =
				(OGLMesh*)RasterisationMesh::CreateLineFromPoints(
					{ Vector3(160, 10, -20), Vector3(170, 35, -20),
					Vector3(170, 35,-20), Vector3(190, 35, -20),
					Vector3(190, 35,-20), Vector3(200, 10, -20),
					

					},
					{ Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1),
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1)

					},
					false);
			renderer->AddRenderObject(new RenderObject(a));

			OGLMesh* tria = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({
				Vector3(170,35, -20), Vector3(180,70,-20), Vector3(190,35,-20) }, 

				{ Vector4(0 , 1 , 1 , 1),
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) });
			renderer->AddRenderObject(new RenderObject(tria));

			OGLMesh* r =
				(OGLMesh*)RasterisationMesh::CreateLineFromPoints(
					{ Vector3(220, 10, -20), Vector3(220, 70, -20),
					Vector3(220, 70,-20), Vector3(235, 70, -20),
					Vector3(235, 70,-20), Vector3(245, 60, -20),
					Vector3(245, 60,-20), Vector3(245, 50, -20),
					Vector3(245, 50,-20), Vector3(235, 40, -20),
					Vector3(235, 40,-20), Vector3(220, 40, -20),
					Vector3(220, 40,-20), Vector3(245, 10, -20),
					
					},
					{ Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1),
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1),
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1) ,
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1),
					Vector4(0 , 1 , 1 , 1) , Vector4(0 , 1 , 1 , 1),
					Vector4(0 , 1 , 1 , 1) ,Vector4(0 , 1 , 1 , 1) ,
					
					},
					false);
			renderer->AddRenderObject(new RenderObject(r));
			



		}

		renderer->SetViewMatrix(Matrix4::Translation(viewPosition) * pitchRotate * yawRotate);

		w->SetTitle(std::to_string(time));

		
		if (pyramid != nullptr) {

			if (forwards) {
				pyramid->SetTransform(pyramid->GetTransform() * Matrix4::Translation(Vector3(0, 0, +10 * time)));
			}

			if (!forwards) {
				pyramid->SetTransform(pyramid->GetTransform() * Matrix4::Translation(Vector3(0, 0, -10 * time)));
			}

			if (pyramid->GetTransform().GetPositionVector().z > 100) {
				forwards = false;
			}

			if (pyramid->GetTransform().GetPositionVector().z < -100) {
				forwards = true;
			}
		}

		if (planet != nullptr) {
			planet->SetTransform(planet->GetTransform() * Matrix4::Rotation(2, Vector3(0, 1, 0)));
		}

		//pyramid->SetTransform(pyramid->GetTransform() * Matrix4::Translation(Vector3(0, 0, time)));
		
	}

	delete renderer;

	Window::DestroyGameWindow();
}