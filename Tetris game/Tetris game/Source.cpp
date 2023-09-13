#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <time.h>
#include <Windows.h>
#include <string>
#include <iostream>
using namespace sf;

//settings
float speedAmplfierVert; //0
float speedAmplfierHor; //1
int volume;  //2
bool peaceful;  //3

float interacted;
bool destroyed;
int song;
bool ToExit;
Music theme[5];
bool start;
int score;
int music;
bool created;
Text scorePoints, points;
Font font;
int p;
int map[64][36];
Texture brick[6];
Texture pattern;
int qwer = 0;
class Brick
{
private:
public:
	float fallSpeed = 0;
	int horizontalSpeed = 0;
	Sprite brickSprite;
	int color = 0;
	int type = 0;
	Vector2f positionInt;
	Vector2f positionFloat;

	Sprite getSprite()
	{
		return brickSprite;
	}

	Vector2f getPosition()
	{
		return positionFloat;
	}
};


void create(Brick* obj);

void initialize();

void keyboard(Brick* obj, float dt, Event event, RenderWindow* window);

bool tryRotate(Brick* obj);

bool collision(Brick* obj, int rotation, Vector2f rotPos);

Vector2f getSize(int type, int rotation);

void stop(Brick* obj, int rotation, Vector2f pos);

void optimization(Texture* video, int fr);

void pause(RenderWindow* window);

int main()
{
	interacted = 0;
	volume = 50;
	speedAmplfierVert = 2.0;
	speedAmplfierHor = 3.0;
	ToExit = 0;
	int nextType = -1;
	int nextColor = -1;
	start = 0;
	score = 0;
	if (!theme[0].openFromFile("Theme BASS.ogg"))
	{
		return -1;
	}
	if (!theme[1].openFromFile("Theme 1.ogg"))
	{
		return -1;
	}
	if (!theme[2].openFromFile("Theme piano.ogg"))
	{
		return -1;
	}
	if (!theme[3].openFromFile("Theme 8bit.ogg"))
	{
		return -1;
	}
	if (!theme[4].openFromFile("Peaceful.ogg"))
	{
		return -1;
	}
	Clock clock, frame;
	srand(static_cast<unsigned int>(time(NULL)));
	initialize();
	created = 0;
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 36; j++)
		{
			if (i < 4 || i >= 60 || j < 6)
			{
				map[i][j] = -2; //стенки
			}
			else
			{
				map[i][j] = -1; //пустота
			}

		}

	bool fallen = 1;
	RenderWindow window(VideoMode(1920, 1080), "Wide Tetris", Style::Fullscreen);
	window.setFramerateLimit(60);
	Texture backgr;
	backgr.loadFromFile("background.png");
	Sprite bg_sprite;
	bg_sprite.setTexture(backgr);
	int color[56];
	Vector2f posBr[56];
	Sprite vid1;
	Sprite vid2;
	Texture video1;
	Texture video2;
	Sprite block;
	Brick obj;
	Brick next;
	Clock clockSpear;
	int j = -1;
	obj.color = rand() % 6;
	obj.type = rand() % 7;
	next.color = rand() % 6;
	next.type = rand() % 7;
	obj.color = 0;
	obj.fallSpeed = 0;
	obj.horizontalSpeed = 0;
	obj.type = 0;
	int fallenBrick[56];
	peaceful = 1;
	if (!peaceful)
	{
		song = rand() % 4;
		for (int i = 0; i < 5; i++)
		{
			theme[i].play();
			theme[i].stop();
		}
		theme[song].play();
	}
	else
	{
		theme[4].play();
	}
	for (int i = 0; i < 5; i++)
	{
		theme[i].setVolume(50);
	}
	int fr = 0;
	theme[4].setLoop(true);
	destroyed = 1;
	Sprite spear;
	int spr = 0;
	Music sound, spearMove;
	if (!sound.openFromFile("GetOverHere.ogg"))
	{
		return -1;
	}
	if (!spearMove.openFromFile("spearMove.ogg"))
	{
		return -1;
	}
	sound.play();
	sound.stop();
	spearMove.play();
	spearMove.stop();
	Sprite brick1;
	bool first = 0, second = 0, third = 0;

	while (window.isOpen() && !ToExit)
	{
	again:
		if (!peaceful)
		{
			if (!(theme[0].getStatus() || theme[1].getStatus() || theme[2].getStatus() || theme[3].getStatus()))
			{
				if (song == 0)
				{
					song = rand() % 4;
					if (song == 0)
					{
						goto again;
					}
				}
				else if (song == 1)
				{
					song = rand() % 4;
					if (song == 1)
					{
						goto again;
					}
				}
				else if (song == 2)
				{
					song = rand() % 4;
					if (song == 2)
					{
						goto again;
					}
				}
				else if (song == 3)
				{
					song = rand() % 4;
					if (song == 3)
					{
						goto again;
					}
				}
				theme[song].play();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::P) && start == 0)
		{
			start = 1;
		}
		window.clear();
		Time frameTime = frame.getElapsedTime();
		if (frameTime.asMilliseconds() > 1000.0 / 60)
		{
			if (fr < 499)
			{
				fr++;
			}
			else
			{
				fr = 0;
			}
			frame.restart();
		}
		if (!peaceful)
		{
			vid1.setPosition(120, 180);
			optimization(&video1, fr);
			vid1.setTexture(video1);
			vid1.setScale((float)1.35, (float)1.35);
			window.draw(vid1);
		}
		else
		{
			optimization(&video2, fr);
			vid2.setScale(1, 1);
			vid2.setTexture(video2);
			window.draw(vid2);
		}


		window.draw(bg_sprite);

		for (int i = 4; i < 60; i++)
			for (int j = 6; j < 36; j++)
				for (int k = 0; k < 6; k++)
				{
					if (map[i][j] == k)
					{
						Sprite setBrick;
						setBrick.setTexture(brick[k]);
						setBrick.setPosition(30.0 * i, 30.0 * j);
						window.draw(setBrick);
					}
				}
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		int i = 1;
		if (!created)
		{
			if (map[28][6] != -1 || map[27][6] != -1 || map[28][7] != -1 || map[27][7] != -1)
			{
				start = 0;
				Text gameover;
				auto s = std::to_string(score);
				gameover.setString("              Ты проиграл\n              Твой счёт: " + s + "\n\n\n\nНажми Enter для продолжения");
				Font font;
				font.loadFromFile("CyrilicOld.ttf");
				gameover.setFont(font);
				gameover.setFillColor(Color::Black);
				gameover.setPosition(590, 440);
				gameover.setCharacterSize(50);
				window.clear(Color::White);
				window.draw(gameover);
				window.display();
				score = 0;
				while (1)
				{
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
							window.close();
					}
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						for (int i = 4; i < 60; i++)
							for (int j = 6; j < 36; j++)
							{
								map[i][j] = -1;
							}
						break;
					}
				}
			}
			int amplifier = 0;
			int str = -1;
			for (int k = 6; k < 36; k++)
			{
				int s = 0;
				for (int i = 4; i < 60; i++)
				{
					if (map[i][k] == -1)
					{
						s++;
						break;
					}
				}
				if (s == 0)
				{
					str = k;
					amplifier++;
					j = str;
				}
			}
			if (amplifier == 1 && destroyed)
			{
				for (int i = 4; i < 60; i++)
				{
					color[i - 4] = map[i][j];
					fallenBrick[i - 4] = 0;
				}
				if (peaceful)
				{
					theme[4].pause();
				}
				else
				{
					theme[song].pause();
				}
				interacted = 0;
				destroyed = 0;
				j = str;
				spear.setPosition(-300.0, j * 30.0);
				spr = 0;
			}
			else if (amplifier > 1)
			{
				for (int y = 0; y < amplifier; y++)
				{
					for (int i = 4; i < 60; i++)
					{
						map[i][j] = -1;
					}
					for (int i = 4; i < 60; i++)
						for (int u = j; u > 6; u--)
						{
							map[i][u] = map[i][u - 1];
						}
					for (int i = 4; i < 60; i++)
					{
						map[i][6] = -1;
					}
				}
				if (amplifier == 4)
				{
					score += 240;
				}
				else
					score += 60;
			}
			if (!destroyed)
			{
				if (spr == 0)
				{
					spr = 1;
					spearMove.play();
				}
				Texture br;
				br.loadFromFile("Pattern.png");
				Texture spearTexture;
				spearTexture.loadFromFile("spear.png");
				spear.setTexture(spearTexture);
				if (third == 0 && second == 0 && first == 1 && interacted < 1.0)
				{
					Time t = clockSpear.getElapsedTime();
					interacted += t.asSeconds();
				}
				Time t1 = clockSpear.restart();
				float dt1 = t1.asSeconds();
				if (dt1 > 2)
				{
					dt1 /= 50;
				}
				Vector2f pos = spear.getPosition();
				if (pos.x < 120 - 246 && first == 0 && second == 0 && third == 0)
				{
					dt1 /= 50;
					for (int i = 0; i < 50 && pos.x < 120 - 246; i++)
					{
						pos.x += 1000 * dt1;
					}
					spear.setPosition(pos);
					if (pos.x >= 120 - 246)
					{
						first = 1;
					}
					window.draw(spear);
				}
				else if (first == 1 && second == 0 && third == 0 && interacted < 1.0)
				{
					window.draw(spear);
				}
				else if (first == 1 && second == 0 && third == 0 && interacted >= 1.0)
				{
					second = 1;
					sound.play();
					window.draw(spear);
					clockSpear.restart();
				}
				else if (first == 1 && second == 1 && third == 0)
				{
					if (dt1 > 1.0)
					{
						dt1 = 0;
					}
					pos.x -= 1000 * dt1;
					spear.setPosition(pos);
					for (int i = 0; i < 56; i++)
					{
						Vector2f brPos = pos;
						brPos.x += 246 + 30 * i;
						brick1.setPosition(brPos);
						IntRect a(0, color[i] * 30 * 2, 30, 30);
						brick1.setTextureRect(a);
						brick1.setTexture(br);
						window.draw(brick1);
						if (pos.x + 246 + 1800 < 30 * (i + 4) && map[i + 4][j] == -1 && fallenBrick[i] == 0)
						{
							for (int u = j - 1; u >= 6; u--)
							{
								map[i + 4][u + 1] = map[i + 4][u];
							}
							fallenBrick[i] = 1;
						}
						else if (fallenBrick[i] == 0)
						{
							map[i + 4][j] = -1;
						}
					}
					window.draw(spear);
					if (pos.x < -1800 + 120 - 246)
					{
						third = 1;
						sound.stop();
						spearMove.stop();
					}
				}
				else if (third == 1)
				{
					destroyed = 1;
					first = 0;
					second = 0;
					third = 0;
					score += 60;
					if (peaceful)
					{
						theme[4].play();
					}
					else
					{
						theme[song].play();
					}
				}
			}
			else if (destroyed)
			{
				obj.brickSprite.setRotation(0);
				obj.color = next.color;
				obj.type = next.type;
				next.color = rand() % 6;
				next.type = rand() % 7;
				create(&next);
				next.fallSpeed = 0;
				next.horizontalSpeed = 0;
				next.positionFloat.y -= 30 * 4.5;
				create(&obj);
				created = true;
				clock.restart();
			}
		}
		else
		{
			Time dT = clock.restart();
			float dt = dT.asSeconds();
			keyboard(&obj, dt, event, &window);
			obj.brickSprite.setPosition(obj.positionInt);
			next.brickSprite.setPosition(next.positionFloat);
			window.draw(obj.brickSprite);
		}
		window.draw(next.brickSprite);
		Text scorePoints;
		Font font;
		font.loadFromFile("CyrilicOld.ttf");
		scorePoints.setFont(font);
		scorePoints.setPosition(30, 30);
		scorePoints.setCharacterSize(30);
		scorePoints.setFillColor(Color::Black);
		auto s = std::to_string(score);
		if (!peaceful)
		{
			scorePoints.setString("Счёт: " + s + "\nEsc - пауза\nF12 - выход \n M - смена трека");
		}
		else
		{
			scorePoints.setString("Счёт: " + s + "\nEsc - пауза\nF12 - выход \n");
		}
		window.draw(scorePoints);
		if (!start)
		{
			Text st;
			st.setFont(font);
			st.setString("Нажми P для старта");
			st.setPosition(1600, 30);
			st.setCharacterSize(30);
			st.setFillColor(Color::Black);
			window.draw(st);
		}
		if (Keyboard::isKeyPressed(Keyboard::M))
		{
			qwer = 1;
		}
		if (event.key.code == Keyboard::M && qwer == 1)
		{
			if (!peaceful)
			{
				song = (song+1) % 4;
				for (int i = 0; i < 5; i++)
				{
					theme[i].play();
					theme[i].stop();
				}
				theme[song].play();
				qwer = 0;
			}
		}
		window.display();
	}
	return 0;
}

void create(Brick* obj)
{
	IntRect rect;
	obj->brickSprite.setTexture(pattern);
	obj->positionFloat.y = 30.0 * 6;
	obj->positionInt.y = 30 * 6;
	if (obj->type == 6)
	{
		obj->positionFloat.x = 28.0 * 30;
		obj->positionInt.x = 28 * 30;
		obj->brickSprite.setPosition(obj->positionInt);
		rect.left = 540;
		rect.height = 30;
		rect.width = 30 * 4;
	}
	else
	{
		obj->positionFloat.x = 29.0 * 30;
		obj->positionInt.x = 29 * 30;
		obj->brickSprite.setPosition(obj->positionInt);
		rect.left = obj->type * 90;
		rect.height = 60;
		rect.width = 90;
	}
	rect.top = obj->color * 60;
	obj->brickSprite.setTextureRect(rect);
}

