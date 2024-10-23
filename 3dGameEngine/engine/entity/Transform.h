#pragma once
#include <glm/glm.hpp>


namespace MK {

	struct Transform
	{
	public:

		glm::vec3 mPosition;
		float mScale;
		float mAngle;

		glm::mat4 mModelMat;


	public:

		void move(glm::vec3 pos);
		void movex(float amount);
		void movey(float amount);
		void movez(float amount);





	};

}
