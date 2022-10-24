// COMP710 Les Mcilroy
#ifndef __GUIContainer_H__
#define __GUIContainer_H__

//Local includes

//Library includes

#include <vector>
//Forward declarations:
class Sprite;
class Renderer;
class InputSystem;

//Class delcaration
class GUIContainer
{
public:
	GUIContainer();
	~GUIContainer();

	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);
	bool Initialise(Renderer& renderer);

	void AddSprite(Sprite* sprite);

	void SetVisable(bool setActive);
	void SetReady(bool setReady);
	bool IsVisable();
	bool IsReady();
	float GetFirstElementHeight();
	float GetFirstElementWidth();
	std::vector<Sprite*> m_spriteVector;

private:

	bool m_isVisable;
	bool m_isReady;
};

#endif // !__GUIContainer_H__
