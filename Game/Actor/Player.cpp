#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "PlayerBullet.h"
#include "Level/GameLevel.h"
#include "utill/utill.h"
#include "Render/Renderer.h"
#include "PlayerGui.h"

Player::Player()
	: super(" ", Vector2::Zero, Color::Green),
	fireMode(FireMode::Normal), bulletFirePos(Vector2::Zero) , bulletCnt(5)
{
	// 생성 위치 설정.
	int xPosition = (Engine::Get().GetWidth() / 2) - (width / 2);
	int yPosition = Engine::Get().GetHeight() /2;

	SetPosition(Vector2(xPosition, yPosition));


	mx = xPosition;
	my = yPosition;
	direction = 270;


	const char* strtemp1 = 
R"(  
  A
 AAA)";
	size_t length = strlen(strtemp1) + 1;
	this->image1 = new char[length];	
	strcpy_s(this->image1, length, strtemp1);

	//회전 이미지.
	const char* strtemp2 = 
		R"(  
 A A 
  A
 A)";

	length = strlen(strtemp2) + 1;
	this->image2 = new char[length];
	strcpy_s(this->image2, length, strtemp2);

	const char* strtemp3 = 
		R"(  
  A
 AA 
  A
  )";

	length = strlen(strtemp3) + 1;
	this->image3 = new char[length];
	strcpy_s(this->image3, length, strtemp3);



	const char* strtemp4 =
		R"(  
 V
  V
 V V)";
	length = strlen(strtemp4) + 1;
	this->image4 = new char[length];
	strcpy_s(this->image4, length, strtemp4);

	timer.SetTargetTime(fireInterval);


	const char* strtemp5 = 
		R"(  

 VVV
  V)";
	length = strlen(strtemp5) + 1;
	this->image5 = new char[length];
	strcpy_s(this->image5, length, strtemp5);
	     
	timer.SetTargetTime(fireInterval);



	const char* strtemp6 =
		R"(  
   V
  V
 V V
)";
	length = strlen(strtemp6) + 1;
	this->image6 = new char[length];
	strcpy_s(this->image6, length, strtemp6);

	timer.SetTargetTime(fireInterval);


	const char* strtemp7 =
		R"(  
  A 
  AA
  A
  )";
	length = strlen(strtemp7) + 1;
	this->image7 = new char[length];
	strcpy_s(this->image7, length, strtemp7);

	timer.SetTargetTime(fireInterval);



	const char* strtemp8 =
		R"(
 A A
  A
   A)";
	length = strlen(strtemp8) + 1;
	this->image8 = new char[length];
	strcpy_s(this->image8, length, strtemp8);

	timer.SetTargetTime(fireInterval);
}

Player::~Player()
{
	SafeDeleteArray(image1);
	SafeDeleteArray(image2);
	SafeDeleteArray(image3);
	SafeDeleteArray(image4);
	SafeDeleteArray(image5);
	SafeDeleteArray(image6);
	SafeDeleteArray(image7);
	SafeDeleteArray(image8);
}



void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (Input::Get().GetKeyKey(VK_ESCAPE))
	{
		Engine::Get().QuitEngine();
	}


	//경과 시간 업뎃.


	timer.Tick(deltaTime);
	//elapsedTime += deltaTime;

	//위 아래...전진 후진
	//moveSpeed = 0;
	if (moveSpeed > 0)
		moveSpeed -= moveSlideSpeed;

	if (Input::Get().GetKeyKey(VK_UP))
	{

		moveSpeed = moveSetSpeed;
	}
	if (Input::Get().GetKeyKey(VK_DOWN))
	{
	///	moveSpeed = -0.2f;
	}





	// 좌우 방향키 입력처리.
	if (Input::Get().GetKeyKey(VK_RIGHT))
	{
		//MoveLeft();

		direction += (rotSpeed);
	}
	if (Input::Get().GetKeyKey(VK_LEFT))
	{
		//MoveRight();

		direction -= (rotSpeed);
	}

	direction = Utill::WrapAngle(direction);
	

	//이동 업데이트...
	mx += cos(Utill::to_radian(direction)) * moveSpeed* deltaTime;
	my += sin(Utill::to_radian(direction)) * moveSpeed* deltaTime;


	position.x = static_cast<int>(mx);
	position.y = static_cast<int>(my);
	//
	//SetPosition(Vector2(mx, my));
	MoveCheck();



	if (fireMode == FireMode::Normal)
	{
		if (Input::Get().GetKeyDown(VK_SPACE))
		{
			Fire();
		}
	}
	else if (fireMode == FireMode::Repeat)
	{
		if (Input::Get().GetKeyKey(VK_SPACE))
		{
			Fire();
		}
	}
	
	if (Input::Get().GetKeyDown('G'))
	{
		AddBulletCnt(10);// += 10;
		
	}

	//발사 모드 전환.
	if (Input::Get().GetKeyDown('R'))
	{
		int mode = static_cast<int>(fireMode);

		mode = 1 - mode;
		fireMode = static_cast<FireMode>(mode);
	}
	
}

