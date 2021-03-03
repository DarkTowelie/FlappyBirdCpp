#pragma once
#include "Bird.h"
#include "Pipe.h"
#include <cstdlib>

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	float pipeShift = 206;
	Bird bird = Bird(50, 206);
	Pipe pipe1 = Pipe(300, -pipeShift);
	Pipe pipe2 = Pipe(600, -pipeShift);

	int score;
	bool gameOver;
	float gravityValue;

	void init()
	{
		gameOver = false;

		gravityValue = 0.3f;
		score = 0;

		bird = Bird(50, 206);
		pipe1 = Pipe(300, -pipeShift);
		pipe2 = Pipe(600, -pipeShift);
	}

	void refreshScore()
	{
		if (bird.X() > pipe1.X() + pipe1.SpriteSizeX() && !pipe1.passed)
		{
			score++;
			pipe1.passed = true;
		}

		if (bird.X() > pipe2.X() + pipe2.SpriteSizeX() && !pipe2.passed)
		{
			score++;
			pipe2.passed = true;
		}
	}

	void CreateWall()
	{
		float newY = -pipeShift + rand() % 200 - 100;

		if (bird.X() - 300 > pipe1.X())
		{
			pipe1 = Pipe(bird.X() + 300, newY);
		}

		if (bird.X() - 300 > pipe2.X())
		{
			pipe2 = Pipe(bird.X() + 300, newY);
		}
	}

	bool CheckGameOver(Pipe pipe)
	{
		float birdLBound = bird.X();
		float birdRBound = bird.X() + bird.SpriteSize();
		float birdUBound = bird.Y();
		float birdBBound = bird.Y() + bird.SpriteSize();

		float pipesLBound = pipe.X();
		float pipesRBound = pipe.X() + pipe.SpriteSizeX();
		float topPipeBound = pipe.Y() + pipe.SpriteSizeY();
		float bottomPipeBound = pipe.Y() + pipe.SpriteSizeY() + pipe.WindowSize();

		if ((birdLBound > pipesLBound && birdLBound < pipesRBound)
			|| (birdRBound > pipesLBound && birdRBound < pipe.X() + pipesRBound))
		{
			if ((birdUBound <= topPipeBound) || (birdBBound >= bottomPipeBound))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	bool CheckGameOver()
	{
		if (bird.Y() > 500)
			return true;
		else
			return false;
	}

	void updateScore()
	{
		if (bird.X() > pipe1.X() + pipe1.SpriteSizeX() && !pipe1.passed)
		{
			score++;
			pipe1.passed = true;
		}

		if (bird.X() > pipe2.X() + pipe2.SpriteSizeX() && !pipe2.passed)
		{
			score++;
			pipe2.passed = true;
		}
	}

	public ref class Form1 : public System::Windows::Forms::Form
	{
		Image^ bgSprite;
		Image^ birdSprite;
		Image^ pipeTopSprite;
		Image^ pipeBottomSprite;

		System::Windows::Forms::Timer^ timer;
		System::Windows::Forms::Timer^ timer1;
		System::ComponentModel::IContainer^ components;

		void update()
		{
			if (!gameOver)
			{
				this->Text = "Score:";
				bird.fall(gravityValue);
				pipe1.Move();
				pipe2.Move();
				CreateWall();

				if (CheckGameOver(pipe1) || CheckGameOver(pipe2) || CheckGameOver())
					gameOver = true;

				updateScore();
				Invalidate();
			}
			else
			{
				timer1->Stop();
			}
		}
		

	public:
		Form1(void)
		{
			InitializeComponent();
			bgSprite = Image::FromFile("image\\bg.png");
			birdSprite = Image::FromFile("image\\bird.png");
			pipeBottomSprite = Image::FromFile("image\\pipeBottom.png");
			pipeTopSprite = Image::FromFile("image\\pipeTop.png");
			init();
			Invalidate();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(272, 473);
			this->DoubleBuffered = true;
			this->Name = L"Form1";
			this->Text = L"FlappyBird";
			this->Click += gcnew System::EventHandler(this, &Form1::Form1_Click);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->ResumeLayout(false);

		}


#pragma endregion
	private: System::Void Form1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ graphics = e->Graphics;
		graphics->DrawImage(bgSprite, 0, 0, bgSprite->Width, bgSprite->Height);
		graphics->DrawImage(birdSprite, bird.X(), bird.Y(), bird.SpriteSize(), bird.SpriteSize());

		graphics->DrawImage(pipeTopSprite, pipe1.X(), pipe1.Y(), pipe1.SpriteSizeX(), pipe1.SpriteSizeY());
		graphics->DrawImage(pipeBottomSprite, pipe1.X(), pipe1.Y() + pipe1.SpriteSizeY() + pipe1.WindowSize(), pipe1.SpriteSizeX(), pipe1.SpriteSizeY());

		graphics->DrawImage(pipeTopSprite, pipe2.X(), pipe2.Y(), pipe2.SpriteSizeX(), pipe2.SpriteSizeY());
		graphics->DrawImage(pipeBottomSprite, pipe2.X(), pipe2.Y() + pipe2.SpriteSizeY() + pipe2.WindowSize(), pipe2.SpriteSizeX(), pipe2.SpriteSizeY());
	}
	private: System::Void Form1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!gameOver)
		{
			bird.jump();
		}
		else
			init();
		if (!timer1->Enabled)
		{
			timer1->Start();
			timer1->Interval = 10;
			bird.jump();
		}
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		update();
	}
};
}
