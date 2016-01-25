id="TexturingShort"><p><p>This training course illustrates how to perform alpha testing and provides a visual comparison between alpha blending and alpha testing.
</p></p></div>
							<br>
							<div class="FullDescription" id="TexturingFull">
								<p><strong>Description:</strong></p>
								<p><p>Alpha testing is a technique through which a test is conducted on a per-fragment basis to determine whether that fragment should be discarded and not contribute to the final scene. This can allow complex shapes to be drawn using very simple geometries, but often at the price of hardware optimisations in the graphics pipeline. In programmable graphics pipelines supporting GLSL this is done through the use of the 'discard' keyword in the fragment shader while in the fixed function pipeline API OpenGL ES 1.x this is performed by calling either glEnable(GL_BLEND) or glEnable(GL_ALPHA_TEST).
</p></p>
								<p><strong>Controls:</strong></p>
								<p><p>	Esc	:	Close the application</p></p>
								<p><strong>Links:</strong></p>
								<p class="source"><a href="../../Examples/Intermediate/AlphaTest/OGLES2/OGLES2AlphaTest.cpp" target="_blank">OGLES2AlphaTest.cpp</a>  |  <a href="../../Examples/Intermediate/AlphaTest/OGLES2/Build/" target="_blank">Projects</a></p>
							</div>
						</input>
					</div>
				</li>
				<li id="AnisotropicLighting">
					<div class="title">
						<a href="../../Examples/Intermediate/AnisotropicLighting/AnisotropicLighting.png" title="Click to view image" target="_blank"><img class="examplesmall" src="../../Examples/Intermediate/AnisotropicLighting/AnisotropicLighting.png" alt="AnisotropicLighting" /></a>
						<input type="checkbox" id="AnisotropicLightingFull2">
							<label for="AnisotropicLightingFull2" title="Click for more information"><h3>AnisotropicLighting</h3></label>
							<div class="ShortDescription" id="TexturingShort"><p><p>In this training course two techniques are shown for generating an anisotropic lighting effect, one technique using per vertex/pixel calculations, and the other using a texture lookup.
</p></p></div>
							<br>
							<div class="FullDescription" id="TexturingFull">
								<p><strong>Description:</strong></p>
								<p><p>In this training course two techniques are shown for generating an anisotropic lighting effect (the effect of surface grain on materials such as brushed metal, velvet etc.).  The first technique uses per vertex and pixel calculations to calculate the shading and thus generate the effect on the fly.  The second technique uses a texture lookup to determine the shading and would be useful in situations where bandwidth was more readily available than processing time.
</p></p>
								<p><strong>Controls:</strong></p>
								<p><p>	Left/Right Arrow	:	Toggle effect</p><p>	Esc	:	Close application</p></p>
								<p><strong>Links:</strong></p>
								<p class="source"><a href="../../Examples/Intermediate/AnisotropicLighting/OGLES2/OGLES2AnisotropicLighting.cpp" target="_blank">OGLES2AnisotropicLighting.cpp</a>  |  <a href="../../Examples/Intermediate/AnisotropicLighting/OGLES2/Build/" target="_blank">Projects</a></p>
							</div>
						</input>
					</div>
				</li>
				<li id="Bloom">
					<div class="title">
						<a href="../../Examples/Intermediate/Bloom/Bloom.png" title="Click to view image" target="_blank"><img class="examplesmall" src="../../Examples/Intermediate/Bloom/Bloom.png" alt="Bloom" /></a>
						<input type="checkbox" id="BloomFull2">
							<label for="BloomFull2" title="Click for more information"><h3>Bloom</h3></label>
							<div class="ShortDescription" id="TexturingShort"><p><p>This training course demonstrates a simple implementation of a 'bloom' effect.
</p></p></div>
							<br>
							<div class="FullDescription" id="TexturingFull">
								<p><strong>Description:</strong></p>
								<p><p>This training course demonstrates a simple implementation of a 'bloom' post processing effect. The bright parts of the picture are extracted in a post processing step, blurred and added over the final image to create a glow around the object's borders.
</p></p>
								<p><strong>Controls:</strong></p>
								<p><p>	Up/Down	:	Toggle the bloom effect On/Off</p><p>	Esc	:	Close the application</p></p>
								<p><strong>Links:</strong></p>
								<p class="source"><a href="../../Examples/Intermediate/Bloom/OGLES2/OGLES2Bloom.cpp" target="_blank">OGLES2Bloom.cpp</a>  |  <a href="../../Examples/Intermediate/Bloom/OGLES2/Build/" target="_blank">Projects</a></p>
							</div>
						</input>
					</div>
				</li>
				<li id="Bumpmap">
					<div class="title">
						<a href="../../Examples/Intermediate/Bumpmap/Bumpmap.png" title="Click to view image" target="_blank"><img class="examplesmall" src="../../Examples/Intermediate/Bumpmap/Bumpmap.png" alt="Bumpmap" /></a>
						<input type="checkbox" id="BumpmapFull2">
							<label for="BumpmapFull2" title="Click for more information"><h3>Bumpmap</h3></label>
							<div class="ShortDescription" id="TexturingShort"><p><p>This training course demonstrates an example of using a normal map to implement bump mapping.
</p></p></div>
							<br>
							<div class="FullDescription" id="TexturingFull">
								<p><strong>Description:</strong></p>
								<p>