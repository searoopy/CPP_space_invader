
#include "TitleLevel.h"
#include "Render/Renderer.h"
#include "Actor/TitleActor.h"


TitleLevel::TitleLevel()
{
	AddNewActor(new TitleActor(Vector2(0,0)));



}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Tick(float dtime)
{
	super::Tick(dtime);
}


