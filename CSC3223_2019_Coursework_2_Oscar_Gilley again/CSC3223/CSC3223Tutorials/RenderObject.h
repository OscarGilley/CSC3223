#pragma once
#include "../../Common/Matrix4.h"
#include "../../Common/TextureBase.h"
#include "../../Common/ShaderBase.h"

#include <vector>
namespace NCL {
	using namespace NCL::Rendering;
	class MeshGeometry;
	namespace CSC3223 {
		using namespace Maths;

		class RenderObject
		{
		public:
			RenderObject(MeshGeometry* mesh, Matrix4 m = Matrix4());
			~RenderObject();

			void SetSecondTexture(TextureBase* t) {
				secondTexture = t;
			}

			TextureBase* GetSecondTexture() const {
				return secondTexture;
			}

			MeshGeometry*		GetMesh() const {
				return mesh;
			}

			void  SetTransform(Matrix4 mat) {
				transform = mat;
			}

			Matrix4 GetTransform() const {
				return transform;
			}

			void SetBaseTexture(TextureBase* t) {
				texture = t;
			}

			TextureBase* GetBaseTexture() const {
				return texture;
			}


			void SetShader(ShaderBase* s) {
				shader = s;
			}

			ShaderBase* GetShader() const {
				return shader;
			}

		protected:
			TextureBase*	secondTexture;
			MeshGeometry*	mesh;
			TextureBase*	texture;
			ShaderBase*		shader;
			Matrix4			transform;
		};
	}
}