void Player::Draw()
{

	//위 방향이 270도....
	const int _degree = 23;
	
	if (direction > (270- _degree) && direction < 270 + _degree) //위쪽.
	{
		Renderer::Get().Submit(
			image1, position, color, sortingorder);

		
	}
	else if (direction >= (225- _degree) && direction < (225 + _degree)) //왼쪽
	{
		Renderer::Get().Submit(
			image2, position, color, sortingorder);

	}
	else if (direction >= (180 - _degree) && direction < (180 + _degree)) //왼쪽
	{
		Renderer::Get().Submit(
			image3, position, color, sortingorder);

	}
	else if (direction >= (135 - _degree) && direction < (135 + _degree)) //왼아래
	{
		Renderer::Get().Submit(
			image4, position, color, sortingorder);

	}
	else if (direction >= (90 - _degree) && direction < (90 + _degree)) //아래
	{
		Renderer::Get().Submit(
			image5, position, color, sortingorder);

	}
	else if (direction >= (45 - _degree) && direction < (45 + _degree)) //아래로느
	{
		Renderer::Get().Submit(
			image6, position, color, sortingorder);

	}
	else if (direction >= Utill::WrapAngle(360 - _degree) || direction < Utill::WrapAngle(360 + _degree)) //오른
	{
		Renderer::Get().Submit(
			image7, position, color, sortingorder);

	}
	else
	{
		Renderer::Get().Submit(
			image8, position, color, sortingorder);

	}



}


void Player::CheckBulletFirePos()
{
	//bulletFirePosconst int _degree = 23;
	int _degree = 23;
	int _x = 0;
	int _y = 0;
	if (direction > (270 - _degree) && direction < 270 + _degree) //위쪽.
	{
		_x = 2;
		_y = 2;
	}
	else if (direction >= (225 - _degree) && direction < (225 + _degree)) //왼쪽
	{
		_x = 1;
		_y = 1;
	}
	else if (direction >= (180 - _degree) && direction < (180 + _degree)) //왼쪽
	{
		_x = 0;
		_y = 5;
	}
	else if (direction >= (135 - _degree) && direction < (135 + _degree)) //왼아래
	{
		//_x = -2;
		_x = 1;
		_y = 6;
	}
	else if (direction >= (90 - _degree) && direction < (90 + _degree)) //아래
	{
		_x = 3;
		_y = 6;
	}
	else if (direction >= (45 - _degree) && direction < (45 + _degree)) //아래로느
	{
		_x = 5;
		_y = 6;
	}
	else if (direction >= Utill::WrapAngle(360 - _degree) || direction < Utill::WrapAngle(360 + _degree)) //오른
	{
		_x = 5;
		_y = 3;

	}
	else
	{
		_x = 5;
		_y = 2;
	}


	bulletFirePos.x = _x;
	bulletFirePos.y = _y;
}

void Player::MoveCheck()
{
	// 오른쪽 이동 처리.

	// 좌표 검사.
	// "<-=A=->"
	int width2 = Engine::Get().GetWidth();
	int height2 = Engine::Get().GetHeight();

	if (mx - width > width2 )
	{
		mx = 0;

	}
	else if (mx < -width)
	{
		mx = width2-1;

	}

	if (my + height > height2)
	{
		my = 0;

	}
	else if (my < -height)
	{
		my = height2- 1;
	}

}



void Player::Fire()
{
	if (bulletCnt <= 0)
		return;

	AddBulletCnt(-1);
	PlayerGui::Get().SetBullet(bulletCnt);

	timer.Reset();
	//elapsedTime = 0.0f;


	CheckBulletFirePos();

	//총알 생성 위치 계산...
	int _tempx = bulletFirePos.x + cos(Utill::to_radian(direction)) * 1;
	int _tempy = bulletFirePos.y + sin(Utill::to_radian(direction)) * 1;

	Vector2 bulletPos(position.x + _tempx, position.y + _tempy );

	GetOwner()->AddNewActor(new PlayerBullet(bulletPos, direction ));

}

void Player::FireInterval()
{
	if (!CanShot() || fireMode == FireMode::Repeat)
	{
		return;
	}

	Fire();
}


bool Player::CanShot()
{
	return timer.IsTimeOut();
}

void Player::SetBulletCnt(int val)
{
	bulletCnt = val;
	PlayerGui::Get().SetBullet(bulletCnt);

}
void Player::AddBulletCnt(int val)
{
	bulletCnt += val;
	PlayerGui::Get().SetBullet(bulletCnt);

}