#pragma once
class LoaderParams
{
public:
	~LoaderParams(void);
	LoaderParams(int x, int y, int width, int height, std::string
		textureID,int maxFrame,float speed) : m_x(x), m_y(y), m_width(width), m_height(height),
		m_textureID(textureID),m_maxFrame(maxFrame),m_speed(speed),m_currentFrame(0)
	{
	}
	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }
	int getcurrentFrame()const { return m_currentFrame; }
	int getmaxFrame()const { return m_maxFrame; }
	float getSpeed()const { return m_speed; }
   private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	float m_speed;
	std::string m_textureID;
	int m_currentFrame;
	int m_maxFrame;
};

