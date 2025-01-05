#include <iostream>
#include "raylib.h"
#include "deque"
#include "raymath.h"

// Declare
Color green = { 173, 204, 96, 255 };
Color darkGreen = { 43, 51, 24, 255 };

int cellSize = 30;
int cellCount = 25;
int offset = 75;

double lastUpdateTime;

bool IsElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
	for (unsigned int i = 0; i < deque.size(); i++) {
		if (Vector2Equals(deque[i], element)) {
			return true;
		}
	}
	return false;
}

bool eventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

class Food
{
public:
	Vector2 position;
	Texture2D texture;

	Food(std::deque<Vector2> deque)
	{
		Image image = LoadImage("Graphics/food.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);

		position = GenerateRandomPos(deque);
	}

	~Food()
	{
		UnloadTexture(texture);
	}

	void Draw()
	{
		DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
	}

	Vector2 GenerateRandomCell() {
		float x = GetRandomValue(0, cellCount - 1);
		float y = GetRandomValue(0, cellCount - 1);
		return Vector2{ x,y };
	}

	Vector2 GenerateRandomPos(std::deque<Vector2> deque)
	{
		Vector2 element = GenerateRandomCell();
		while (IsElementInDeque(element, deque)) {
			element = GenerateRandomCell();
		}
		return element;
	}
};

class Snack
{
public:
	std::deque<Vector2> body = { {4,9}, {5,9}, {6,9} };
	Vector2 direction{ 0,1 };
	bool addSegment = false;

	void Draw()
	{
		for (int i = 0; i < body.size(); i++) {
			float x = body[i].x;
			float y = body[i].y;
			Rectangle segment = Rectangle{ offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize };
			DrawRectangleRounded(segment, .5, 6, darkGreen);
		}
	}

	void Update()
	{
		body.push_front(Vector2Add(body[0], direction));
		if (addSegment == true) {
			addSegment = false;
		}
		else {
			body.pop_back();
		}
	}

	void Reset() {
		body = { {4,9}, {5,9}, {6,9} };
		direction = { 0,1 };
	}
};

class Game
{
public:
	Snack snack = Snack();
	Food food = Food(snack.body);
	bool running = true;
	int score = 0;
	Sound eat;
	Sound wall;

	Game() {
		InitAudioDevice();
		eat = LoadSound("Sounds/eat.mp3");
		wall = LoadSound("Sounds/wall.mp3");
	}

	~Game() {
		UnloadSound(eat);
		UnloadSound(wall);
		CloseAudioDevice();
	}

	void Draw() 
	{
		snack.Draw();
		food.Draw();
	}

	void Update() 
	{
		if (!running) return;
		snack.Update();
		this->CheckCollisionWithFood();
		this->CheckCollisionWithEdge();
		this->CheckCollisionWithTail();
	}

	void CheckCollisionWithFood() {
		if (Vector2Equals(snack.body[0], food.position)) {
			snack.addSegment = true;
			food.position = food.GenerateRandomPos(snack.body);
			score++;
			PlaySound(eat);
		}
	}

	void CheckCollisionWithEdge() {
		if (snack.body[0].x == -1 || snack.body[0].x == cellCount) {
			PlaySound(wall);
			GameOver();
		}
		if (snack.body[0].y == -1 || snack.body[0].y == cellCount) {
			PlaySound(wall);
			GameOver();
		}
	}

	void GameOver() {
		snack.Reset();
		food.position = food.GenerateRandomPos(snack.body);

		score = 0;
		running = false;
	}

	void CheckCollisionWithTail() {
		std::deque<Vector2> headless = snack.body;
		headless.pop_front();
		if (IsElementInDeque(snack.body[0], headless)) {
			GameOver();
		}
	}
};

int main()
{
	InitWindow( 2*offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Snake Game");
	SetTargetFPS(60);

	// Init
	Game game = Game();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		if (eventTriggered(.2)) {
			game.Update();
		}

		if (IsKeyPressed(KEY_UP) && game.snack.direction != Vector2{0, 1})
		{
			game.snack.direction = { 0, -1 };
			game.running = true;
		}
		if (IsKeyPressed(KEY_DOWN) && game.snack.direction != Vector2{ 0, -1 })
		{
			game.snack.direction = { 0, 1 };
			game.running = true;
		}
		if (IsKeyPressed(KEY_RIGHT) && game.snack.direction != Vector2{ -1, 0 })
		{
			game.snack.direction = { 1, 0 };
			game.running = true;
		}
		if (IsKeyPressed(KEY_LEFT) && game.snack.direction != Vector2{ 1, 0 })
		{
			game.snack.direction = { -1, 0 };
			game.running = true;
		}


		// Draw
		ClearBackground(green);
		DrawRectangleLinesEx(Rectangle{(float) offset - 5, (float) offset - 5, (float) cellSize * cellCount + 10, (float)cellSize * cellCount + 10 }, 5, darkGreen);
		game.Draw();
		DrawText("Retro Snake", offset - 5, 20, 40, darkGreen);
		DrawText(TextFormat("%i", game.score), offset - 5, offset + cellCount * cellSize + 10, 40, darkGreen);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}