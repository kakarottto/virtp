#include <text.h>
Text::~Text()
{
	if(label != nullptr) TTF_DestroyText(label);
    if(font != nullptr) TTF_CloseFont(font);
}
void Text::SetText(std::string text)
{
	this->text = text;
	if(engine == nullptr || font == nullptr) return;
	if(label == nullptr)
	{
		label = TTF_CreateText(engine, font, text.c_str(), 0);
	}
	else TTF_SetTextString(label, text.c_str(),0);

}
std::string Text::GetText() const {return text;}
void Text::SetFont(std::string path)
{
	if(font == nullptr) font = TTF_OpenFont(path.c_str(),(float)font_size);
	else
	{
		TTF_CloseFont(font);
		font = TTF_OpenFont(path.c_str(),(float)font_size);
	}
	if(label != nullptr) TTF_SetTextFont(label,font);
}
void Text::SetSize(double font_size)
{
	if(font_size <= 0.0) return;
	this->font_size = font_size;
	if(font != nullptr) TTF_SetFontSize(font,font_size);
}
double Text::GetSize(){return font_size;}
void Text::SetEngine(TTF_TextEngine* engine){this->engine=engine;}
double Text::GetX(){return x;}
double Text::GetY(){return y;}
void Text::SetX(double x) {this->x=x;}
void Text::SetY(double y){this->y=y;}
void Text::SetPos(double x,double y){this->x=x;this->y=y;}
void Text::Draw()
{
	TTF_DrawRendererText(label, x, y);
}
