#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
class Text
{
public:
	Text() = default;
	~Text();
	void SetText(std::string);
	std::string GetText() const; 
	void SetFont(std::string);
	void SetSize(double);
	double GetSize();
	void SetEngine(TTF_TextEngine* engine);
	double GetX();
	double GetY();
	void SetX(double);
	void SetY(double);
	void SetPos(double,double);
	void Draw();
private:
	double x,y;
	std::string text;
	double font_size=10.0;
	TTF_TextEngine* engine = nullptr;
	TTF_Text* label = nullptr;
	TTF_Font* font = nullptr;
};