void keyboard(Brick* obj, float dt, Event event, RenderWindow* window)
{
	int width = 0;
	int height = 0;
	int rotation;
	rotation = obj->brickSprite.getRotation() / 90;

	if (obj->type == 6 && rotation % 2 == 0)
	{
		width = 4;
		height = 1;
	}
	else if (obj->type == 2)
	{
		width = 2;
		height = 2;
	}
	else if (obj->type != 6 && rotation % 2 != 0)
	{
		width = 2;
		height = 3;
	}
	else if (obj->type == 6)
	{
		width = 1;
	}
	else
	{
		width = 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::D))
	{
		obj->horizontalSpeed = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A))
	{
		int rotation = ((int)obj->brickSprite.getRotation() / 90) % 4;
		Vector2f size = getSize(obj->type, rotation);
		Vector2f pos;
		pos.x = obj->positionFloat.x - 30;
		pos.y = obj->positionFloat.y;
		pos.x = 30.0 * (int)(pos.x / 30);
		pos.y = 30.0 * (int)(pos.y / 30);
		if ((rotation == 0 || rotation == 3) && collision(obj, rotation, pos))
		{
			if (obj->positionInt.x > 120)
			{
				obj->horizontalSpeed = -100.0 * speedAmplfierHor;
			}
			else
			{
				obj->horizontalSpeed = 0;
			}
		}
		else if (!collision(obj, rotation, pos))
		{
			obj->horizontalSpeed = 0;
		}
		if ((rotation == 1 || rotation == 2) && collision(obj, rotation, pos))
		{
			if (obj->positionInt.x - size.x * 30 > 120)
			{
				obj->horizontalSpeed = -100.0 * speedAmplfierHor;
			}
			else
			{
				obj->horizontalSpeed = 0;
			}
		}
		else if (!collision(obj, rotation, pos))
		{
			obj->horizontalSpeed = 0;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		int rotation = ((int)obj->brickSprite.getRotation() / 90) % 4;
		Vector2f size = getSize(obj->type, rotation);
		Vector2f pos;
		pos.x = obj->positionFloat.x + 30;
		pos.y = obj->positionFloat.y;
		pos.x = 30.0 * (int)(pos.x / 30);
		pos.y = 30.0 * (int)(pos.y / 30);
		if ((rotation == 0 || rotation == 3) && collision(obj, rotation, pos))
		{
			if (obj->positionInt.x + 30 * size.x < 1800)
			{
				obj->horizontalSpeed = 100.0 * speedAmplfierHor;
			}
			else
			{
				obj->horizontalSpeed = 0;
			}
		}
		else if (!collision(obj, rotation, pos))
		{
			obj->horizontalSpeed = 0;
		}
		if ((rotation == 1 || rotation == 2) && collision(obj, rotation, pos))
		{
			if (obj->positionInt.x < 1800)
			{
				obj->horizontalSpeed = 100.0 * speedAmplfierHor;
			}
			else
			{
				obj->horizontalSpeed = 0;
			}
		}
		else if (!collision(obj, rotation, pos))
		{
			obj->horizontalSpeed = 0;
		}
	}
	else
	{
		obj->horizontalSpeed = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		obj->fallSpeed = 150 * speedAmplfierVert;
	}
	else
	{
		obj->fallSpeed = 50 * speedAmplfierVert;
	}

	if (Keyboard::isKeyPressed(Keyboard::F12))
	{
		ToExit = 1;
		window->close();
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		pause(window);
	}


	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		p = 1;
	}
	if (event.type == Event::KeyReleased && event.key.code == Keyboard::R && p == 1)
	{
		if (tryRotate(obj) && obj->type != 2)
		{
			obj->brickSprite.rotate(90);
			if (obj->brickSprite.getRotation() == 90)
			{
				obj->positionFloat.x += 60;
			}
			if (obj->brickSprite.getRotation() == 180)
			{
				obj->positionFloat.y += 60;
			}
			if (obj->brickSprite.getRotation() == 270)
			{
				obj->positionFloat.x -= 60;
			}
			if (obj->brickSprite.getRotation() == 0)
			{
				obj->positionFloat.y -= 60;
			}
		}
		p = 0;
	}


	if (!start || !destroyed)
	{
		obj->horizontalSpeed = 0;
		obj->fallSpeed = 0;
	}


	float ddt = dt / 1000;

	for (int i = 0; ddt * i <= dt; i++)
	{
		obj->positionInt.x = 30.0 * (int)(obj->positionFloat.x / 30);
		obj->positionInt.y = 30.0 * (int)(obj->positionFloat.y / 30);

		Vector2f old = obj->positionInt;
		rotation = ((int)obj->brickSprite.getRotation() / 90) % 4;
		Vector2f pos1;
		pos1.x = old.x;
		pos1.y = old.y + 30;
		Vector2f moveLeft, moveRight;
		moveLeft = old;
		moveRight = old;
		moveLeft.x -= 30;
		moveRight.x += 30;

		if (!collision(obj, rotation, pos1))
		{
			if (Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) && collision(obj, rotation, moveRight))
			{
				old.x += 30;
				stop(obj, rotation, old);
				break;
			}
			else if (Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D) && collision(obj, rotation, moveLeft))
			{
				old.x -= 30;
				stop(obj, rotation, old);
				break;
			}
			else
			{
				stop(obj, rotation, old);
				break;
			}
		}
		else
		{
			obj->positionFloat.x += obj->horizontalSpeed * ddt;
			obj->positionFloat.y += obj->fallSpeed * ddt;
			obj->positionInt.x = 30.0 * (int)(obj->positionFloat.x / 30);
			obj->positionInt.y = 30.0 * (int)(obj->positionFloat.y / 30);
		}
	}
}

