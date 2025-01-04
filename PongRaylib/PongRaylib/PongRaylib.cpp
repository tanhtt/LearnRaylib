#include <iostream>
#include <raylib.h>

int player_score = 0;
int ai_score = 0;

class Ball {
public:
	float x, y;
	int x_speed, y_speed;
	int radius;

	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}

	void ResetBall() {
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;
		int speed_choice[2] = { -1, 1 };
		x_speed *= speed_choice[GetRandomValue(0, 1)];
		y_speed *= speed_choice[GetRandomValue(0, 1)];
	}

	void Move() {
		x += x_speed;
		y += y_speed;

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			y_speed *= -1;
		}

		if (x + radius >= GetScreenWidth() || x - radius <= 0) {
			x_speed *= -1;
		}

		if (x + radius >= GetScreenWidth()) {
			player_score++;
			ResetBall();
		}

		if (x - radius <= 0) {
			ai_score++;
			ResetBall();
		}
	}
};

class Paddle {
protected:
	void LimitMovement() {
		if (y <= 0) {
			y = 5;
		}
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height - 5;
		}
	}
public:
	float x, y;
	float width, height;
	int speed;

	void Draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}

	void Move() {
		if (IsKeyDown(KEY_W)) {
			y -= speed;
		}
		if (IsKeyDown(KEY_S)) {
			y += speed;
		}
		LimitMovement();
	}
};

class PaddleAI : public Paddle {
public:
	void Move(Ball ball) {
		if (ball.y < y + height / 2) {
			y -= speed;
		}
		if (ball.y > y + height / 2) {
			y += speed;
		}
		LimitMovement();
	};
};

Ball ball;
Paddle left_paddle;
PaddleAI right_paddle;

int main() {
	std::cout << "Hello World!" << std::endl;
	const int screen_width = 800;
	const int screen_height = 600;

	InitWindow(screen_width, screen_height, "Pong");
	SetTargetFPS(60);

	// Ball init
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.x_speed = 5;
	ball.y_speed = 5;
	ball.radius = 20;

	// Paddle init
	left_paddle.x = 10;
	left_paddle.y = screen_height / 2 - 60;
	left_paddle.width = 25;
	left_paddle.height = 120;
	left_paddle.speed = 5;

	right_paddle.x = screen_width - 25 - 10;
	right_paddle.y = screen_height / 2 - 60;
	right_paddle.width = 25;
	right_paddle.height = 120;
	right_paddle.speed = 5;

	while (WindowShouldClose() == false) {
		BeginDrawing();
		// Update
		ball.Move();
		left_paddle.Move();
		right_paddle.Move(ball);

		// Check Collision

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ left_paddle.x, left_paddle.y, left_paddle.width, left_paddle.height })) {
			ball.x_speed *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ right_paddle.x, right_paddle.y, right_paddle.width, right_paddle.height })) {
			ball.x_speed *= -1;
		}

		// Draw
		ClearBackground(BLACK);
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
		ball.Draw();
		left_paddle.Draw();
		right_paddle.Draw();
		DrawText(TextFormat("%i", player_score), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", ai_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

		EndDrawing();
	}
	CloseWindow();
	return 0;
}