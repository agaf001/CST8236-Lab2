#include "Cube.h"

Cube::Cube(GLuint textureID) : _horizontalAngle(0), _verticalAngle(0), _textureID(textureID)
{
	_textureOffset = 0.0f;
}

void Cube::Update(float dt)
{
	_horizontalAngle += 90.0f * dt;
	_textureOffset += 0.1f * dt;
	if (_textureOffset > 1.0f) {
		_textureOffset -= 1.0f;
	}
}

void Cube::Draw(GLenum mode)
{
	float offset = 0.25f;

	float leftS = _textureOffset;
	float rightS = leftS + 0.4f;
	float topT = 0.25f;
	float bottomT = 0.75f;

	//glBindTexture(GL_TEXTURE_2D, _textureID);
	GLenum error = glGetError();

	glPushMatrix();
	error = glGetError();
	{
		glRotatef(_horizontalAngle, 0.0f, 1.0f, 0.0f); // rotate at 90 degrees/second on the X axis. 
		glRotatef(_verticalAngle, 1.0f, 0.0f, 0.0f); //rotate 20 degrees on the Y axis

													 // Begin our drawing block.
		glBegin(mode);

		// Front
		glColor3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-offset, -offset, offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(offset, offset, offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(offset, -offset, offset);

		// Right
		glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, -offset, offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, offset, offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, -offset, -offset);

		// Left
		glColor3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, -offset, -offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, -offset, offset);

		// Back
		glColor3f(0.0f, 1.0f, 1.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(offset, -offset, -offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-offset, -offset, -offset);

		// Top
		glColor3f(1.0f, 0.0f, 1.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(offset, offset, offset);

		// Bottom
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-offset, -offset, -offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-offset, -offset, offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(offset, -offset, offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(offset, -offset, -offset);

		// End our drawing block.
		glEnd();
	}
	glPopMatrix();
}