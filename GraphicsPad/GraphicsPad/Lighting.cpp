/*#include "lighting.h"
#include "GLM\glm.hpp"
#include "Primitives\Vertex3D.h"
#include "renderingEngine.h"
#include "../core/coreEngine.h"

#define COLOR_DEPTH 256

void BaseLight::AddToEngine(CoreEngine* engine) const
{
	engine->GetRenderingEngine()->AddLight(*this);
}

ShadowCameraTransform BaseLight::CalcShadowCameraTransform(const glm::vec3& mainCameraPos, const glm::quat& mainCameraRot) const
{
	return ShadowCameraTransform(GetTransform().GetTransformedPos(), GetTransform().GetTransformedRot());
}

DirectionalLight::DirectionalLight(const Color& color, float intensity, int shadowMapSizeAsPowerOf2,
	float shadowArea, float shadowSoftness, float lightBleedReductionAmount, float minVariance) :
	BaseLight(color, intensity, Shader("forward-directional")),
	m_halfShadowArea(shadowArea / 2.0f)
{
	if (shadowMapSizeAsPowerOf2 != 0)
	{
		SetShadowInfo(ShadowInfo(glm::mat4().InitOrthographic(-m_halfShadowArea, m_halfShadowArea, -m_halfShadowArea,
			m_halfShadowArea, -m_halfShadowArea, m_halfShadowArea),
			true, shadowMapSizeAsPowerOf2, shadowSoftness, lightBleedReductionAmount, minVariance));
	}
}


ShadowCameraTransform DirectionalLight::CalcShadowCameraTransform(const glm::vec3& mainCameraPos, const glm::quat& mainCameraRot) const
{
	glm::vec3 resultPos = mainCameraPos + mainCameraRot.GetForward() * GetHalfShadowArea();
	glm::quat resultRot = GetTransform().GetTransformedRot();

	float worldTexelSize = (GetHalfShadowArea() * 2) / ((float)(1 << GetShadowInfo().GetShadowMapSizeAsPowerOf2()));

	glm::vec3 lightSpaceCameraPos = resultPos.Rotate(resultRot.Conjugate());

	lightSpaceCameraPos.SetX(worldTexelSize * floor(lightSpaceCameraPos.GetX() / worldTexelSize));
	lightSpaceCameraPos.SetY(worldTexelSize * floor(lightSpaceCameraPos.GetY() / worldTexelSize));

	resultPos = lightSpaceCameraPos.Rotate(resultRot);

	return ShadowCameraTransform(resultPos, resultRot);
}

PointLight::PointLight(const Color& color, float intensity, const Attenuation& attenuation, const Shader& shader) :
	BaseLight(color, intensity, shader),
	m_attenuation(attenuation)
{
	float a = m_attenuation.GetExponent();
	float b = m_attenuation.GetLinear();
	float c = m_attenuation.GetConstant() - COLOR_DEPTH * intensity * color.Max();

	m_range = (-b + sqrtf(b*b - 4 * a*c)) / (2 * a);
}

SpotLight::SpotLight(const Color& color, float intensity, const Attenuation& attenuation, float viewAngle,
	int shadowMapSizeAsPowerOf2, float shadowSoftness, float lightBleedReductionAmount, float minVariance) :
	PointLight(color, intensity, attenuation, Shader("forward-spot")),
	m_cutoff(cos(viewAngle / 2))
{
	if (shadowMapSizeAsPowerOf2 != 0)
	{
		SetShadowInfo(ShadowInfo(glm::mat4().InitPerspective(viewAngle, 1.0, 0.1, GetRange()), false, shadowMapSizeAsPowerOf2,
			shadowSoftness, lightBleedReductionAmount, minVariance));
	}
}
*/