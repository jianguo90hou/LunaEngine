

	// Save the binary format.
	if(!fwrite((void*)&binaryFormat,sizeof(GLenum),1,outfile)) 
	{
		fclose(outfile);
		return false; // Couldn't write binary format to file.
	}

	// Save the actual binary program.
	if(!fwrite(ShaderBinary, length,1,outfile))
	{
		fclose(outfile);
		return false;				 // Couldn't write binary data to file.
	}

	// Close the file.
	fclose(outfile);

	// Free the memory used by Shader Binary.
	free(ShaderBinary);
	return true;
#else
	return false;
#endif
}
/*!****************************************************************************
 @Function		loadBinaryProgram
 @Return		bool	True if load succeeded.
 @Description	This function takes as input the ID of a shader program object
				which should have been created prior to calling this function,
				as well as a filename to load the binary program from.
				The function will load in a file storing the binary shader
				program, and the enum value determining its format.
				It will then load the binary into memory.

 @Note:			Th