bool tryRotate(Brick* obj)
{
	int rotation = (obj->brickSprite.getRotation() + 90) / 90;
	Vector2f rotPos;
	rotPos = obj->positionInt;
	if (rotation % 4 == 0)
	{
		rotPos.y = obj->positionInt.y - 60;
		if (collision(obj, rotation, rotPos))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (rotation % 4 == 1)
	{
		rotPos.x = obj->positionInt.x + 60;
		if (collision(obj, rotation, rotPos))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (rotation % 4 == 2)
	{
		rotPos.y = obj->positionInt.y + 60;
		if (collision(obj, rotation, rotPos))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (rotation % 4 == 3)
	{
		rotPos.x = obj->positionInt.x - 60;
		if (collision(obj, rotation, rotPos))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;

}

bool collision(Brick* obj, int rotation, Vector2f rotPos)
{
	if (obj->type == 0)
	{
		if (rotation % 4 == 0)
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 2][(int)rotPos.y / 30 + 1] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		if (rotation % 4 == 1)
		{
			if (map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 + 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 2)
		{
			if (map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 - 3][(int)rotPos.y / 30 - 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 3)
		{
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 3] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	///////////////////
	if (obj->type == 1)
	{
		if (rotation % 4 == 0)
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 2][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 2][(int)rotPos.y / 30] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		if (rotation % 4 == 1)
		{
			if (map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 + 2] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 + 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 2)
		{
			if (map[(int)rotPos.x / 30 - 3][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 - 3][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 - 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 3)
		{
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 3] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 3] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	///////////////////
	if (obj->type == 2)
	{
		if (map[(int)rotPos.x / 30][(int)rotPos.y / 30] == -1 &&
			map[(int)rotPos.x / 30][(int)rotPos.y / 30 + 1] == -1 &&
			map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30] == -1 &&
			map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 + 1] == -1
			)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	///////////////////
	if (obj->type == 3)
	{
		if (rotation % 4 == 0)
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 + 2][(int)rotPos.y / 30] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		if (rotation % 4 == 1)
		{
			if (map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 + 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 2)
		{
			if (map[(int)rotPos.x / 30 - 3][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 - 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 3)
		{
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 3] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	///////////////////
	if (obj->type == 4)
	{
		if (rotation % 4 == 0)
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 + 2][(int)rotPos.y / 30 + 1] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		if (rotation % 4 == 1)
		{
			if (map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 + 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 2)
		{
			if (map[(int)rotPos.x / 30 - 3][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 - 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 3)
		{
			if (map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 3] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	///////////////////	
	if (obj->type == 5)
	{
		if (rotation % 4 == 0)
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 + 2][(int)rotPos.y / 30 + 1] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		if (rotation % 4 == 1)
		{
			if (map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 + 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 2)
		{
			if (map[(int)rotPos.x / 30 - 3][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 - 1] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 3)
		{
			if (map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 3] == -1 &&
				map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 2] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	///////////////////
	if (obj->type == 6)
	{
		if (rotation % 4 == 0)
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 + 1][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 + 2][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 + 3][(int)rotPos.y / 30] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		if (rotation % 4 == 1)
		{
			if (map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 + 1] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 + 2] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 + 3] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 2)
		{
			if (map[(int)rotPos.x / 30 - 4][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 - 3][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 - 2][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30 - 1][(int)rotPos.y / 30 - 1] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if (rotation % 4 == 3)
		{
			if (map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 1] == -1 &&
				map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 2] == -1 &&
				map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 3] == -1 &&
				map[(int)rotPos.x / 30][(int)rotPos.y / 30 - 4] == -1
				)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

Vector2f getSize(int type, int rotation)
{
	int width;
	int height;
	if (type == 6 && rotation % 2 == 0)
	{
		width = 4;
		height = 1;
	}
	else if (type == 2)
	{
		width = 2;
		height = 2;
	}
	else if (type != 6 && rotation % 2 != 0)
	{
		width = 2;
		height = 3;
	}
	else if (type == 6)
	{
		width = 1;
		height = 4;
	}
	else
	{
		width = 3;
		height = 2;
	}
	Vector2f size;
	size.x = (float)width;
	size.y = (float)height;
	return size;
}

void stop(Brick* obj, int rotation, Vector2f pos)
{
	created = 0;
	if (obj->type == 0)
	{
		if (rotation % 4 == 0)
		{
			map[(int)pos.x / 30][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 2][(int)pos.y / 30 + 1] = obj->color;
		}
		if (rotation % 4 == 1)
		{
			map[(int)pos.x / 30 - 1][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 + 2] = obj->color;
		}
		if (rotation % 4 == 2)
		{
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 - 3][(int)pos.y / 30 - 2] = obj->color;
		}
		if (rotation % 4 == 3)
		{
			map[(int)pos.x / 30][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 3] = obj->color;
		}
	}
	///////////////////
	if (obj->type == 1)
	{
		if (rotation % 4 == 0)
		{
			map[(int)pos.x / 30][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 2][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 2][(int)pos.y / 30] = obj->color;
		}
		if (rotation % 4 == 1)
		{
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 + 2] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 + 2] = obj->color;
		}
		if (rotation % 4 == 2)
		{
			map[(int)pos.x / 30 - 3][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 - 3][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 - 2] = obj->color;
		}
		if (rotation % 4 == 3)
		{
			map[(int)pos.x / 30][(int)pos.y / 30 - 3] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 3] = obj->color;
		}
	}
	///////////////////
	if (obj->type == 2)
	{
		map[(int)pos.x / 30][(int)pos.y / 30] = obj->color;
		map[(int)pos.x / 30][(int)pos.y / 30 + 1] = obj->color;
		map[(int)pos.x / 30 + 1][(int)pos.y / 30] = obj->color;
		map[(int)pos.x / 30 + 1][(int)pos.y / 30 + 1] = obj->color;
	}
	///////////////////
	if (obj->type == 3)
	{
		if (rotation % 4 == 0)
		{
			map[(int)pos.x / 30][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 + 2][(int)pos.y / 30] = obj->color;
		}
		if (rotation % 4 == 1)
		{
			map[(int)pos.x / 30 - 2][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 + 2] = obj->color;
		}
		if (rotation % 4 == 2)
		{
			map[(int)pos.x / 30 - 3][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 - 2] = obj->color;
		}
		if (rotation % 4 == 3)
		{
			map[(int)pos.x / 30][(int)pos.y / 30 - 3] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30][(int)pos.y / 30 - 2] = obj->color;
		}
	}
	///////////////////
	if (obj->type == 4)
	{
		if (rotation % 4 == 0)
		{
			map[(int)pos.x / 30][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 + 2][(int)pos.y / 30 + 1] = obj->color;
		}
		if (rotation % 4 == 1)
		{
			map[(int)pos.x / 30 - 2][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 + 2] = obj->color;
		}
		if (rotation % 4 == 2)
		{
			map[(int)pos.x / 30 - 3][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 - 2] = obj->color;
		}
		if (rotation % 4 == 3)
		{
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 3] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30][(int)pos.y / 30 - 2] = obj->color;
		}
	}
	///////////////////
	if (obj->type == 5)
	{
		if (rotation % 4 == 0)
		{
			map[(int)pos.x / 30][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 + 2][(int)pos.y / 30 + 1] = obj->color;
		}
		if (rotation % 4 == 1)
		{
			map[(int)pos.x / 30 - 1][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 + 2] = obj->color;
		}
		if (rotation % 4 == 2)
		{
			map[(int)pos.x / 30 - 3][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 - 1] = obj->color;
		}
		if (rotation % 4 == 3)
		{
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 3] = obj->color;
			map[(int)pos.x / 30][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30][(int)pos.y / 30 - 2] = obj->color;
		}
	}
	///////////////////
	if (obj->type == 6)
	{
		if (rotation % 4 == 0)
		{
			map[(int)pos.x / 30][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 + 1][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 + 2][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 + 3][(int)pos.y / 30] = obj->color;
		}
		if (rotation % 4 == 1)
		{
			map[(int)pos.x / 30 - 1][(int)pos.y / 30] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 + 1] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 + 2] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 + 3] = obj->color;
		}
		if (rotation % 4 == 2)
		{
			map[(int)pos.x / 30 - 4][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 - 3][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 - 2][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30 - 1][(int)pos.y / 30 - 1] = obj->color;
		}
		if (rotation % 4 == 3)
		{
			map[(int)pos.x / 30][(int)pos.y / 30 - 1] = obj->color;
			map[(int)pos.x / 30][(int)pos.y / 30 - 2] = obj->color;
			map[(int)pos.x / 30][(int)pos.y / 30 - 3] = obj->color;
			map[(int)pos.x / 30][(int)pos.y / 30 - 4] = obj->color;
		}
	}
}

void pause(RenderWindow* window)
{
	start = 0;
	Event event;
	Texture background;
	background.loadFromFile("MenuBack.png");
	Sprite back;
	back.setTexture(background);
	Texture settingsTexture;
	settingsTexture.loadFromFile("settings.png");
	int currentLine = 0;
	Sprite buttons1, buttons2, buttons3, buttons0;
	buttons0.setPosition(1500, 100);
	buttons0.setTexture(settingsTexture);
	buttons1.setPosition(1500, 1 * 200 + 100);
	buttons1.setTexture(settingsTexture);
	buttons2.setPosition(1500, 2 * 200 + 100);
	buttons2.setTexture(settingsTexture);
	buttons3.setPosition(1500, 3 * 200 + 100);
	buttons3.setTexture(settingsTexture);
	Brick tap;
	tap.type = 6;
	tap.color = rand() % 6;
	create(&tap);
	tap.brickSprite.setPosition(1300, 100 + 95.0 / 2 - 15);
	currentLine = 0;
	int a[5];
	for (int i = 0; i < 5; i++)
	{
		a[i] = 0;
	}


	Text text0, text1, text2, text3, tips;
	Font font;

	font.loadFromFile("CyrilicOld.ttf");
	text0.setFont(font);
	text0.setFillColor(Color::White);
	text0.setCharacterSize(50);

	text1.setFont(font);
	text1.setFillColor(Color::White);
	text1.setCharacterSize(50);

	text2.setFont(font);
	text2.setFillColor(Color::White);
	text2.setCharacterSize(50);

	text3.setFont(font);
	text3.setFillColor(Color::White);
	text3.setCharacterSize(25);

	tips.setFont(font);
	tips.setFillColor(Color::White);
	tips.setCharacterSize(50);
	tips.setString("W/S - выбрать параметр   A/D - выбрать значение   Tab - выход");
	tips.setPosition(500, 1000);

	Text label0, label1, label2, label3;

	label0.setFont(font);
	label0.setFillColor(Color::White);
	label0.setCharacterSize(30);
	label0.setPosition(1510, 60);
	label0.setString("Вертикальная скорость");

	label1.setFont(font);
	label1.setFillColor(Color::White);
	label1.setCharacterSize(30);
	label1.setPosition(1510, 260);
	label1.setString("Горизонтальная скорость");

	label2.setFont(font);
	label2.setFillColor(Color::White);
	label2.setCharacterSize(30);
	label2.setPosition(1510, 460);
	label2.setString("Громкость");

	label3.setFont(font);
	label3.setFillColor(Color::White);
	label3.setCharacterSize(30);
	label3.setPosition(1510, 660);
	label3.setString("Состояние души");



	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}
		int sp1 = (int)(speedAmplfierVert * 100);
		auto s1 = std::to_string(sp1 / 100);
		auto s11 = std::to_string(sp1 % 100);
		text0.setString(s1 + "." + s11);
		int sp2 = (int)(speedAmplfierHor * 100);
		auto s2 = std::to_string(sp2 / 100);
		auto s22 = std::to_string(sp2 % 100);
		text1.setString(s2 + "." + s22);
		auto s3 = std::to_string(volume);
		text2.setString(s3);
		text0.setPosition(1660, 105);
		text1.setPosition(1660, 305);
		text2.setPosition(1660, 505);
		text3.setPosition(1605, 725);

		if (peaceful)
		{
			text3.setString("    Спокойное");
		}
		else
		{
			text3.setString("     Широкое");
		}
		window->clear();
		window->draw(back);
		tap.brickSprite.setPosition(1300.0, 100.0 + 95.0 / 2 - 15.0 + 200.0 * currentLine);

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			a[0] = 1;
		}
		if (event.key.code == Keyboard::S && a[0] == 1)
		{
			a[0] = 0;
			currentLine++;
			currentLine = currentLine % 4;
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			a[1] = 1;
		}
		if (event.key.code == Keyboard::W && a[1] == 1)
		{
			a[1] = 0;
			currentLine--;
			if (currentLine < 0)
			{
				currentLine = 3;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			a[2] = 1;
		}
		if (event.key.code == Keyboard::D && a[2] == 1)
		{
			a[2] = 0;
			if (currentLine == 0)
			{
				speedAmplfierVert += 0.25;
				if (speedAmplfierVert > 4.0)
				{
					speedAmplfierVert = 4.0;
				}
			}
			if (currentLine == 1)
			{
				speedAmplfierHor += 0.25;
				if (speedAmplfierHor > 4.0)
				{
					speedAmplfierHor = 4.0;
				}
			}
			if (currentLine == 2)
			{
				volume += 10;
				if (volume > 100)
				{
					volume = 100;
				}
				for (int i = 0; i < 5; i++)
				{
					theme[i].setVolume((float)volume);
				}
			}
			if (currentLine == 3)
			{
				peaceful = !peaceful;
				if (peaceful)
				{
					theme[song].pause();
					theme[4].play();
				}
				else
				{
					theme[song].play();
					theme[4].stop();
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			a[3] = 1;
		}
		if (event.key.code == Keyboard::A && a[3] == 1)
		{
			a[3] = 0;
			if (currentLine == 0)
			{
				speedAmplfierVert -= 0.25;
				if (speedAmplfierVert < 1.0)
				{
					speedAmplfierVert = 1.0;
				}
			}
			if (currentLine == 1)
			{
				speedAmplfierHor -= 0.25;
				if (speedAmplfierHor < 1.0)
				{
					speedAmplfierHor = 1.0;
				}
			}
			if (currentLine == 2)
			{
				volume -= 10;
				if (volume < 0)
				{
					volume = 0;
				}
				for (int i = 0; i < 5; i++)
				{
					theme[i].setVolume((float)volume);
				}
			}
			if (currentLine == 3)
			{
				peaceful = !peaceful;
				if (peaceful)
				{
					theme[song].pause();
					theme[4].play();
				}
				else
				{
					theme[song].play();
					theme[4].stop();
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Tab))
		{
			a[4] = 1;
		}
		if (event.key.code == Keyboard::Tab && a[4] == 1)
		{
			{
				a[4] = 0;
				break;
			}
		}

		window->draw(buttons0);
		window->draw(buttons1);
		window->draw(buttons2);
		window->draw(buttons3);

		window->draw(text0);
		window->draw(text1);
		window->draw(text2);
		window->draw(text3);

		window->draw(tips);

		window->draw(label0);
		window->draw(label1);
		window->draw(label2);
		window->draw(label3);

		window->draw(tap.brickSprite);
		window->display();
	}

}

void initialize()
{
	brick[0].loadFromFile("Brick0.jpg");
	brick[1].loadFromFile("Brick1.jpg");
	brick[2].loadFromFile("Brick2.jpg");
	brick[3].loadFromFile("Brick3.jpg");
	brick[4].loadFromFile("Brick4.jpg");
	brick[5].loadFromFile("Brick5.jpg");
	pattern.loadFromFile("Pattern.png");
}

void optimization(Texture* video, int fr)
{
	if (!peaceful)
	{
		if (fr == 0)
			video->loadFromFile("0001.jpg");
		if (fr == 1)
			video->loadFromFile("0002.jpg");
		if (fr == 2)
			video->loadFromFile("0003.jpg");
		if (fr == 3)
			video->loadFromFile("0004.jpg");
		if (fr == 4)
			video->loadFromFile("0005.jpg");
		if (fr == 5)
			video->loadFromFile("0006.jpg");
		if (fr == 6)
			video->loadFromFile("0007.jpg");
		if (fr == 7)
			video->loadFromFile("0008.jpg");
		if (fr == 8)
			video->loadFromFile("0009.jpg");
		if (fr == 9)
			video->loadFromFile("0010.jpg");
		if (fr == 10)
			video->loadFromFile("0011.jpg");
		if (fr == 11)
			video->loadFromFile("0012.jpg");
		if (fr == 12)
			video->loadFromFile("0013.jpg");
		if (fr == 13)
			video->loadFromFile("0014.jpg");
		if (fr == 14)
			video->loadFromFile("0015.jpg");
		if (fr == 15)
			video->loadFromFile("0016.jpg");
		if (fr == 16)
			video->loadFromFile("0017.jpg");
		if (fr == 17)
			video->loadFromFile("0018.jpg");
		if (fr == 18)
			video->loadFromFile("0019.jpg");
		if (fr == 19)
			video->loadFromFile("0020.jpg");
		if (fr == 20)
			video->loadFromFile("0021.jpg");
		if (fr == 21)
			video->loadFromFile("0022.jpg");
		if (fr == 22)
			video->loadFromFile("0023.jpg");
		if (fr == 23)
			video->loadFromFile("0024.jpg");
		if (fr == 24)
			video->loadFromFile("0025.jpg");
		if (fr == 25)
			video->loadFromFile("0026.jpg");
		if (fr == 26)
			video->loadFromFile("0027.jpg");
		if (fr == 27)
			video->loadFromFile("0028.jpg");
		if (fr == 28)
			video->loadFromFile("0029.jpg");
		if (fr == 29)
			video->loadFromFile("0030.jpg");
		if (fr == 30)
			video->loadFromFile("0031.jpg");
		if (fr == 31)
			video->loadFromFile("0032.jpg");
		if (fr == 32)
			video->loadFromFile("0033.jpg");
		if (fr == 33)
			video->loadFromFile("0034.jpg");
		if (fr == 34)
			video->loadFromFile("0035.jpg");
		if (fr == 35)
			video->loadFromFile("0036.jpg");
		if (fr == 36)
			video->loadFromFile("0037.jpg");
		if (fr == 37)
			video->loadFromFile("0038.jpg");
		if (fr == 38)
			video->loadFromFile("0039.jpg");
		if (fr == 39)
			video->loadFromFile("0040.jpg");
		if (fr == 40)
			video->loadFromFile("0041.jpg");
		if (fr == 41)
			video->loadFromFile("0042.jpg");
		if (fr == 42)
			video->loadFromFile("0043.jpg");
		if (fr == 43)
			video->loadFromFile("0044.jpg");
		if (fr == 44)
			video->loadFromFile("0045.jpg");
		if (fr == 45)
			video->loadFromFile("0046.jpg");
		if (fr == 46)
			video->loadFromFile("0047.jpg");
		if (fr == 47)
			video->loadFromFile("0048.jpg");
		if (fr == 48)
			video->loadFromFile("0049.jpg");
		if (fr == 49)
			video->loadFromFile("0050.jpg");
		if (fr == 50)
			video->loadFromFile("0051.jpg");
		if (fr == 51)
			video->loadFromFile("0052.jpg");
		if (fr == 52)
			video->loadFromFile("0053.jpg");
		if (fr == 53)
			video->loadFromFile("0054.jpg");
		if (fr == 54)
			video->loadFromFile("0055.jpg");
		if (fr == 55)
			video->loadFromFile("0056.jpg");
		if (fr == 56)
			video->loadFromFile("0057.jpg");
		if (fr == 57)
			video->loadFromFile("0058.jpg");
		if (fr == 58)
			video->loadFromFile("0059.jpg");
		if (fr == 59)
			video->loadFromFile("0060.jpg");
		if (fr == 60)
			video->loadFromFile("0061.jpg");
		if (fr == 61)
			video->loadFromFile("0062.jpg");
		if (fr == 62)
			video->loadFromFile("0063.jpg");
		if (fr == 63)
			video->loadFromFile("0064.jpg");
		if (fr == 64)
			video->loadFromFile("0065.jpg");
		if (fr == 65)
			video->loadFromFile("0066.jpg");
		if (fr == 66)
			video->loadFromFile("0067.jpg");
		if (fr == 67)
			video->loadFromFile("0068.jpg");
		if (fr == 68)
			video->loadFromFile("0069.jpg");
		if (fr == 69)
			video->loadFromFile("0070.jpg");
		if (fr == 70)
			video->loadFromFile("0071.jpg");
		if (fr == 71)
			video->loadFromFile("0072.jpg");
		if (fr == 72)
			video->loadFromFile("0073.jpg");
		if (fr == 73)
			video->loadFromFile("0074.jpg");
		if (fr == 74)
			video->loadFromFile("0075.jpg");
		if (fr == 75)
			video->loadFromFile("0076.jpg");
		if (fr == 76)
			video->loadFromFile("0077.jpg");
		if (fr == 77)
			video->loadFromFile("0078.jpg");
		if (fr == 78)
			video->loadFromFile("0079.jpg");
		if (fr == 79)
			video->loadFromFile("0080.jpg");
		if (fr == 80)
			video->loadFromFile("0081.jpg");
		if (fr == 81)
			video->loadFromFile("0082.jpg");
		if (fr == 82)
			video->loadFromFile("0083.jpg");
		if (fr == 83)
			video->loadFromFile("0084.jpg");
		if (fr == 84)
			video->loadFromFile("0085.jpg");
		if (fr == 85)
			video->loadFromFile("0086.jpg");
		if (fr == 86)
			video->loadFromFile("0087.jpg");
		if (fr == 87)
			video->loadFromFile("0088.jpg");
		if (fr == 88)
			video->loadFromFile("0089.jpg");
		if (fr == 89)
			video->loadFromFile("0090.jpg");
		if (fr == 90)
			video->loadFromFile("0091.jpg");
		if (fr == 91)
			video->loadFromFile("0092.jpg");
		if (fr == 92)
			video->loadFromFile("0093.jpg");
		if (fr == 93)
			video->loadFromFile("0094.jpg");
		if (fr == 94)
			video->loadFromFile("0095.jpg");
		if (fr == 95)
			video->loadFromFile("0096.jpg");
		if (fr == 96)
			video->loadFromFile("0097.jpg");
		if (fr == 97)
			video->loadFromFile("0098.jpg");
		if (fr == 98)
			video->loadFromFile("0099.jpg");
		if (fr == 99)
			video->loadFromFile("0100.jpg");
		if (fr == 100)
			video->loadFromFile("0101.jpg");
		if (fr == 101)
			video->loadFromFile("0102.jpg");
		if (fr == 102)
			video->loadFromFile("0103.jpg");
		if (fr == 103)
			video->loadFromFile("0104.jpg");
		if (fr == 104)
			video->loadFromFile("0105.jpg");
		if (fr == 105)
			video->loadFromFile("0106.jpg");
		if (fr == 106)
			video->loadFromFile("0107.jpg");
		if (fr == 107)
			video->loadFromFile("0108.jpg");
		if (fr == 108)
			video->loadFromFile("0109.jpg");
		if (fr == 109)
			video->loadFromFile("0110.jpg");
		if (fr == 110)
			video->loadFromFile("0111.jpg");
		if (fr == 111)
			video->loadFromFile("0112.jpg");
		if (fr == 112)
			video->loadFromFile("0113.jpg");
		if (fr == 113)
			video->loadFromFile("0114.jpg");
		if (fr == 114)
			video->loadFromFile("0115.jpg");
		if (fr == 115)
			video->loadFromFile("0116.jpg");
		if (fr == 116)
			video->loadFromFile("0117.jpg");
		if (fr == 117)
			video->loadFromFile("0118.jpg");
		if (fr == 118)
			video->loadFromFile("0119.jpg");
		if (fr == 119)
			video->loadFromFile("0120.jpg");
		if (fr == 120)
			video->loadFromFile("0121.jpg");
		if (fr == 121)
			video->loadFromFile("0122.jpg");
		if (fr == 122)
			video->loadFromFile("0123.jpg");
		if (fr == 123)
			video->loadFromFile("0124.jpg");
		if (fr == 124)
			video->loadFromFile("0125.jpg");
		if (fr == 125)
			video->loadFromFile("0126.jpg");
		if (fr == 126)
			video->loadFromFile("0127.jpg");
		if (fr == 127)
			video->loadFromFile("0128.jpg");
		if (fr == 128)
			video->loadFromFile("0129.jpg");
		if (fr == 129)
			video->loadFromFile("0130.jpg");
		if (fr == 130)
			video->loadFromFile("0131.jpg");
		if (fr == 131)
			video->loadFromFile("0132.jpg");
		if (fr == 132)
			video->loadFromFile("0133.jpg");
		if (fr == 133)
			video->loadFromFile("0134.jpg");
		if (fr == 134)
			video->loadFromFile("0135.jpg");
		if (fr == 135)
			video->loadFromFile("0136.jpg");
		if (fr == 136)
			video->loadFromFile("0137.jpg");
		if (fr == 137)
			video->loadFromFile("0138.jpg");
		if (fr == 138)
			video->loadFromFile("0139.jpg");
		if (fr == 139)
			video->loadFromFile("0140.jpg");
		if (fr == 140)
			video->loadFromFile("0141.jpg");
		if (fr == 141)
			video->loadFromFile("0142.jpg");
		if (fr == 142)
			video->loadFromFile("0143.jpg");
		if (fr == 143)
			video->loadFromFile("0144.jpg");
		if (fr == 144)
			video->loadFromFile("0145.jpg");
		if (fr == 145)
			video->loadFromFile("0146.jpg");
		if (fr == 146)
			video->loadFromFile("0147.jpg");
		if (fr == 147)
			video->loadFromFile("0148.jpg");
		if (fr == 148)
			video->loadFromFile("0149.jpg");
		if (fr == 149)
			video->loadFromFile("0150.jpg");
		if (fr == 150)
			video->loadFromFile("0151.jpg");
		if (fr == 151)
			video->loadFromFile("0152.jpg");
		if (fr == 152)
			video->loadFromFile("0153.jpg");
		if (fr == 153)
			video->loadFromFile("0154.jpg");
		if (fr == 154)
			video->loadFromFile("0155.jpg");
		if (fr == 155)
			video->loadFromFile("0156.jpg");
		if (fr == 156)
			video->loadFromFile("0157.jpg");
		if (fr == 157)
			video->loadFromFile("0158.jpg");
		if (fr == 158)
			video->loadFromFile("0159.jpg");
		if (fr == 159)
			video->loadFromFile("0160.jpg");
		if (fr == 160)
			video->loadFromFile("0161.jpg");
		if (fr == 161)
			video->loadFromFile("0162.jpg");
		if (fr == 162)
			video->loadFromFile("0163.jpg");
		if (fr == 163)
			video->loadFromFile("0164.jpg");
		if (fr == 164)
			video->loadFromFile("0165.jpg");
		if (fr == 165)
			video->loadFromFile("0166.jpg");
		if (fr == 166)
			video->loadFromFile("0167.jpg");
		if (fr == 167)
			video->loadFromFile("0168.jpg");
		if (fr == 168)
			video->loadFromFile("0169.jpg");
		if (fr == 169)
			video->loadFromFile("0170.jpg");
		if (fr == 170)
			video->loadFromFile("0171.jpg");
		if (fr == 171)
			video->loadFromFile("0172.jpg");
		if (fr == 172)
			video->loadFromFile("0173.jpg");
		if (fr == 173)
			video->loadFromFile("0174.jpg");
		if (fr == 174)
			video->loadFromFile("0175.jpg");
		if (fr == 175)
			video->loadFromFile("0176.jpg");
		if (fr == 176)
			video->loadFromFile("0177.jpg");
		if (fr == 177)
			video->loadFromFile("0178.jpg");
		if (fr == 178)
			video->loadFromFile("0179.jpg");
		if (fr == 179)
			video->loadFromFile("0180.jpg");
		if (fr == 180)
			video->loadFromFile("0181.jpg");
		if (fr == 181)
			video->loadFromFile("0182.jpg");
		if (fr == 182)
			video->loadFromFile("0183.jpg");
		if (fr == 183)
			video->loadFromFile("0184.jpg");
		if (fr == 184)
			video->loadFromFile("0185.jpg");
		if (fr == 185)
			video->loadFromFile("0186.jpg");
		if (fr == 186)
			video->loadFromFile("0187.jpg");
		if (fr == 187)
			video->loadFromFile("0188.jpg");
		if (fr == 188)
			video->loadFromFile("0189.jpg");
		if (fr == 189)
			video->loadFromFile("0190.jpg");
		if (fr == 190)
			video->loadFromFile("0191.jpg");
		if (fr == 191)
			video->loadFromFile("0192.jpg");
		if (fr == 192)
			video->loadFromFile("0193.jpg");
		if (fr == 193)
			video->loadFromFile("0194.jpg");
		if (fr == 194)
			video->loadFromFile("0195.jpg");
		if (fr == 195)
			video->loadFromFile("0196.jpg");
		if (fr == 196)
			video->loadFromFile("0197.jpg");
		if (fr == 197)
			video->loadFromFile("0198.jpg");
		if (fr == 198)
			video->loadFromFile("0199.jpg");
		if (fr == 199)
			video->loadFromFile("0200.jpg");
		if (fr == 200)
			video->loadFromFile("0201.jpg");
		if (fr == 201)
			video->loadFromFile("0202.jpg");
		if (fr == 202)
			video->loadFromFile("0203.jpg");
		if (fr == 203)
			video->loadFromFile("0204.jpg");
		if (fr == 204)
			video->loadFromFile("0205.jpg");
		if (fr == 205)
			video->loadFromFile("0206.jpg");
		if (fr == 206)
			video->loadFromFile("0207.jpg");
		if (fr == 207)
			video->loadFromFile("0208.jpg");
		if (fr == 208)
			video->loadFromFile("0209.jpg");
		if (fr == 209)
			video->loadFromFile("0210.jpg");
		if (fr == 210)
			video->loadFromFile("0211.jpg");
		if (fr == 211)
			video->loadFromFile("0212.jpg");
		if (fr == 212)
			video->loadFromFile("0213.jpg");
		if (fr == 213)
			video->loadFromFile("0214.jpg");
		if (fr == 214)
			video->loadFromFile("0215.jpg");
		if (fr == 215)
			video->loadFromFile("0216.jpg");
		if (fr == 216)
			video->loadFromFile("0217.jpg");
		if (fr == 217)
			video->loadFromFile("0218.jpg");
		if (fr == 218)
			video->loadFromFile("0219.jpg");
		if (fr == 219)
			video->loadFromFile("0220.jpg");
		if (fr == 220)
			video->loadFromFile("0221.jpg");
		if (fr == 221)
			video->loadFromFile("0222.jpg");
		if (fr == 222)
			video->loadFromFile("0223.jpg");
		if (fr == 223)
			video->loadFromFile("0224.jpg");
		if (fr == 224)
			video->loadFromFile("0225.jpg");
		if (fr == 225)
			video->loadFromFile("0226.jpg");
		if (fr == 226)
			video->loadFromFile("0227.jpg");
		if (fr == 227)
			video->loadFromFile("0228.jpg");
		if (fr == 228)
			video->loadFromFile("0229.jpg");
		if (fr == 229)
			video->loadFromFile("0230.jpg");
		if (fr == 230)
			video->loadFromFile("0231.jpg");
		if (fr == 231)
			video->loadFromFile("0232.jpg");
		if (fr == 232)
			video->loadFromFile("0233.jpg");
		if (fr == 233)
			video->loadFromFile("0234.jpg");
		if (fr == 234)
			video->loadFromFile("0235.jpg");
		if (fr == 235)
			video->loadFromFile("0236.jpg");
		if (fr == 236)
			video->loadFromFile("0237.jpg");
		if (fr == 237)
			video->loadFromFile("0238.jpg");
		if (fr == 238)
			video->loadFromFile("0239.jpg");
		if (fr == 239)
			video->loadFromFile("0240.jpg");
		if (fr == 240)
			video->loadFromFile("0241.jpg");
		if (fr == 241)
			video->loadFromFile("0242.jpg");
		if (fr == 242)
			video->loadFromFile("0243.jpg");
		if (fr == 243)
			video->loadFromFile("0244.jpg");
		if (fr == 244)
			video->loadFromFile("0245.jpg");
		if (fr == 245)
			video->loadFromFile("0246.jpg");
		if (fr == 246)
			video->loadFromFile("0247.jpg");
		if (fr == 247)
			video->loadFromFile("0248.jpg");
		if (fr == 248)
			video->loadFromFile("0249.jpg");
		if (fr == 249)
			video->loadFromFile("0250.jpg");
		if (fr == 250)
			video->loadFromFile("0251.jpg");
		if (fr == 251)
			video->loadFromFile("0252.jpg");
		if (fr == 252)
			video->loadFromFile("0253.jpg");
		if (fr == 253)
			video->loadFromFile("0254.jpg");
		if (fr == 254)
			video->loadFromFile("0255.jpg");
		if (fr == 255)
			video->loadFromFile("0256.jpg");
		if (fr == 256)
			video->loadFromFile("0257.jpg");
		if (fr == 257)
			video->loadFromFile("0258.jpg");
		if (fr == 258)
			video->loadFromFile("0259.jpg");
		if (fr == 259)
			video->loadFromFile("0260.jpg");
		if (fr == 260)
			video->loadFromFile("0261.jpg");
		if (fr == 261)
			video->loadFromFile("0262.jpg");
		if (fr == 262)
			video->loadFromFile("0263.jpg");
		if (fr == 263)
			video->loadFromFile("0264.jpg");
		if (fr == 264)
			video->loadFromFile("0265.jpg");
		if (fr == 265)
			video->loadFromFile("0266.jpg");
		if (fr == 266)
			video->loadFromFile("0267.jpg");
		if (fr == 267)
			video->loadFromFile("0268.jpg");
		if (fr == 268)
			video->loadFromFile("0269.jpg");
		if (fr == 269)
			video->loadFromFile("0270.jpg");
		if (fr == 270)
			video->loadFromFile("0271.jpg");
		if (fr == 271)
			video->loadFromFile("0272.jpg");
		if (fr == 272)
			video->loadFromFile("0273.jpg");
		if (fr == 273)
			video->loadFromFile("0274.jpg");
		if (fr == 274)
			video->loadFromFile("0275.jpg");
		if (fr == 275)
			video->loadFromFile("0276.jpg");
		if (fr == 276)
			video->loadFromFile("0277.jpg");
		if (fr == 277)
			video->loadFromFile("0278.jpg");
		if (fr == 278)
			video->loadFromFile("0279.jpg");
		if (fr == 279)
			video->loadFromFile("0280.jpg");
		if (fr == 280)
			video->loadFromFile("0281.jpg");
		if (fr == 281)
			video->loadFromFile("0282.jpg");
		if (fr == 282)
			video->loadFromFile("0283.jpg");
		if (fr == 283)
			video->loadFromFile("0284.jpg");
		if (fr == 284)
			video->loadFromFile("0285.jpg");
		if (fr == 285)
			video->loadFromFile("0286.jpg");
		if (fr == 286)
			video->loadFromFile("0287.jpg");
		if (fr == 287)
			video->loadFromFile("0288.jpg");
		if (fr == 288)
			video->loadFromFile("0289.jpg");
		if (fr == 289)
			video->loadFromFile("0290.jpg");
		if (fr == 290)
			video->loadFromFile("0291.jpg");
		if (fr == 291)
			video->loadFromFile("0292.jpg");
		if (fr == 292)
			video->loadFromFile("0293.jpg");
		if (fr == 293)
			video->loadFromFile("0294.jpg");
		if (fr == 294)
			video->loadFromFile("0295.jpg");
		if (fr == 295)
			video->loadFromFile("0296.jpg");
		if (fr == 296)
			video->loadFromFile("0297.jpg");
		if (fr == 297)
			video->loadFromFile("0298.jpg");
		if (fr == 298)
			video->loadFromFile("0299.jpg");
		if (fr == 299)
			video->loadFromFile("0300.jpg");
		if (fr == 300)
			video->loadFromFile("0301.jpg");
		if (fr == 301)
			video->loadFromFile("0302.jpg");
		if (fr == 302)
			video->loadFromFile("0303.jpg");
		if (fr == 303)
			video->loadFromFile("0304.jpg");
		if (fr == 304)
			video->loadFromFile("0305.jpg");
		if (fr == 305)
			video->loadFromFile("0306.jpg");
		if (fr == 306)
			video->loadFromFile("0307.jpg");
		if (fr == 307)
			video->loadFromFile("0308.jpg");
		if (fr == 308)
			video->loadFromFile("0309.jpg");
		if (fr == 309)
			video->loadFromFile("0310.jpg");
		if (fr == 310)
			video->loadFromFile("0311.jpg");
		if (fr == 311)
			video->loadFromFile("0312.jpg");
		if (fr == 312)
			video->loadFromFile("0313.jpg");
		if (fr == 313)
			video->loadFromFile("0314.jpg");
		if (fr == 314)
			video->loadFromFile("0315.jpg");
		if (fr == 315)
			video->loadFromFile("0316.jpg");
		if (fr == 316)
			video->loadFromFile("0317.jpg");
		if (fr == 317)
			video->loadFromFile("0318.jpg");
		if (fr == 318)
			video->loadFromFile("0319.jpg");
		if (fr == 319)
			video->loadFromFile("0320.jpg");
		if (fr == 320)
			video->loadFromFile("0321.jpg");
		if (fr == 321)
			video->loadFromFile("0322.jpg");
		if (fr == 322)
			video->loadFromFile("0323.jpg");
		if (fr == 323)
			video->loadFromFile("0324.jpg");
		if (fr == 324)
			video->loadFromFile("0325.jpg");
		if (fr == 325)
			video->loadFromFile("0326.jpg");
		if (fr == 326)
			video->loadFromFile("0327.jpg");
		if (fr == 327)
			video->loadFromFile("0328.jpg");
		if (fr == 328)
			video->loadFromFile("0329.jpg");
		if (fr == 329)
			video->loadFromFile("0330.jpg");
		if (fr == 330)
			video->loadFromFile("0331.jpg");
		if (fr == 331)
			video->loadFromFile("0332.jpg");
		if (fr == 332)
			video->loadFromFile("0333.jpg");
		if (fr == 333)
			video->loadFromFile("0334.jpg");
		if (fr == 334)
			video->loadFromFile("0335.jpg");
		if (fr == 335)
			video->loadFromFile("0336.jpg");
		if (fr == 336)
			video->loadFromFile("0337.jpg");
		if (fr == 337)
			video->loadFromFile("0338.jpg");
		if (fr == 338)
			video->loadFromFile("0339.jpg");
		if (fr == 339)
			video->loadFromFile("0340.jpg");
		if (fr == 340)
			video->loadFromFile("0341.jpg");
		if (fr == 341)
			video->loadFromFile("0342.jpg");
		if (fr == 342)
			video->loadFromFile("0343.jpg");
		if (fr == 343)
			video->loadFromFile("0344.jpg");
		if (fr == 344)
			video->loadFromFile("0345.jpg");
		if (fr == 345)
			video->loadFromFile("0346.jpg");
		if (fr == 346)
			video->loadFromFile("0347.jpg");
		if (fr == 347)
			video->loadFromFile("0348.jpg");
		if (fr == 348)
			video->loadFromFile("0349.jpg");
		if (fr == 349)
			video->loadFromFile("0350.jpg");
		if (fr == 350)
			video->loadFromFile("0351.jpg");
		if (fr == 351)
			video->loadFromFile("0352.jpg");
		if (fr == 352)
			video->loadFromFile("0353.jpg");
		if (fr == 353)
			video->loadFromFile("0354.jpg");
		if (fr == 354)
			video->loadFromFile("0355.jpg");
		if (fr == 355)
			video->loadFromFile("0356.jpg");
		if (fr == 356)
			video->loadFromFile("0357.jpg");
		if (fr == 357)
			video->loadFromFile("0358.jpg");
		if (fr == 358)
			video->loadFromFile("0359.jpg");
		if (fr == 359)
			video->loadFromFile("0360.jpg");
		if (fr == 360)
			video->loadFromFile("0361.jpg");
		if (fr == 361)
			video->loadFromFile("0362.jpg");
		if (fr == 362)
			video->loadFromFile("0363.jpg");
		if (fr == 363)
			video->loadFromFile("0364.jpg");
		if (fr == 364)
			video->loadFromFile("0365.jpg");
		if (fr == 365)
			video->loadFromFile("0366.jpg");
		if (fr == 366)
			video->loadFromFile("0367.jpg");
		if (fr == 367)
			video->loadFromFile("0368.jpg");
		if (fr == 368)
			video->loadFromFile("0369.jpg");
		if (fr == 369)
			video->loadFromFile("0370.jpg");
		if (fr == 370)
			video->loadFromFile("0371.jpg");
		if (fr == 371)
			video->loadFromFile("0372.jpg");
		if (fr == 372)
			video->loadFromFile("0373.jpg");
		if (fr == 373)
			video->loadFromFile("0374.jpg");
		if (fr == 374)
			video->loadFromFile("0375.jpg");
		if (fr == 375)
			video->loadFromFile("0376.jpg");
		if (fr == 376)
			video->loadFromFile("0377.jpg");
		if (fr == 377)
			video->loadFromFile("0378.jpg");
		if (fr == 378)
			video->loadFromFile("0379.jpg");
		if (fr == 379)
			video->loadFromFile("0380.jpg");
		if (fr == 380)
			video->loadFromFile("0381.jpg");
		if (fr == 381)
			video->loadFromFile("0382.jpg");
		if (fr == 382)
			video->loadFromFile("0383.jpg");
		if (fr == 383)
			video->loadFromFile("0384.jpg");
		if (fr == 384)
			video->loadFromFile("0385.jpg");
		if (fr == 385)
			video->loadFromFile("0386.jpg");
		if (fr == 386)
			video->loadFromFile("0387.jpg");
		if (fr == 387)
			video->loadFromFile("0388.jpg");
		if (fr == 388)
			video->loadFromFile("0389.jpg");
		if (fr == 389)
			video->loadFromFile("0390.jpg");
		if (fr == 390)
			video->loadFromFile("0391.jpg");
		if (fr == 391)
			video->loadFromFile("0392.jpg");
		if (fr == 392)
			video->loadFromFile("0393.jpg");
		if (fr == 393)
			video->loadFromFile("0394.jpg");
		if (fr == 394)
			video->loadFromFile("0395.jpg");
		if (fr == 395)
			video->loadFromFile("0396.jpg");
		if (fr == 396)
			video->loadFromFile("0397.jpg");
		if (fr == 397)
			video->loadFromFile("0398.jpg");
		if (fr == 398)
			video->loadFromFile("0399.jpg");
		if (fr == 399)
			video->loadFromFile("0400.jpg");
		if (fr == 400)
			video->loadFromFile("0401.jpg");
		if (fr == 401)
			video->loadFromFile("0402.jpg");
		if (fr == 402)
			video->loadFromFile("0403.jpg");
		if (fr == 403)
			video->loadFromFile("0404.jpg");
		if (fr == 404)
			video->loadFromFile("0405.jpg");
		if (fr == 405)
			video->loadFromFile("0406.jpg");
		if (fr == 406)
			video->loadFromFile("0407.jpg");
		if (fr == 407)
			video->loadFromFile("0408.jpg");
		if (fr == 408)
			video->loadFromFile("0409.jpg");
		if (fr == 409)
			video->loadFromFile("0410.jpg");
		if (fr == 410)
			video->loadFromFile("0411.jpg");
		if (fr == 411)
			video->loadFromFile("0412.jpg");
		if (fr == 412)
			video->loadFromFile("0413.jpg");
		if (fr == 413)
			video->loadFromFile("0414.jpg");
		if (fr == 414)
			video->loadFromFile("0415.jpg");
		if (fr == 415)
			video->loadFromFile("0416.jpg");
		if (fr == 416)
			video->loadFromFile("0417.jpg");
		if (fr == 417)
			video->loadFromFile("0418.jpg");
		if (fr == 418)
			video->loadFromFile("0419.jpg");
		if (fr == 419)
			video->loadFromFile("0420.jpg");
		if (fr == 420)
			video->loadFromFile("0421.jpg");
		if (fr == 421)
			video->loadFromFile("0422.jpg");
		if (fr == 422)
			video->loadFromFile("0423.jpg");
		if (fr == 423)
			video->loadFromFile("0424.jpg");
		if (fr == 424)
			video->loadFromFile("0425.jpg");
		if (fr == 425)
			video->loadFromFile("0426.jpg");
		if (fr == 426)
			video->loadFromFile("0427.jpg");
		if (fr == 427)
			video->loadFromFile("0428.jpg");
		if (fr == 428)
			video->loadFromFile("0429.jpg");
		if (fr == 429)
			video->loadFromFile("0430.jpg");
		if (fr == 430)
			video->loadFromFile("0431.jpg");
		if (fr == 431)
			video->loadFromFile("0432.jpg");
		if (fr == 432)
			video->loadFromFile("0433.jpg");
		if (fr == 433)
			video->loadFromFile("0434.jpg");
		if (fr == 434)
			video->loadFromFile("0435.jpg");
		if (fr == 435)
			video->loadFromFile("0436.jpg");
		if (fr == 436)
			video->loadFromFile("0437.jpg");
		if (fr == 437)
			video->loadFromFile("0438.jpg");
		if (fr == 438)
			video->loadFromFile("0439.jpg");
		if (fr == 439)
			video->loadFromFile("0440.jpg");
		if (fr == 440)
			video->loadFromFile("0441.jpg");
		if (fr == 441)
			video->loadFromFile("0442.jpg");
		if (fr == 442)
			video->loadFromFile("0443.jpg");
		if (fr == 443)
			video->loadFromFile("0444.jpg");
		if (fr == 444)
			video->loadFromFile("0445.jpg");
		if (fr == 445)
			video->loadFromFile("0446.jpg");
		if (fr == 446)
			video->loadFromFile("0447.jpg");
		if (fr == 447)
			video->loadFromFile("0448.jpg");
		if (fr == 448)
			video->loadFromFile("0449.jpg");
		if (fr == 449)
			video->loadFromFile("0450.jpg");
		if (fr == 450)
			video->loadFromFile("0451.jpg");
		if (fr == 451)
			video->loadFromFile("0452.jpg");
		if (fr == 452)
			video->loadFromFile("0453.jpg");
		if (fr == 453)
			video->loadFromFile("0454.jpg");
		if (fr == 454)
			video->loadFromFile("0455.jpg");
		if (fr == 455)
			video->loadFromFile("0456.jpg");
		if (fr == 456)
			video->loadFromFile("0457.jpg");
		if (fr == 457)
			video->loadFromFile("0458.jpg");
		if (fr == 458)
			video->loadFromFile("0459.jpg");
		if (fr == 459)
			video->loadFromFile("0460.jpg");
		if (fr == 460)
			video->loadFromFile("0461.jpg");
		if (fr == 461)
			video->loadFromFile("0462.jpg");
		if (fr == 462)
			video->loadFromFile("0463.jpg");
		if (fr == 463)
			video->loadFromFile("0464.jpg");
		if (fr == 464)
			video->loadFromFile("0465.jpg");
		if (fr == 465)
			video->loadFromFile("0466.jpg");
		if (fr == 466)
			video->loadFromFile("0467.jpg");
		if (fr == 467)
			video->loadFromFile("0468.jpg");
		if (fr == 468)
			video->loadFromFile("0469.jpg");
		if (fr == 469)
			video->loadFromFile("0470.jpg");
		if (fr == 470)
			video->loadFromFile("0471.jpg");
		if (fr == 471)
			video->loadFromFile("0472.jpg");
		if (fr == 472)
			video->loadFromFile("0473.jpg");
		if (fr == 473)
			video->loadFromFile("0474.jpg");
		if (fr == 474)
			video->loadFromFile("0475.jpg");
		if (fr == 475)
			video->loadFromFile("0476.jpg");
		if (fr == 476)
			video->loadFromFile("0477.jpg");
		if (fr == 477)
			video->loadFromFile("0478.jpg");
		if (fr == 478)
			video->loadFromFile("0479.jpg");
		if (fr == 479)
			video->loadFromFile("0480.jpg");
		if (fr == 480)
			video->loadFromFile("0481.jpg");
		if (fr == 481)
			video->loadFromFile("0482.jpg");
		if (fr == 482)
			video->loadFromFile("0483.jpg");
		if (fr == 483)
			video->loadFromFile("0484.jpg");
		if (fr == 484)
			video->loadFromFile("0485.jpg");
		if (fr == 485)
			video->loadFromFile("0486.jpg");
		if (fr == 486)
			video->loadFromFile("0487.jpg");
		if (fr == 487)
			video->loadFromFile("0488.jpg");
		if (fr == 488)
			video->loadFromFile("0489.jpg");
		if (fr == 489)
			video->loadFromFile("0490.jpg");
		if (fr == 490)
			video->loadFromFile("0491.jpg");
		if (fr == 491)
			video->loadFromFile("0492.jpg");
		if (fr == 492)
			video->loadFromFile("0493.jpg");
		if (fr == 493)
			video->loadFromFile("0494.jpg");
		if (fr == 494)
			video->loadFromFile("0495.jpg");
		if (fr == 495)
			video->loadFromFile("0496.jpg");
		if (fr == 496)
			video->loadFromFile("0497.jpg");
		if (fr == 497)
			video->loadFromFile("0498.jpg");
		if (fr == 498)
			video->loadFromFile("0499.jpg");
		if (fr == 499)
			video->loadFromFile("0500.jpg");
	}
	else
	{
		if (fr == 0)
			video->loadFromFile("Settings\\0001.jpg");
		if (fr == 1)
			video->loadFromFile("Settings\\0002.jpg");
		if (fr == 2)
			video->loadFromFile("Settings\\0003.jpg");
		if (fr == 3)
			video->loadFromFile("Settings\\0004.jpg");
		if (fr == 4)
			video->loadFromFile("Settings\\0005.jpg");
		if (fr == 5)
			video->loadFromFile("Settings\\0006.jpg");
		if (fr == 6)
			video->loadFromFile("Settings\\0007.jpg");
		if (fr == 7)
			video->loadFromFile("Settings\\0008.jpg");
		if (fr == 8)
			video->loadFromFile("Settings\\0009.jpg");
		if (fr == 9)
			video->loadFromFile("Settings\\0010.jpg");
		if (fr == 10)
			video->loadFromFile("Settings\\0011.jpg");
		if (fr == 11)
			video->loadFromFile("Settings\\0012.jpg");
		if (fr == 12)
			video->loadFromFile("Settings\\0013.jpg");
		if (fr == 13)
			video->loadFromFile("Settings\\0014.jpg");
		if (fr == 14)
			video->loadFromFile("Settings\\0015.jpg");
		if (fr == 15)
			video->loadFromFile("Settings\\0016.jpg");
		if (fr == 16)
			video->loadFromFile("Settings\\0017.jpg");
		if (fr == 17)
			video->loadFromFile("Settings\\0018.jpg");
		if (fr == 18)
			video->loadFromFile("Settings\\0019.jpg");
		if (fr == 19)
			video->loadFromFile("Settings\\0020.jpg");
		if (fr == 20)
			video->loadFromFile("Settings\\0021.jpg");
		if (fr == 21)
			video->loadFromFile("Settings\\0022.jpg");
		if (fr == 22)
			video->loadFromFile("Settings\\0023.jpg");
		if (fr == 23)
			video->loadFromFile("Settings\\0024.jpg");
		if (fr == 24)
			video->loadFromFile("Settings\\0025.jpg");
		if (fr == 25)
			video->loadFromFile("Settings\\0026.jpg");
		if (fr == 26)
			video->loadFromFile("Settings\\0027.jpg");
		if (fr == 27)
			video->loadFromFile("Settings\\0028.jpg");
		if (fr == 28)
			video->loadFromFile("Settings\\0029.jpg");
		if (fr == 29)
			video->loadFromFile("Settings\\0030.jpg");
		if (fr == 30)
			video->loadFromFile("Settings\\0031.jpg");
		if (fr == 31)
			video->loadFromFile("Settings\\0032.jpg");
		if (fr == 32)
			video->loadFromFile("Settings\\0033.jpg");
		if (fr == 33)
			video->loadFromFile("Settings\\0034.jpg");
		if (fr == 34)
			video->loadFromFile("Settings\\0035.jpg");
		if (fr == 35)
			video->loadFromFile("Settings\\0036.jpg");
		if (fr == 36)
			video->loadFromFile("Settings\\0037.jpg");
		if (fr == 37)
			video->loadFromFile("Settings\\0038.jpg");
		if (fr == 38)
			video->loadFromFile("Settings\\0039.jpg");
		if (fr == 39)
			video->loadFromFile("Settings\\0040.jpg");
		if (fr == 40)
			video->loadFromFile("Settings\\0041.jpg");
		if (fr == 41)
			video->loadFromFile("Settings\\0042.jpg");
		if (fr == 42)
			video->loadFromFile("Settings\\0043.jpg");
		if (fr == 43)
			video->loadFromFile("Settings\\0044.jpg");
		if (fr == 44)
			video->loadFromFile("Settings\\0045.jpg");
		if (fr == 45)
			video->loadFromFile("Settings\\0046.jpg");
		if (fr == 46)
			video->loadFromFile("Settings\\0047.jpg");
		if (fr == 47)
			video->loadFromFile("Settings\\0048.jpg");
		if (fr == 48)
			video->loadFromFile("Settings\\0049.jpg");
		if (fr == 49)
			video->loadFromFile("Settings\\0050.jpg");
		if (fr == 50)
			video->loadFromFile("Settings\\0051.jpg");
		if (fr == 51)
			video->loadFromFile("Settings\\0052.jpg");
		if (fr == 52)
			video->loadFromFile("Settings\\0053.jpg");
		if (fr == 53)
			video->loadFromFile("Settings\\0054.jpg");
		if (fr == 54)
			video->loadFromFile("Settings\\0055.jpg");
		if (fr == 55)
			video->loadFromFile("Settings\\0056.jpg");
		if (fr == 56)
			video->loadFromFile("Settings\\0057.jpg");
		if (fr == 57)
			video->loadFromFile("Settings\\0058.jpg");
		if (fr == 58)
			video->loadFromFile("Settings\\0059.jpg");
		if (fr == 59)
			video->loadFromFile("Settings\\0060.jpg");
		if (fr == 60)
			video->loadFromFile("Settings\\0061.jpg");
		if (fr == 61)
			video->loadFromFile("Settings\\0062.jpg");
		if (fr == 62)
			video->loadFromFile("Settings\\0063.jpg");
		if (fr == 63)
			video->loadFromFile("Settings\\0064.jpg");
		if (fr == 64)
			video->loadFromFile("Settings\\0065.jpg");
		if (fr == 65)
			video->loadFromFile("Settings\\0066.jpg");
		if (fr == 66)
			video->loadFromFile("Settings\\0067.jpg");
		if (fr == 67)
			video->loadFromFile("Settings\\0068.jpg");
		if (fr == 68)
			video->loadFromFile("Settings\\0069.jpg");
		if (fr == 69)
			video->loadFromFile("Settings\\0070.jpg");
		if (fr == 70)
			video->loadFromFile("Settings\\0071.jpg");
		if (fr == 71)
			video->loadFromFile("Settings\\0072.jpg");
		if (fr == 72)
			video->loadFromFile("Settings\\0073.jpg");
		if (fr == 73)
			video->loadFromFile("Settings\\0074.jpg");
		if (fr == 74)
			video->loadFromFile("Settings\\0075.jpg");
		if (fr == 75)
			video->loadFromFile("Settings\\0076.jpg");
		if (fr == 76)
			video->loadFromFile("Settings\\0077.jpg");
		if (fr == 77)
			video->loadFromFile("Settings\\0078.jpg");
		if (fr == 78)
			video->loadFromFile("Settings\\0079.jpg");
		if (fr == 79)
			video->loadFromFile("Settings\\0080.jpg");
		if (fr == 80)
			video->loadFromFile("Settings\\0081.jpg");
		if (fr == 81)
			video->loadFromFile("Settings\\0082.jpg");
		if (fr == 82)
			video->loadFromFile("Settings\\0083.jpg");
		if (fr == 83)
			video->loadFromFile("Settings\\0084.jpg");
		if (fr == 84)
			video->loadFromFile("Settings\\0085.jpg");
		if (fr == 85)
			video->loadFromFile("Settings\\0086.jpg");
		if (fr == 86)
			video->loadFromFile("Settings\\0087.jpg");
		if (fr == 87)
			video->loadFromFile("Settings\\0088.jpg");
		if (fr == 88)
			video->loadFromFile("Settings\\0089.jpg");
		if (fr == 89)
			video->loadFromFile("Settings\\0090.jpg");
		if (fr == 90)
			video->loadFromFile("Settings\\0091.jpg");
		if (fr == 91)
			video->loadFromFile("Settings\\0092.jpg");
		if (fr == 92)
			video->loadFromFile("Settings\\0093.jpg");
		if (fr == 93)
			video->loadFromFile("Settings\\0094.jpg");
		if (fr == 94)
			video->loadFromFile("Settings\\0095.jpg");
		if (fr == 95)
			video->loadFromFile("Settings\\0096.jpg");
		if (fr == 96)
			video->loadFromFile("Settings\\0097.jpg");
		if (fr == 97)
			video->loadFromFile("Settings\\0098.jpg");
		if (fr == 98)
			video->loadFromFile("Settings\\0099.jpg");
		if (fr == 99)
			video->loadFromFile("Settings\\0100.jpg");
		if (fr == 100)
			video->loadFromFile("Settings\\0101.jpg");
		if (fr == 101)
			video->loadFromFile("Settings\\0102.jpg");
		if (fr == 102)
			video->loadFromFile("Settings\\0103.jpg");
		if (fr == 103)
			video->loadFromFile("Settings\\0104.jpg");
		if (fr == 104)
			video->loadFromFile("Settings\\0105.jpg");
		if (fr == 105)
			video->loadFromFile("Settings\\0106.jpg");
		if (fr == 106)
			video->loadFromFile("Settings\\0107.jpg");
		if (fr == 107)
			video->loadFromFile("Settings\\0108.jpg");
		if (fr == 108)
			video->loadFromFile("Settings\\0109.jpg");
		if (fr == 109)
			video->loadFromFile("Settings\\0110.jpg");
		if (fr == 110)
			video->loadFromFile("Settings\\0111.jpg");
		if (fr == 111)
			video->loadFromFile("Settings\\0112.jpg");
		if (fr == 112)
			video->loadFromFile("Settings\\0113.jpg");
		if (fr == 113)
			video->loadFromFile("Settings\\0114.jpg");
		if (fr == 114)
			video->loadFromFile("Settings\\0115.jpg");
		if (fr == 115)
			video->loadFromFile("Settings\\0116.jpg");
		if (fr == 116)
			video->loadFromFile("Settings\\0117.jpg");
		if (fr == 117)
			video->loadFromFile("Settings\\0118.jpg");
		if (fr == 118)
			video->loadFromFile("Settings\\0119.jpg");
		if (fr == 119)
			video->loadFromFile("Settings\\0120.jpg");
		if (fr == 120)
			video->loadFromFile("Settings\\0121.jpg");
		if (fr == 121)
			video->loadFromFile("Settings\\0122.jpg");
		if (fr == 122)
			video->loadFromFile("Settings\\0123.jpg");
		if (fr == 123)
			video->loadFromFile("Settings\\0124.jpg");
		if (fr == 124)
			video->loadFromFile("Settings\\0125.jpg");
		if (fr == 125)
			video->loadFromFile("Settings\\0126.jpg");
		if (fr == 126)
			video->loadFromFile("Settings\\0127.jpg");
		if (fr == 127)
			video->loadFromFile("Settings\\0128.jpg");
		if (fr == 128)
			video->loadFromFile("Settings\\0129.jpg");
		if (fr == 129)
			video->loadFromFile("Settings\\0130.jpg");
		if (fr == 130)
			video->loadFromFile("Settings\\0131.jpg");
		if (fr == 131)
			video->loadFromFile("Settings\\0132.jpg");
		if (fr == 132)
			video->loadFromFile("Settings\\0133.jpg");
		if (fr == 133)
			video->loadFromFile("Settings\\0134.jpg");
		if (fr == 134)
			video->loadFromFile("Settings\\0135.jpg");
		if (fr == 135)
			video->loadFromFile("Settings\\0136.jpg");
		if (fr == 136)
			video->loadFromFile("Settings\\0137.jpg");
		if (fr == 137)
			video->loadFromFile("Settings\\0138.jpg");
		if (fr == 138)
			video->loadFromFile("Settings\\0139.jpg");
		if (fr == 139)
			video->loadFromFile("Settings\\0140.jpg");
		if (fr == 140)
			video->loadFromFile("Settings\\0141.jpg");
		if (fr == 141)
			video->loadFromFile("Settings\\0142.jpg");
		if (fr == 142)
			video->loadFromFile("Settings\\0143.jpg");
		if (fr == 143)
			video->loadFromFile("Settings\\0144.jpg");
		if (fr == 144)
			video->loadFromFile("Settings\\0145.jpg");
		if (fr == 145)
			video->loadFromFile("Settings\\0146.jpg");
		if (fr == 146)
			video->loadFromFile("Settings\\0147.jpg");
		if (fr == 147)
			video->loadFromFile("Settings\\0148.jpg");
		if (fr == 148)
			video->loadFromFile("Settings\\0149.jpg");
		if (fr == 149)
			video->loadFromFile("Settings\\0150.jpg");
		if (fr == 150)
			video->loadFromFile("Settings\\0151.jpg");
		if (fr == 151)
			video->loadFromFile("Settings\\0152.jpg");
		if (fr == 152)
			video->loadFromFile("Settings\\0153.jpg");
		if (fr == 153)
			video->loadFromFile("Settings\\0154.jpg");
		if (fr == 154)
			video->loadFromFile("Settings\\0155.jpg");
		if (fr == 155)
			video->loadFromFile("Settings\\0156.jpg");
		if (fr == 156)
			video->loadFromFile("Settings\\0157.jpg");
		if (fr == 157)
			video->loadFromFile("Settings\\0158.jpg");
		if (fr == 158)
			video->loadFromFile("Settings\\0159.jpg");
		if (fr == 159)
			video->loadFromFile("Settings\\0160.jpg");
		if (fr == 160)
			video->loadFromFile("Settings\\0161.jpg");
		if (fr == 161)
			video->loadFromFile("Settings\\0162.jpg");
		if (fr == 162)
			video->loadFromFile("Settings\\0163.jpg");
		if (fr == 163)
			video->loadFromFile("Settings\\0164.jpg");
		if (fr == 164)
			video->loadFromFile("Settings\\0165.jpg");
		if (fr == 165)
			video->loadFromFile("Settings\\0166.jpg");
		if (fr == 166)
			video->loadFromFile("Settings\\0167.jpg");
		if (fr == 167)
			video->loadFromFile("Settings\\0168.jpg");
		if (fr == 168)
			video->loadFromFile("Settings\\0169.jpg");
		if (fr == 169)
			video->loadFromFile("Settings\\0170.jpg");
		if (fr == 170)
			video->loadFromFile("Settings\\0171.jpg");
		if (fr == 171)
			video->loadFromFile("Settings\\0172.jpg");
		if (fr == 172)
			video->loadFromFile("Settings\\0173.jpg");
		if (fr == 173)
			video->loadFromFile("Settings\\0174.jpg");
		if (fr == 174)
			video->loadFromFile("Settings\\0175.jpg");
		if (fr == 175)
			video->loadFromFile("Settings\\0176.jpg");
		if (fr == 176)
			video->loadFromFile("Settings\\0177.jpg");
		if (fr == 177)
			video->loadFromFile("Settings\\0178.jpg");
		if (fr == 178)
			video->loadFromFile("Settings\\0179.jpg");
		if (fr == 179)
			video->loadFromFile("Settings\\0180.jpg");
		if (fr == 180)
			video->loadFromFile("Settings\\0181.jpg");
		if (fr == 181)
			video->loadFromFile("Settings\\0182.jpg");
		if (fr == 182)
			video->loadFromFile("Settings\\0183.jpg");
		if (fr == 183)
			video->loadFromFile("Settings\\0184.jpg");
		if (fr == 184)
			video->loadFromFile("Settings\\0185.jpg");
		if (fr == 185)
			video->loadFromFile("Settings\\0186.jpg");
		if (fr == 186)
			video->loadFromFile("Settings\\0187.jpg");
		if (fr == 187)
			video->loadFromFile("Settings\\0188.jpg");
		if (fr == 188)
			video->loadFromFile("Settings\\0189.jpg");
		if (fr == 189)
			video->loadFromFile("Settings\\0190.jpg");
		if (fr == 190)
			video->loadFromFile("Settings\\0191.jpg");
		if (fr == 191)
			video->loadFromFile("Settings\\0192.jpg");
		if (fr == 192)
			video->loadFromFile("Settings\\0193.jpg");
		if (fr == 193)
			video->loadFromFile("Settings\\0194.jpg");
		if (fr == 194)
			video->loadFromFile("Settings\\0195.jpg");
		if (fr == 195)
			video->loadFromFile("Settings\\0196.jpg");
		if (fr == 196)
			video->loadFromFile("Settings\\0197.jpg");
		if (fr == 197)
			video->loadFromFile("Settings\\0198.jpg");
		if (fr == 198)
			video->loadFromFile("Settings\\0199.jpg");
		if (fr == 199)
			video->loadFromFile("Settings\\0200.jpg");
		if (fr == 200)
			video->loadFromFile("Settings\\0201.jpg");
		if (fr == 201)
			video->loadFromFile("Settings\\0202.jpg");
		if (fr == 202)
			video->loadFromFile("Settings\\0203.jpg");
		if (fr == 203)
			video->loadFromFile("Settings\\0204.jpg");
		if (fr == 204)
			video->loadFromFile("Settings\\0205.jpg");
		if (fr == 205)
			video->loadFromFile("Settings\\0206.jpg");
		if (fr == 206)
			video->loadFromFile("Settings\\0207.jpg");
		if (fr == 207)
			video->loadFromFile("Settings\\0208.jpg");
		if (fr == 208)
			video->loadFromFile("Settings\\0209.jpg");
		if (fr == 209)
			video->loadFromFile("Settings\\0210.jpg");
		if (fr == 210)
			video->loadFromFile("Settings\\0211.jpg");
		if (fr == 211)
			video->loadFromFile("Settings\\0212.jpg");
		if (fr == 212)
			video->loadFromFile("Settings\\0213.jpg");
		if (fr == 213)
			video->loadFromFile("Settings\\0214.jpg");
		if (fr == 214)
			video->loadFromFile("Settings\\0215.jpg");
		if (fr == 215)
			video->loadFromFile("Settings\\0216.jpg");
		if (fr == 216)
			video->loadFromFile("Settings\\0217.jpg");
		if (fr == 217)
			video->loadFromFile("Settings\\0218.jpg");
		if (fr == 218)
			video->loadFromFile("Settings\\0219.jpg");
		if (fr == 219)
			video->loadFromFile("Settings\\0220.jpg");
		if (fr == 220)
			video->loadFromFile("Settings\\0221.jpg");
		if (fr == 221)
			video->loadFromFile("Settings\\0222.jpg");
		if (fr == 222)
			video->loadFromFile("Settings\\0223.jpg");
		if (fr == 223)
			video->loadFromFile("Settings\\0224.jpg");
		if (fr == 224)
			video->loadFromFile("Settings\\0225.jpg");
		if (fr == 225)
			video->loadFromFile("Settings\\0226.jpg");
		if (fr == 226)
			video->loadFromFile("Settings\\0227.jpg");
		if (fr == 227)
			video->loadFromFile("Settings\\0228.jpg");
		if (fr == 228)
			video->loadFromFile("Settings\\0229.jpg");
		if (fr == 229)
			video->loadFromFile("Settings\\0230.jpg");
		if (fr == 230)
			video->loadFromFile("Settings\\0231.jpg");
		if (fr == 231)
			video->loadFromFile("Settings\\0232.jpg");
		if (fr == 232)
			video->loadFromFile("Settings\\0233.jpg");
		if (fr == 233)
			video->loadFromFile("Settings\\0234.jpg");
		if (fr == 234)
			video->loadFromFile("Settings\\0235.jpg");
		if (fr == 235)
			video->loadFromFile("Settings\\0236.jpg");
		if (fr == 236)
			video->loadFromFile("Settings\\0237.jpg");
		if (fr == 237)
			video->loadFromFile("Settings\\0238.jpg");
		if (fr == 238)
			video->loadFromFile("Settings\\0239.jpg");
		if (fr == 239)
			video->loadFromFile("Settings\\0240.jpg");
		if (fr == 240)
			video->loadFromFile("Settings\\0241.jpg");
		if (fr == 241)
			video->loadFromFile("Settings\\0242.jpg");
		if (fr == 242)
			video->loadFromFile("Settings\\0243.jpg");
		if (fr == 243)
			video->loadFromFile("Settings\\0244.jpg");
		if (fr == 244)
			video->loadFromFile("Settings\\0245.jpg");
		if (fr == 245)
			video->loadFromFile("Settings\\0246.jpg");
		if (fr == 246)
			video->loadFromFile("Settings\\0247.jpg");
		if (fr == 247)
			video->loadFromFile("Settings\\0248.jpg");
		if (fr == 248)
			video->loadFromFile("Settings\\0249.jpg");
		if (fr == 249)
			video->loadFromFile("Settings\\0250.jpg");
		if (fr == 250)
			video->loadFromFile("Settings\\0251.jpg");
		if (fr == 251)
			video->loadFromFile("Settings\\0252.jpg");
		if (fr == 252)
			video->loadFromFile("Settings\\0253.jpg");
		if (fr == 253)
			video->loadFromFile("Settings\\0254.jpg");
		if (fr == 254)
			video->loadFromFile("Settings\\0255.jpg");
		if (fr == 255)
			video->loadFromFile("Settings\\0256.jpg");
		if (fr == 256)
			video->loadFromFile("Settings\\0257.jpg");
		if (fr == 257)
			video->loadFromFile("Settings\\0258.jpg");
		if (fr == 258)
			video->loadFromFile("Settings\\0259.jpg");
		if (fr == 259)
			video->loadFromFile("Settings\\0260.jpg");
		if (fr == 260)
			video->loadFromFile("Settings\\0261.jpg");
		if (fr == 261)
			video->loadFromFile("Settings\\0262.jpg");
		if (fr == 262)
			video->loadFromFile("Settings\\0263.jpg");
		if (fr == 263)
			video->loadFromFile("Settings\\0264.jpg");
		if (fr == 264)
			video->loadFromFile("Settings\\0265.jpg");
		if (fr == 265)
			video->loadFromFile("Settings\\0266.jpg");
		if (fr == 266)
			video->loadFromFile("Settings\\0267.jpg");
		if (fr == 267)
			video->loadFromFile("Settings\\0268.jpg");
		if (fr == 268)
			video->loadFromFile("Settings\\0269.jpg");
		if (fr == 269)
			video->loadFromFile("Settings\\0270.jpg");
		if (fr == 270)
			video->loadFromFile("Settings\\0271.jpg");
		if (fr == 271)
			video->loadFromFile("Settings\\0272.jpg");
		if (fr == 272)
			video->loadFromFile("Settings\\0273.jpg");
		if (fr == 273)
			video->loadFromFile("Settings\\0274.jpg");
		if (fr == 274)
			video->loadFromFile("Settings\\0275.jpg");
		if (fr == 275)
			video->loadFromFile("Settings\\0276.jpg");
		if (fr == 276)
			video->loadFromFile("Settings\\0277.jpg");
		if (fr == 277)
			video->loadFromFile("Settings\\0278.jpg");
		if (fr == 278)
			video->loadFromFile("Settings\\0279.jpg");
		if (fr == 279)
			video->loadFromFile("Settings\\0280.jpg");
		if (fr == 280)
			video->loadFromFile("Settings\\0281.jpg");
		if (fr == 281)
			video->loadFromFile("Settings\\0282.jpg");
		if (fr == 282)
			video->loadFromFile("Settings\\0283.jpg");
		if (fr == 283)
			video->loadFromFile("Settings\\0284.jpg");
		if (fr == 284)
			video->loadFromFile("Settings\\0285.jpg");
		if (fr == 285)
			video->loadFromFile("Settings\\0286.jpg");
		if (fr == 286)
			video->loadFromFile("Settings\\0287.jpg");
		if (fr == 287)
			video->loadFromFile("Settings\\0288.jpg");
		if (fr == 288)
			video->loadFromFile("Settings\\0289.jpg");
		if (fr == 289)
			video->loadFromFile("Settings\\0290.jpg");
		if (fr == 290)
			video->loadFromFile("Settings\\0291.jpg");
		if (fr == 291)
			video->loadFromFile("Settings\\0292.jpg");
		if (fr == 292)
			video->loadFromFile("Settings\\0293.jpg");
		if (fr == 293)
			video->loadFromFile("Settings\\0294.jpg");
		if (fr == 294)
			video->loadFromFile("Settings\\0295.jpg");
		if (fr == 295)
			video->loadFromFile("Settings\\0296.jpg");
		if (fr == 296)
			video->loadFromFile("Settings\\0297.jpg");
		if (fr == 297)
			video->loadFromFile("Settings\\0298.jpg");
		if (fr == 298)
			video->loadFromFile("Settings\\0299.jpg");
		if (fr == 299)
			video->loadFromFile("Settings\\0300.jpg");
		if (fr == 300)
			video->loadFromFile("Settings\\0301.jpg");
		if (fr == 301)
			video->loadFromFile("Settings\\0302.jpg");
		if (fr == 302)
			video->loadFromFile("Settings\\0303.jpg");
		if (fr == 303)
			video->loadFromFile("Settings\\0304.jpg");
		if (fr == 304)
			video->loadFromFile("Settings\\0305.jpg");
		if (fr == 305)
			video->loadFromFile("Settings\\0306.jpg");
		if (fr == 306)
			video->loadFromFile("Settings\\0307.jpg");
		if (fr == 307)
			video->loadFromFile("Settings\\0308.jpg");
		if (fr == 308)
			video->loadFromFile("Settings\\0309.jpg");
		if (fr == 309)
			video->loadFromFile("Settings\\0310.jpg");
		if (fr == 310)
			video->loadFromFile("Settings\\0311.jpg");
		if (fr == 311)
			video->loadFromFile("Settings\\0312.jpg");
		if (fr == 312)
			video->loadFromFile("Settings\\0313.jpg");
		if (fr == 313)
			video->loadFromFile("Settings\\0314.jpg");
		if (fr == 314)
			video->loadFromFile("Settings\\0315.jpg");
		if (fr == 315)
			video->loadFromFile("Settings\\0316.jpg");
		if (fr == 316)
			video->loadFromFile("Settings\\0317.jpg");
		if (fr == 317)
			video->loadFromFile("Settings\\0318.jpg");
		if (fr == 318)
			video->loadFromFile("Settings\\0319.jpg");
		if (fr == 319)
			video->loadFromFile("Settings\\0320.jpg");
		if (fr == 320)
			video->loadFromFile("Settings\\0321.jpg");
		if (fr == 321)
			video->loadFromFile("Settings\\0322.jpg");
		if (fr == 322)
			video->loadFromFile("Settings\\0323.jpg");
		if (fr == 323)
			video->loadFromFile("Settings\\0324.jpg");
		if (fr == 324)
			video->loadFromFile("Settings\\0325.jpg");
		if (fr == 325)
			video->loadFromFile("Settings\\0326.jpg");
		if (fr == 326)
			video->loadFromFile("Settings\\0327.jpg");
		if (fr == 327)
			video->loadFromFile("Settings\\0328.jpg");
		if (fr == 328)
			video->loadFromFile("Settings\\0329.jpg");
		if (fr == 329)
			video->loadFromFile("Settings\\0330.jpg");
		if (fr == 330)
			video->loadFromFile("Settings\\0331.jpg");
		if (fr == 331)
			video->loadFromFile("Settings\\0332.jpg");
		if (fr == 332)
			video->loadFromFile("Settings\\0333.jpg");
		if (fr == 333)
			video->loadFromFile("Settings\\0334.jpg");
		if (fr == 334)
			video->loadFromFile("Settings\\0335.jpg");
		if (fr == 335)
			video->loadFromFile("Settings\\0336.jpg");
		if (fr == 336)
			video->loadFromFile("Settings\\0337.jpg");
		if (fr == 337)
			video->loadFromFile("Settings\\0338.jpg");
		if (fr == 338)
			video->loadFromFile("Settings\\0339.jpg");
		if (fr == 339)
			video->loadFromFile("Settings\\0340.jpg");
		if (fr == 340)
			video->loadFromFile("Settings\\0341.jpg");
		if (fr == 341)
			video->loadFromFile("Settings\\0342.jpg");
		if (fr == 342)
			video->loadFromFile("Settings\\0343.jpg");
		if (fr == 343)
			video->loadFromFile("Settings\\0344.jpg");
		if (fr == 344)
			video->loadFromFile("Settings\\0345.jpg");
		if (fr == 345)
			video->loadFromFile("Settings\\0346.jpg");
		if (fr == 346)
			video->loadFromFile("Settings\\0347.jpg");
		if (fr == 347)
			video->loadFromFile("Settings\\0348.jpg");
		if (fr == 348)
			video->loadFromFile("Settings\\0349.jpg");
		if (fr == 349)
			video->loadFromFile("Settings\\0350.jpg");
		if (fr == 350)
			video->loadFromFile("Settings\\0351.jpg");
		if (fr == 351)
			video->loadFromFile("Settings\\0352.jpg");
		if (fr == 352)
			video->loadFromFile("Settings\\0353.jpg");
		if (fr == 353)
			video->loadFromFile("Settings\\0354.jpg");
		if (fr == 354)
			video->loadFromFile("Settings\\0355.jpg");
		if (fr == 355)
			video->loadFromFile("Settings\\0356.jpg");
		if (fr == 356)
			video->loadFromFile("Settings\\0357.jpg");
		if (fr == 357)
			video->loadFromFile("Settings\\0358.jpg");
		if (fr == 358)
			video->loadFromFile("Settings\\0359.jpg");
		if (fr == 359)
			video->loadFromFile("Settings\\0360.jpg");
		if (fr == 360)
			video->loadFromFile("Settings\\0361.jpg");
		if (fr == 361)
			video->loadFromFile("Settings\\0362.jpg");
		if (fr == 362)
			video->loadFromFile("Settings\\0363.jpg");
		if (fr == 363)
			video->loadFromFile("Settings\\0364.jpg");
		if (fr == 364)
			video->loadFromFile("Settings\\0365.jpg");
		if (fr == 365)
			video->loadFromFile("Settings\\0366.jpg");
		if (fr == 366)
			video->loadFromFile("Settings\\0367.jpg");
		if (fr == 367)
			video->loadFromFile("Settings\\0368.jpg");
		if (fr == 368)
			video->loadFromFile("Settings\\0369.jpg");
		if (fr == 369)
			video->loadFromFile("Settings\\0370.jpg");
		if (fr == 370)
			video->loadFromFile("Settings\\0371.jpg");
		if (fr == 371)
			video->loadFromFile("Settings\\0372.jpg");
		if (fr == 372)
			video->loadFromFile("Settings\\0373.jpg");
		if (fr == 373)
			video->loadFromFile("Settings\\0374.jpg");
		if (fr == 374)
			video->loadFromFile("Settings\\0375.jpg");
		if (fr == 375)
			video->loadFromFile("Settings\\0376.jpg");
		if (fr == 376)
			video->loadFromFile("Settings\\0377.jpg");
		if (fr == 377)
			video->loadFromFile("Settings\\0378.jpg");
		if (fr == 378)
			video->loadFromFile("Settings\\0379.jpg");
		if (fr == 379)
			video->loadFromFile("Settings\\0380.jpg");
		if (fr == 380)
			video->loadFromFile("Settings\\0381.jpg");
		if (fr == 381)
			video->loadFromFile("Settings\\0382.jpg");
		if (fr == 382)
			video->loadFromFile("Settings\\0383.jpg");
		if (fr == 383)
			video->loadFromFile("Settings\\0384.jpg");
		if (fr == 384)
			video->loadFromFile("Settings\\0385.jpg");
		if (fr == 385)
			video->loadFromFile("Settings\\0386.jpg");
		if (fr == 386)
			video->loadFromFile("Settings\\0387.jpg");
		if (fr == 387)
			video->loadFromFile("Settings\\0388.jpg");
		if (fr == 388)
			video->loadFromFile("Settings\\0389.jpg");
		if (fr == 389)
			video->loadFromFile("Settings\\0390.jpg");
		if (fr == 390)
			video->loadFromFile("Settings\\0391.jpg");
		if (fr == 391)
			video->loadFromFile("Settings\\0392.jpg");
		if (fr == 392)
			video->loadFromFile("Settings\\0393.jpg");
		if (fr == 393)
			video->loadFromFile("Settings\\0394.jpg");
		if (fr == 394)
			video->loadFromFile("Settings\\0395.jpg");
		if (fr == 395)
			video->loadFromFile("Settings\\0396.jpg");
		if (fr == 396)
			video->loadFromFile("Settings\\0397.jpg");
		if (fr == 397)
			video->loadFromFile("Settings\\0398.jpg");
		if (fr == 398)
			video->loadFromFile("Settings\\0399.jpg");
		if (fr == 399)
			video->loadFromFile("Settings\\0400.jpg");
		if (fr == 400)
			video->loadFromFile("Settings\\0401.jpg");
		if (fr == 401)
			video->loadFromFile("Settings\\0402.jpg");
		if (fr == 402)
			video->loadFromFile("Settings\\0403.jpg");
		if (fr == 403)
			video->loadFromFile("Settings\\0404.jpg");
		if (fr == 404)
			video->loadFromFile("Settings\\0405.jpg");
		if (fr == 405)
			video->loadFromFile("Settings\\0406.jpg");
		if (fr == 406)
			video->loadFromFile("Settings\\0407.jpg");
		if (fr == 407)
			video->loadFromFile("Settings\\0408.jpg");
		if (fr == 408)
			video->loadFromFile("Settings\\0409.jpg");
		if (fr == 409)
			video->loadFromFile("Settings\\0410.jpg");
		if (fr == 410)
			video->loadFromFile("Settings\\0411.jpg");
		if (fr == 411)
			video->loadFromFile("Settings\\0412.jpg");
		if (fr == 412)
			video->loadFromFile("Settings\\0413.jpg");
		if (fr == 413)
			video->loadFromFile("Settings\\0414.jpg");
		if (fr == 414)
			video->loadFromFile("Settings\\0415.jpg");
		if (fr == 415)
			video->loadFromFile("Settings\\0416.jpg");
		if (fr == 416)
			video->loadFromFile("Settings\\0417.jpg");
		if (fr == 417)
			video->loadFromFile("Settings\\0418.jpg");
		if (fr == 418)
			video->loadFromFile("Settings\\0419.jpg");
		if (fr == 419)
			video->loadFromFile("Settings\\0420.jpg");
		if (fr == 420)
			video->loadFromFile("Settings\\0421.jpg");
		if (fr == 421)
			video->loadFromFile("Settings\\0422.jpg");
		if (fr == 422)
			video->loadFromFile("Settings\\0423.jpg");
		if (fr == 423)
			video->loadFromFile("Settings\\0424.jpg");
		if (fr == 424)
			video->loadFromFile("Settings\\0425.jpg");
		if (fr == 425)
			video->loadFromFile("Settings\\0426.jpg");
		if (fr == 426)
			video->loadFromFile("Settings\\0427.jpg");
		if (fr == 427)
			video->loadFromFile("Settings\\0428.jpg");
		if (fr == 428)
			video->loadFromFile("Settings\\0429.jpg");
		if (fr == 429)
			video->loadFromFile("Settings\\0430.jpg");
		if (fr == 430)
			video->loadFromFile("Settings\\0431.jpg");
		if (fr == 431)
			video->loadFromFile("Settings\\0432.jpg");
		if (fr == 432)
			video->loadFromFile("Settings\\0433.jpg");
		if (fr == 433)
			video->loadFromFile("Settings\\0434.jpg");
		if (fr == 434)
			video->loadFromFile("Settings\\0435.jpg");
		if (fr == 435)
			video->loadFromFile("Settings\\0436.jpg");
		if (fr == 436)
			video->loadFromFile("Settings\\0437.jpg");
		if (fr == 437)
			video->loadFromFile("Settings\\0438.jpg");
		if (fr == 438)
			video->loadFromFile("Settings\\0439.jpg");
		if (fr == 439)
			video->loadFromFile("Settings\\0440.jpg");
		if (fr == 440)
			video->loadFromFile("Settings\\0441.jpg");
		if (fr == 441)
			video->loadFromFile("Settings\\0442.jpg");
		if (fr == 442)
			video->loadFromFile("Settings\\0443.jpg");
		if (fr == 443)
			video->loadFromFile("Settings\\0444.jpg");
		if (fr == 444)
			video->loadFromFile("Settings\\0445.jpg");
		if (fr == 445)
			video->loadFromFile("Settings\\0446.jpg");
		if (fr == 446)
			video->loadFromFile("Settings\\0447.jpg");
		if (fr == 447)
			video->loadFromFile("Settings\\0448.jpg");
		if (fr == 448)
			video->loadFromFile("Settings\\0449.jpg");
		if (fr == 449)
			video->loadFromFile("Settings\\0450.jpg");
		if (fr == 450)
			video->loadFromFile("Settings\\0451.jpg");
		if (fr == 451)
			video->loadFromFile("Settings\\0452.jpg");
		if (fr == 452)
			video->loadFromFile("Settings\\0453.jpg");
		if (fr == 453)
			video->loadFromFile("Settings\\0454.jpg");
		if (fr == 454)
			video->loadFromFile("Settings\\0455.jpg");
		if (fr == 455)
			video->loadFromFile("Settings\\0456.jpg");
		if (fr == 456)
			video->loadFromFile("Settings\\0457.jpg");
		if (fr == 457)
			video->loadFromFile("Settings\\0458.jpg");
		if (fr == 458)
			video->loadFromFile("Settings\\0459.jpg");
		if (fr == 459)
			video->loadFromFile("Settings\\0460.jpg");
		if (fr == 460)
			video->loadFromFile("Settings\\0461.jpg");
		if (fr == 461)
			video->loadFromFile("Settings\\0462.jpg");
		if (fr == 462)
			video->loadFromFile("Settings\\0463.jpg");
		if (fr == 463)
			video->loadFromFile("Settings\\0464.jpg");
		if (fr == 464)
			video->loadFromFile("Settings\\0465.jpg");
		if (fr == 465)
			video->loadFromFile("Settings\\0466.jpg");
		if (fr == 466)
			video->loadFromFile("Settings\\0467.jpg");
		if (fr == 467)
			video->loadFromFile("Settings\\0468.jpg");
		if (fr == 468)
			video->loadFromFile("Settings\\0469.jpg");
		if (fr == 469)
			video->loadFromFile("Settings\\0470.jpg");
		if (fr == 470)
			video->loadFromFile("Settings\\0471.jpg");
		if (fr == 471)
			video->loadFromFile("Settings\\0472.jpg");
		if (fr == 472)
			video->loadFromFile("Settings\\0473.jpg");
		if (fr == 473)
			video->loadFromFile("Settings\\0474.jpg");
		if (fr == 474)
			video->loadFromFile("Settings\\0475.jpg");
		if (fr == 475)
			video->loadFromFile("Settings\\0476.jpg");
		if (fr == 476)
			video->loadFromFile("Settings\\0477.jpg");
		if (fr == 477)
			video->loadFromFile("Settings\\0478.jpg");
		if (fr == 478)
			video->loadFromFile("Settings\\0479.jpg");
		if (fr == 479)
			video->loadFromFile("Settings\\0480.jpg");
		if (fr == 480)
			video->loadFromFile("Settings\\0481.jpg");
		if (fr == 481)
			video->loadFromFile("Settings\\0482.jpg");
		if (fr == 482)
			video->loadFromFile("Settings\\0483.jpg");
		if (fr == 483)
			video->loadFromFile("Settings\\0484.jpg");
		if (fr == 484)
			video->loadFromFile("Settings\\0485.jpg");
		if (fr == 485)
			video->loadFromFile("Settings\\0486.jpg");
		if (fr == 486)
			video->loadFromFile("Settings\\0487.jpg");
		if (fr == 487)
			video->loadFromFile("Settings\\0488.jpg");
		if (fr == 488)
			video->loadFromFile("Settings\\0489.jpg");
		if (fr == 489)
			video->loadFromFile("Settings\\0490.jpg");
		if (fr == 490)
			video->loadFromFile("Settings\\0491.jpg");
		if (fr == 491)
			video->loadFromFile("Settings\\0492.jpg");
		if (fr == 492)
			video->loadFromFile("Settings\\0493.jpg");
		if (fr == 493)
			video->loadFromFile("Settings\\0494.jpg");
		if (fr == 494)
			video->loadFromFile("Settings\\0495.jpg");
		if (fr == 495)
			video->loadFromFile("Settings\\0496.jpg");
		if (fr == 496)
			video->loadFromFile("Settings\\0497.jpg");
		if (fr == 497)
			video->loadFromFile("Settings\\0498.jpg");
		if (fr == 498)
			video->loadFromFile("Settings\\0499.jpg");
		if (fr == 499)
			video->loadFromFile("Settings\\0500.jpg");
	}
}
