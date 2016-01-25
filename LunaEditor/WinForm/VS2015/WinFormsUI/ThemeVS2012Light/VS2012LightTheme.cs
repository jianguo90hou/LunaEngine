 the Android SDK's tool folder in your path. After this, the building of an application is done in two stages. The first stage involves compiling the C++ code into a library. This is achieved using <span class="code">ndk-build</span> which is part of the Android NDK and needs to be present in your path. To compile for all supported platforms:</p>
			<ol>
				<li>
				<p>Type <span class="code">ndk-build</span></p>
				</li>
				<li>
				<p>On an a specific platform you can compile by typing: <span class="code">ndk-build APP_ABI=[Platform]</span>. <span class="code">[Platform]</span> is an entry from one of the following supported ABIs:</p>
					<ul>
						<li>armeabi</li>
						<li>armeabi-v7a</li>
						<li>x86</li>
						<li>mips</li>
					</ul>
				</li>
				<li>
				<p>The second stage compiles the remaining Java components and creates the APK file for installing on your device. The quickest way of achieving this is to type: <span class="code">ant debug</span>. This will create an APK file in <span class="code">./bin</span> and will handle the signing of your application for you. For creating a release build of your app please visit the relevant page at <a href="http://developer.android.com/guide/index.html" target="_blank">http://developer.android.com/guide/index.html</a>.</p>
				</li>
			</ol>
			
			<h3>Using Android SDK Manager</h3>
			<p>The following instructions for building the examples in the PowerVR Graphics SDK assume that you have an Eclipse environment with the Android SDK and NDK installed, as well as the NDK Eclipse plug-in. For more details about using the NDK, please visit <a href="http://tools.android.com/recent/usingthendkplugin" target="_blank">Android Tools Project Site</a>.
			<p>To download the Android PowerVR Graphics SDK through the Android SDK Manager, perform the following steps:</p>
			<ol>
				<li>
				<p>Open the Android SDK manager.</p>
				</li>
				<li>
				<p>Open the <span class="code">Tools -> Manage Add-on Sites</span> window and click the <span class="code">User Defined Sites</span> tab.</p>
				</li>
				<li>
				<p>Click <span class="code">New...</span> and add the following URL: <a href="http://cdn.imgtec.com/sdk/androidsdk.xml" target="_blank">http://cdn.imgtec.com/sdk/androidsdk.xml</a></li> The PowerVR SDK should now appear on the <span class="code">Packages</span> list, under <span class="code">API 10</span>.</p>
				</li>
				<li>
				<p>Once the SDK is installed you will then need to add the <span class="code">PVRSDKDIR</span> environment variable for your NDK builds. To do so in Eclipse, click <span class="code">Window</span> and open the <span class="code">Preferences</span> menu. From there, navigate to <span class="code">C/C++ -> Build -> Environment</span> and add the variable <span class="code">PVRSDKDIR</span>, setting its value to where the add-on is installed (typically under the add-ons directory inside the Android SDK).</p>
				</li>
				<li>
				<p>All the examples can be imported by selecting the PowerVR SDK during the creation of a new Android sample project in Eclipse.</p>
				</li>
			</ol>
			<p><em><strong>Note:</strong> Please note that for Windows we recommend to point <span class="code">PVRSDKDIR</span> to <span class="code">../</span> and copy the <span class="code">shell/</span>, <span class="code">tools/</span> and <span class="code">builds/</span> directories from the add-on folder to your <span class="code">workspace/</span>. This is due to the dropping of support for Windows paths in GNU Make 3.81 onwards. Otherwise the use of paths containing <span class="code">:</span> yields the error <span class="code">*** target pattern contains no '%'</span>.</em></p>
			<p><em><strong>Note:</strong> For Windows, the Eclipse CDT <span class="code">"Scanner Configuration Builder"</span> appears not to be working with the directory structure of our <span class="code">samples/tools/shell</span>. For that reason is recommended to disable it from your project. To do this, right-click <span class="code">Project Name -> Properties -> Builders -> Disable the "Scanner Configuration Builder"</strong>.</em></p>
		</div>
		
		<div id="ios">
		<h2>iOS</h2>
			<p>To proceed with the installation of the PowerVR Graphics SDK on iOS, complete the following steps:<p>
			<ol>
				<li>
				<p>Download a version of Apple's iOS SDK from <a href="http://developer.apple.com/ios/" target="_blank">http://developer.apple.com/ios/</a>. You will need to become a member of Apple's developer programme in order to access this page. You can find details of how to join at <a href="http://developer.apple.com" target="_blank">http://developer.apple.com</a>.</p>
				</li>
				<li>
				<p>Install the Apple SDK on your Mac as specified by Apple's hardware and software requirements. This should also install Xcode and the other development tools required.</p>
				</li>
				<li>
				<p>Expand the PowerVR Graphics SDK for iOS to a location for which you have both read and write access.</p>
				</li>
				<li>
				<p>To build the examples and other projects from the SDK, find the various <span class="code">[API]***.xcode</span> projects available within the <span class="code">SDKPackage_[API]</span> directory and double click these to launch them in Xcode.</p>
				</li>
				<li>
				<p>To build for an iOS device you will need a valid developer certificate in your machine's keychain. You may also have to change the <span class="code">Properties | Identifier</span> property from <span class="code">Project | Edit Active Target...</span> to match that which you have set up for yourself through Apple's Program Portal.</p>
				</li>
				<li>
				<p>If you do not have a developer certificate from Apple then you can still build and launch applications in the iOS Simulator. Choose this configuration from the dropdown menu at the top left and then choose <span class="code">Build and Run</span> from the dropdown menu.</p>
				</li>
			</ol>
			<p><em><strong>Note:</strong> The Scheme that you are building under may need to be set up for the SDK's projects to run.</em></p>
		</div>
		
		<div id="windows">
		<h2>Windows</h2>
			<p>This SDK requires a PC equipped with Windows XP, Windows Vista or Windows 7. The required installation steps are:</p>
			<ol>
				<li>
				<p>Install the SDK on your machine as specified by Windows hardware and software requirements. The project and solution files provided do not require the SDK to be installed in a pre-defined location and are configured to use relative paths.</p>
				</li>
				<li>
				<p>Copy the API-specific emulation "drivers" to a DLL-accessible directory prior to running the SDK applications. The API-specific emulation "drivers" are called <span class="code">libEGL.dll</span>, <span class="code">libEGL.lib</span>, <span class="code">lib[PVRVFrameShort].dll</span> and <span class="code">lib[PVRVFrameShort].lib</span>. The files are located by default in <span class="code">\Builds\Windows\x86_32\Lib</span> and <span class="code">\Builds\Windows\x86_64\Lib</span>.</p>
				</li>
			</ol>
			<p><em><strong>Note:</strong> The examples can be launched directly from their project files.</em></p>
		</div>
		
		<div id="osx">
		<h2>OS X</h2>	
			<p>The OS X SDK requires OS X (Snow Leopard) or higher for full operation.</p>
			<ol>
				<li>
				<p>Install the latest version of Xcode, available from <a href="http://developer.apple.com/" target="_blank">http://developer.apple.com/</a> or from the Mac App store.</p>
				<li>
				<p>Expand the PowerVR Graphics SDK for OS X into a location for which you have full access.</p>
				</li>
				<li>
				<p>To build the examples and other projects from the SDK, find the various <span class="code">[API]***.xcodeproj</span> projects available within the <span class="code">SDKPackage_[API]</span> directory and double click these to launch them in Xcode.</p>
				</li>
			</ol>
			<p><em><strong>Note:</strong> The Scheme that you are building under may need to be set up for the SDK's projects to run.</em></p>
		</div>
		
		<div id="linux">
		<h2>Linux</h2>
			<p><em><strong>Note:</strong> API libraries are not distributed with the PowerVR Graphics SDK for Linux. Please ask your platform provider for these libraries if you do not have them. You will also need to install the latest platform toolchain on your development machine for your target platform.</em></p>
			<p>To build the code examples, follow the steps below:</p>
			<ol>
				<li>
				<p>Define the <span class="code">TOOLCHAIN</span> environment variable to the toolchain directory, or add the path of the toolchain to the <span class="code">PATH</span> environment variable (i.e., run <span class="code">export PATH="<i>path to the toolchain</i>:$PATH"</span>).</p>
				</li>
				<li>
				<p>If you want an X11 build and it is available, define the environment variable <span class="code">X11ROOT</span> to point to the <span class="code">freedesktop</span> directory (i.e., <span class="code">export X11ROOT=/usr/X11R6_SGX</span>).</p>
				</li>
				<li>
				<p>To build individual components go to the directory <span class="code">Examples/[Level]/[ExampleName]/[API]/Build/LinuxGeneric</span> and run the command: <span class="code">LinuxRaw: "make PLATFORM=[Platform]"</span> or <span class="code">LinuxX11: "make PLATFORM=[Platform] X11BUILD=1"</span>. <span class="code">[Platform]</span> is an entry from one of the following supported ABIs:</p>
					<ul>
						<li>linux_armv7</li>
						<li>linux_armv7hf</li>
						<li>linux_x86_32</li>
						<li>linux_x86_64</li>
					</ul>
				</li>
			</ol>
				<p>The executables for the examples will be under:	<span class="code">Examples/[Level]/[ExampleName]/[API]/Build/[Platform]/[ReleaseDir]</span> where <span class="code">[ReleaseDir]</span> is one of <span class="code">ReleaseRaw</span> or <span class="code">ReleaseX11</span>. <span class="code">[ExampleName]</span> is the name of the example that you are building and <span class="code">[Level]</span> is either <span class="code">Beginner</span>, <span class="code">Intermediate</span> or <span class="code">Advanced</span>.</p>
			<p>To run an executable, follow the steps below:</p>
			<ol>
				<li>
				<p>Ensure that the PowerVR drivers are installed on the target device (please refer to the DDK/driver installation instructions).</p>
				</li>
				<li>
				<p>If the standard C++ libraries are not present on your target device, copy <span class="code">libc++</span> from the toolchain into <span class="code">/usr/lib</span>. <span class="code">libdl</span> and <span class="code">libgcc</span> may also be required.</p>
				<p><em><strong>Note:</strong> <span class="code">libc++</span> lives at <span class="code">/usr/lib</span> if you have installed the drivers, or can be found as part of a binary driver release package.</em></p>
				</li>
				<li>
				<p>Ensure the drivers are running (e.g., type <span class="code">/etc/init.d/rc/pvr</span> start, then run an X session if required).</p>
				<p>Under X11, window sizes can be specified for the executables using the command-line arguments <span class="code">-posx=n</span> and <span class="code">-posy=n</span> to define the top right hand corner, and <span class="code">-width=n</span> and <span class="code">-height=n</span> to define width and height, respectively.</p>
				<p>For example:</p>
				<p class="code">./[API]IntroducingPOD  -posx=10 -posy=10 -width=100 -height=100</p>
				</li>
				<li>
				<p>If you attempt to run an SDK example and it fails with the message: <span class="code">"Can't open display"</span> produced by the X client, then make sure that the <span class="code">DISPLAY</span> variable is set with the shell command: <span class='code'>"set | grep -e DISPLAY"</span>. If this command does not yield any output then type (in shell): <span class='code'>"DISPLAY=:0.0; export DISPLAY"</span></p>
				</li>
			</ol>
		</div>

		<div id="webgl">
		<h2>WebGL</h2>	
			<p>The steps below highlight the procedure for setting up the WebGL SDK:</p>
			<ol>
				<li>
				<p>To host and run the WebGL SDK you will need a web server. Since the WebGL SDK only uses HTML5 and JavaScript (no dynamically generated content) any web server capable of serving HTML is suitable for hosting it. The WebGL SDK does not require building.</p>
				</li>
				<li>
				<p>To use the WebGL SDK, copy across the contents of the WebGL package to an appropriate location in your web server tree (in some cases, also configure your web server to serve it), keeping the folder structure intact.</p> 
				</li>
				<li>
				<p>You can then navigate to and launch the required example from the SDK Browser.</p>
				</li>
			</ol>
			<p><em><strong>Note:</strong> If you do not have a web server available, you will need to install and configure one, as appropriate. For example, on Windows, IIS is usually built in and may require to be enabled and configured. On OS X, Apache may require to be enabled and configured. Most Linux distributions will contain a web server such as Apache. Alternatively, you may want to download, install and configure another web server depending on what your specific needs are. A useful <a href="http://en.wikipedia.org/wiki/Comparison_of_web_server_software" target="_blank">comparison of web server software</a> is available in Wikipedia.</em></p>
		</div>
		
		<hr/>
		<h3><strong>Tutorials</strong></h3>
		<div id="xcodeoglespvrvframe">
		<h2>XCode Project Setup for OpenGL ES Using PVRVFrame</h2>	
			<p>The following steps detail how to set up, from scratch, an XCode project for OpenGL ES using PVRVFrame:</p>
			<ol>
				<li>
				<p>Open the XCode application and then click <span class="code">File -> New -> Project</span> from the menu. Select <span class="code">Cocoa Application</span> from the template OS X or Application. Select <span class="code">Next</span> and fill the product name, e.g., <span class="code">IntroducingPOD</span>, and the company identifier. Other fields can be left as is. Then select the project destination directory.</p>
				</li>
				<li>
				<p>To organise the project, right-click on it from the <span class="code">Project Navigator</span> and select <span class="code">New Group</span>. Following this, create the following groups (which will contain the mentioned application contents):</p>
				<ul>
					<li>Source/Shell (Shell source files)</li>
					<li>Content/Models (.pod files)</li>
					<li>Content/Textures (.pvr textures)</li>
					<li>Content/Shaders (shaders)</li>
					<li>Libraries (dependencies)</li>
				</ul>
				</li>
				<li>
				<p>Right click the <span class="code">Shell</span> group and select <span class="code">Add Files</span> to <span class="code">"project name"</span> and add these following files:</p>
				<ul>
					<li><span class="code">PVRShell.h</span>,  <span class="code">PVRShell.cpp</span>, <span class="code">PVRShellImpl.h</span> (from <span class="code">[sdk-installation-directory]/Shell</span>)</li>
					<li><span class="code">PVRShellAPI.h</span>, <span class="code">PVRShellAPI.cpp,</span> (from <span class="code">[sdk-installation-directory]/Shell/API/KEGL</span>)</li>
					<li><span class="code">main.m</span>, <span class="code">PVRShellOS.h</span>, <span class="code">PVRShellOS.cpp</span>, <span class="code">AppController.mm</span>, <span class="code">AppController.h</span> (from <span class="code">[sdk-installation-directory]/  /Shell/OS/OSX</span>)</li>
				</ul>
				</li>
				<li>
				<p>Under the <span class="code">Source</span> group create a new .cpp file for your application code and include the following header files:</p>
				<ul>
					<li><span class="code">PVRShell.h</span></li>
					<li><span class="code">OGLES3Tools.h</span></li>
				</ul>	
				</li>
				<li>
				<p>Right-click the <span class="code">Libraries</span> group and then select <span class="code">Add Files</span> to <span class="code">"project name"</span> and navigate to the <span class="code">[sdk-installation-directory] /Tools/[API]/Build/OSX/[API]Tools.xcodeproj</span> and add this project.</p>
				</li>
				<li>
				<p>Go to your project‚Äôs <span class="code">Targets Build Phases</span> settings and add the following source files under the <span class="code">Compile Sources</span> section:</p>
				<ul>
					<li>Your application source file</li>
					<li>PVRShell.cpp</li>
					<li>PVRShellAPI.cpp</li>
					<li>PVRShellOS.cpp</li>
					<li>main.m</li>
					<li>AppController.mm</li>
				</ul>
				<p>Add the library files under <span class="code">LinkBinary With Libraries</span> section:</p>
				<ul>
					<li><span class="code">Lib[API]Tools.a</span></li>
					<li><span class="code">Quartzcore.framework</span></li>
					<li><span class="code">libEGL.dylib</span> located at <span class="code">[sdk-installation-directory]/ /Builds/OSX/x86/Lib</span></li>
					<li><span class="code">libGLESv2.dylib</span> located at <span class="code">[sdk-installation-directory]/ /Builds/OSX/x86/Lib</span></li>
				</ul>
				<p>Then add all content files (such as PVR files, POD files, shaders, icons, etc.) under <span class="code">Copy Bundle Resources</span>.</p>
				<p>Following this, add a new build phase called <span class="code">Copy Files</span>, and select <span class="code">Destination Frameworks</span> and add these following library files:</p>
				<ul>
					<li><span class="code">libEGL.dylib</span></li>
					<li><span class="code">libGLESv2.dylib</span></li>
				</ul>
				</li>
				<li>
				<p>Go to your project‚Äôs <span class="code">Targets Build Phases</span> settings, and under the <span class="code">Preprocessing</span> section add <span class="code">BUILD [API] preprocessor for Debug and release configuration</span>. Then under the <span class="code">Search</span> paths section select <span class="code">Yes for Always Search User Paths</span> and add these header search paths to <span class="code">User Header Search Paths</span>:</p>
				<ul>
					<li><span class="code">[sdk-installation-directory]/Builds/Include</span></li>
					<li><span class="code">[sdk-installation-directory]/Tools/[API]</span></li>
					<li><span class="code">[sdk-installation-directory]/Tools</span></li>
				</ul>
				<p>If your targeted API is OGLES3 then you also have to add:</p>
				<ul>
					<li><span class="code">[sdk-installation-directory]/Builds/Tools/OGLES2</span></li>
				</ul>
				<p>Add these following paths to the Library Search Paths:</p>
				<ul>
					<li><span class="code">[sdk-installation-directory]/Builds/OSX/x86/Lib</span></li>
				</ul>
				</li>
			</ol>
		</div>
		<br>
	</div>

	<div id="FooterMainContainer">
		<div id="FooterContainer">
			<div class="footerlogo">
				<a href="http://www.imgtec.com" target="_blank"><img src="./images/img-footer-logo-grey.png" width="100%" height="100%" /></a>
			</div>
			<div class="copyright">&copy; Imagination Technologies Limited<br> All rights reserved</div>
		</div>
	</div>
