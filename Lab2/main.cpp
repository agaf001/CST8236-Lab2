#include <SFML/Graphics.hpp>
#include <SFML\OpenGL.hpp>

int main(int argc, char *argv)
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Template", sf::Style::Titlebar | sf::Style::Close);


	sf::Image dogeImage;
	dogeImage.loadFromFile("stevegibson.jpg");

	// Tell OpenGL that we want to use 2D textures. 
	glEnable(GL_TEXTURE_2D);

	// Tell OpenGL that we want to use lighting.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	/* Tell OpenGL that we want to test the depth of each vertex to make sure that things that
	* are closer appear closer. */
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CW);
	// Generate a texture in OpenGL, and retrieve its ID so that we can access it.
	GLuint dogeTextureID;
	glGenTextures(1, &dogeTextureID);

	/* 'Bind' our texture to the active texture space so that all of our operations
	* are done to it. */
	glBindTexture(GL_TEXTURE_2D, dogeTextureID);

	glTexImage2D(GL_TEXTURE_2D, // specifies that we're working on the active texture.
		0, // ignore.
		GL_RGBA, // specifies that making a texture that has RGBA data.
		dogeImage.getSize().x, // specify the width of the texture.
		dogeImage.getSize().y, // specify the height of the texture.
		0, // no border
		GL_RGBA, // specifies that we're working with an image that has RGBA data.
		GL_UNSIGNED_BYTE, // specifies the format of the RGBA data (in this case, everything is 0-255)
		dogeImage.getPixelsPtr() // specifies the actual image data.
	);

	/* Telling OpenGL that we want our active texture to magnify and minimize in
	* linear fashion. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Telling OpenGL how we want to represent our texture when we try to draw past its bounds. */
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	float positionZ = 0.5f;
	float angle = 0.0f;
	float angle2 = 0.0f;
	int mode = 1;
	int rotateUp = 0;
	int rotateDown = 0;
	int rotateLeft = 0;
	int rotateRight = 0;

	float shift = 0;
	sf::Event evt;
	sf::Clock appTimer;
	while (window.isOpen()) {
		float deltaTime = appTimer.restart().asSeconds();

		while (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}
			
			if (evt.type == sf::Event::KeyPressed) 
			{
				if (evt.key.code == sf::Keyboard::Key::Num1)
					mode = 1;
				else if (evt.key.code == sf::Keyboard::Key::Num2)
					mode = 2;
				else if (evt.key.code == sf::Keyboard::Key::Num3)
					mode = 3;
				else if (evt.key.code == sf::Keyboard::Key::Num4)
					mode = 4;

				if (evt.key.code == sf::Keyboard::Key::Up)
					rotateUp--;
				else if (evt.key.code == sf::Keyboard::Key::Down)
					rotateDown++;
				else if (evt.key.code == sf::Keyboard::Key::Left)
					rotateLeft--;
				else if (evt.key.code == sf::Keyboard::Key::Right)
					rotateRight++;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLenum error = glGetError();

		float offset = 0.25f;
		//angle += 90.0f * deltaTime;

		//draw stuff
		GLfloat position[] = { positionZ, -0.1, positionZ, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glPushMatrix();

		if (rotateUp < 0) 
		{
			angle += rotateUp*4;
			rotateUp++;
		}
		if (rotateDown > 0)
		{
			angle += rotateDown * 4;
			rotateDown--;
		}

		if (rotateLeft < 0)
		{
			angle2 += rotateLeft * 4;
			rotateLeft++;
		}
		if (rotateRight > 0)
		{
			angle2 += rotateRight * 4;
			rotateRight--;
		}
		
		
		glRotatef(angle, 1.0f, 0.0f, 0.0f); // rotate at 90 degrees/second on the X axis. 
		glRotatef(angle2, 0.0f, 1.0f, 0.0f); //rotate 20 degrees on the Y axis

											// Begin our drawing block.
		switch (mode) 
		{
		case 1:
			glBegin(GL_TRIANGLES);
			break;
		case 2:
			glBegin(GL_TRIANGLE_STRIP);
			break;
		case 3: 
			glBegin(GL_QUADS);
			break;
		case 4: 
			glBegin(GL_QUAD_STRIP);
			break;
		}
		


		float leftS = 0.3f;
		float rightS = 0.7f;
		float topT = 0.25f;
		float bottomT = 0.75f;
		shift += 0.0001;


		// Front
		glColor3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(leftS, bottomT + shift);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-offset, -offset, offset);

		glTexCoord2f(leftS, topT+ shift);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(rightS, topT+ shift);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(offset, offset, offset);

		glTexCoord2f(rightS, bottomT + shift);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(offset, -offset, offset);

		// Right
		glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(leftS, bottomT+ shift);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, -offset, offset);

		glTexCoord2f(leftS, topT + shift);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, offset, offset);

		glTexCoord2f(rightS, topT + shift);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightS, bottomT + shift);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, -offset, -offset);

		// Left
		glColor3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(leftS, bottomT + shift);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, -offset, -offset);

		glTexCoord2f(leftS, topT + shift);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightS, topT + shift);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(rightS, bottomT + shift);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, -offset, offset);

		// Back
		glColor3f(0.0f, 1.0f, 1.0f);
		glTexCoord2f(leftS, bottomT + shift);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(offset, -offset, -offset);

		glTexCoord2f(leftS, topT + shift);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightS, topT + shift);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightS, bottomT + shift);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-offset, -offset, -offset);

		// Top
		glColor3f(1.0f, 0.0f, 1.0f);
		glTexCoord2f(leftS, bottomT + shift);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(leftS, topT + shift);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightS, topT + shift);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightS, bottomT + shift);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(offset, offset, offset);

		// Bottom
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(leftS, bottomT + shift);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-offset, -offset, -offset);

		glTexCoord2f(leftS, topT + shift);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-offset, -offset, offset);

		glTexCoord2f(rightS, topT + shift);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(offset, -offset, offset);

		glTexCoord2f(rightS, bottomT + shift);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(offset, -offset, -offset);

		// End our drawing block.
		glEnd();

		glPopMatrix();

		window.display();
	}

	return 0;
}