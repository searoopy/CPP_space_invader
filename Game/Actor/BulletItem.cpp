#include "BulletItem.h"

#include "Engine/Engine.h"
#include "Utill/utill.h"

int BulletItem::bulletItemCnt = 0;

BulletItem::BulletItem(const char* image)
	: super(image, Vector2::Zero, Color::Red) 
{

	int screenCenterx = Engine::Get().GetWidth()-width;
	int screenCentery = Engine::Get().GetHeight()-height;

	int ranx = Utill::RandomRange(width, screenCenterx);
	int rany = Utill::RandomRange(height, screenCentery);

	mx = ranx;
	my = rany;

	SetPosition(Vector2(mx, my));

	bulletItemCnt += 1;

}

BulletItem::~BulletItem()
{
	bulletItemCnt -= 1;
}

void BulletItem::Tick(float deltaTime)
{
}

void BulletItem::OnDestroy()
{
}