</body>

</html>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           âPNG

   IHDR  ¨  0   ÛøJä   	pHYs    gü“R  
OiCCPPhotoshop ICC profile  x⁄ùSgTSÈ=˜ﬁÙBKàÄîKoR RBãÄë&*!	Jà!°ŸQ¡EE»†àééÄåQ,ä
ÿ‰!¢éÉ£àä ˚·{£k÷º˜ÊÕ˛µ◊>Á¨Ûù≥œ¿ñH3Q5Ä©B‡É«ƒ∆·‰.@Å
$p ≥d!s˝# ¯~<<+"¿æ x” ¿Mõ¿0áˇÍBô\ÄÑ¿të8KÄ @zéB¶ @FÄùò&S † `Àcb„ P- `'Ê” Äù¯ô{ [î!†ë  eàD h; ¨œVäE X0 fKƒ9 ÿ- 0IWfH ∞∑ ¿Œ≤  0QàÖ) { `»##x Ñô FÚW<Ò+ÆÁ*  xô≤<π$9EÅ[-qWW.(ŒI+6aaö@.¬yô2Å4‡ÛÃ  †ë‡ÉÛ˝xŒÆŒŒ6é∂_-Íøˇ"bb„˛Âœ´p@  ·t~—˛,/≥Ä;Äm˛¢%Óh^†u˜ãf≤@µ †È⁄WÛp¯~<<E°êπŸŸÂ‰‰ÿJƒB[a W}˛g¬_¿W˝l˘~<¸˜ı‡æ‚$Å2]ÅG¯‡¬ÃÙL•œí	Ñb‹ÊèG¸∑ˇ¸”"ƒIbπX*„QqéDöåÛ2•"âBí)≈%“ˇd‚ﬂ,˚>ﬂ5 ∞j>{ë-®]cˆK'Xt¿‚˜  Úªo¡‘(ÄhÉ·œwˇÔ?˝G†% ÄfIíq  ^D$.T ≥?«  D†Å*∞AÙ¡,¿¡‹¡¸`6ÑB$ƒ¬BB
dÄr`)¨ÇB(ÜÕ∞*`/‘@4¿QhÜìp.¬U∏=p˙aû¡(ºÅ	A»a!⁄àbäX#éôÖ¯!¡Hã$ …àQ"Kë5H1RäT UHÚ=r9á\F∫ë;» 2Ç¸ÜºG1îÅ≤Q=‘µCπ®7ÑF¢–dt1öè†õ–r¥=å6°Á–´h⁄è>C«0¿Ë3ƒl0.∆√B±8,	ìcÀ±"¨´∆∞V¨ªâıcœ±wÅE¿	6wB aAHXLXNÿH® $4⁄	7	ÑQ¬'"ì®K¥&∫˘ƒb21áXH,#÷è/{àCƒ7$âC2'πêI±§T““F“nR#È,©õ4H#ì…⁄dk≤9î, +»Ö‰ù‰√‰3‰‰!Ú[
ùb@q§¯S‚(R jJÂÂ4Âeò2AU£öR›®°T5èZB≠°∂RØQá®4uö9ÕÉIK•≠¢ï”hh˜iØËt∫›ïNó–W“ÀÈGËóËÙwÜÉ«àg(õgwØòL¶”ã«T071ÎòÁôôoUX*∂*|ë 
ïJï&ï*/T©™¶™ﬁ™UÛUÀTè©^S}ÆFU3S„©	‘ñ´U™ùPÎSSg©;®á™g®oT?§~Y˝âY√L√OC§Q†±_„º∆ c≥x,!k´ÜuÅ5ƒ&±ÕŸ|v*ªò˝ªã=™©°9C3J3W≥RÛîf?„òq¯útN	Á(ßóÛ~äﬁÔ)‚)¶4Lπ1e\k™ñóñX´H´Q´GÎΩ6ÆÌßù¶ΩEªY˚ÅA«J'\'GgèŒùÁSŸS›ß
ßM=:ıÆ.™k•°ªDwønßÓòûæ^ÄûLoßﬁyΩÁ˙}/˝T˝m˙ßıGX≥$€Œ<≈5qo</«€ÒQC]√@C•aïaó·Ñëπ—<£’FçFåi∆\„$„m∆m∆£&&!&KMÍMÓöRMπ¶)¶;L;L«ÕÃÕ¢Õ÷ô5õ=1◊2ÁõÁõ◊õﬂ∑`ZxZ,∂®∂∏eI≤‰Z¶YÓ∂ºnÖZ9Y•XUZ]≥F≠ù≠%÷ª≠ªßßπNìN´û÷g√∞Ò∂…∂©∑∞Âÿ€Æ∂m∂}agbg∑≈Æ√ÓìΩì}∫}ç˝=áŸ´Z~s¥r:V:ﬁöŒúÓ?}≈ÙñÈ/gXœœÿ3„∂À)ƒiùSõ”GggπsÉÛàãâKÇÀ.ó>.õ∆›»Ω‰Jtıq]·z“ıùõ≥õ¬Ì®€ØÓ6ÓiÓá‹üÃ4ü)ûY3s–√»C‡QÂ—?üï0kﬂ¨~OCOÅgµÁ#/c/ëW≠◊∞∑•w™˜aÔ>ˆ>rü„>„<7ﬁ2ﬁY_Ã7¿∑»∑ÀO√oû_ÖﬂC#ˇdˇzˇ— ßÄ%gâÅAÅ[˚¯z|!øé?:€eˆ≤ŸÌAå†πAAèÇ≠ÇÂ¡≠!h»Ïê≠!˜ÁòŒëŒiÖP~Ë÷–aÊaã√~'ÖáÖWÜ?épàX—1ó5w—‹CsﬂD˙DñDﬁõg