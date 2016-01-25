rogram();

		// Attach the fragment and vertex shaders to the shader program.
		glAttachShader(m_uiProgramObject, m_uiFragShader);
		glAttachShader(m_uiProgramObject, m_uiVertexShader);

		// Bind the custom vertex attribute "myVertex" to location VERTEX_ARRAY
		glBindAttribLocation(m_uiProgramObject, VERTEX_ARRAY, "myVertex");

		// Link the program
		glLinkProgram(m_uiProgramObject);

		// Check if linking succeeded in the same way we checked for compilation success
		GLint bLinked;
		glGetProgramiv(m_uiProgramObject, GL_LINK_STATUS, &bLinked);
		if (!bLinked)
		{
			int i32InfoLogLength, i32CharsWritten;
			glGetProgramiv(m_uiProgramObject, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
			char* pszInfoLog = new char[i32InfoLogLength];
			glGetProgramInfoLog(m_uiProgramObject, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
			char* pszMsg = new char[i32InfoLogLength+256];
			strcpy(pszMsg, "Failed to link program: ");
			strcat(pszMsg, pszInfoLog);
			PVRShellSet(prefExitMessage, pszMsg);

			delete [] pszMsg;
			delete [] pszInfoLog;
			delete [] shaderPath;
			return false;
		}

		// As there is no stored binary, save the current binary out for use later.
		// Note that this is done after both binding attributes and linking -
		// none of these can be performed after
		if (m_bBinaryShaderSupported) saveBinaryProgram(shaderPath,m_uiProgramObject);

		//Set red channel of the colour to maximum - red shows that the shaders had to be compiled.
		afColour[0]=1.0f;
	}
	else
	{
		//Set green channel of the colour to maximum - green shows that the shaders were loaded from binary files.
		afColour[1]=1.0f;
	}

	delete[] shaderPath;

	// Uses the program.
	glUseProgram(m_uiProgramObject);

	// Bind the colour to the fragment shader.
	GLint i32ColourLocation = glGetUniformLocation(m_uiProgramObject, "myColour");

	// Then passes the colour to that variable
	glUniform3fv(i32ColourLocation, 1, afColour);

	// Sets the clear color
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);

	// Create VBO for the triangle from our data

	// Vertex data
	GLfloat afVertices[] = {-0.4f,-0.4f,0.0f,  0.4f,-0.4f,0.0f,   0.0f,0.4f,0.0f};

	// Gen VBO
	glGenBuffers(1, &m_ui32Vbo);

	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_ui32Vbo);

	// Set the buffer's data
	glBufferData(GL_ARRAY_BUFFER, 3 * (3 * sizeof(GLfloat)) /* 3 Vertices of 3 floats in size */, afVertices, GL_STATIC_DRAW);

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Enable culling
	glEnable(GL_CULL_FACE);
	return true;
}

/*!****************************************************************************
 @Function		ReleaseView
 @Return		bool		true if no error occured
 @Description	Code in ReleaseView() will be called by PVRShell when the
				application quits or before a change in the rendering context.
******************************************************************************/
bool OGLES2BinaryShader::ReleaseView()
{
	// Release Vertex buffer object.
	glDeleteBuffers(1, &m_ui32Vbo);

	// Frees the OpenGL handles for the program and the 2 shaders
	glDeleteProgram(m_uiProgramObject);
	glDeleteShader(m_uiVertexShader);
	glDeleteShader(m_uiFragShader);
	return true;
}

/*!****************************************************************************
 @Function		RenderScene
 @Return		bool		true if no error occurred
 @Description	Main rendering loop function of the program. The shell will
				call this function every frame.
				eglSwapBuffers() will be performed by PVRShell automatically.
				PVRShell will also manage important OS events.
				Will also manage relevent OS events. The user has access to
				these events through an abstraction layer provided by PVRShell.
******************************************************************************/
bool OGLES2BinaryShader::RenderScene()
{
	// Matrix used for projection model view
	float afIdentity[] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	// Clears the color buffer.
	glClear(GL_COLOR_BUFFER_BIT);

	//	Bind the projection model view matrix (PMVMatrix) to
	//	the associated uniform variable in the shader
	GLint i32PMVLocation = glGetUniformLocation(m_uiProgramObject, "myPMVMatrix");

	// Then pass the matrix to the shader
	glUniformMatrix4fv(i32PMVLocation, 1, GL_FALSE, afIdentity);

	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_ui32Vbo);

	// Enable the custom vertex attribute at index VERTEX_ARRAY.
	// We previously binded that index to the variable in our shader "vec4 MyVertex;"
	glEnableVertexAttribArray(VERTEX_ARRAY);

	// Points to the data for this vertex attribute
	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draws a non-indexed triangle array from t