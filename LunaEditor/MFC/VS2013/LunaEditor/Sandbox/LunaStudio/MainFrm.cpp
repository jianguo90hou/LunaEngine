<!DOCTYPE html>
<html lang="en">
<head>
	<title>The PowerVR SDK Browser</title>
	<meta charset="UTF-8" />
	<link rel="stylesheet" type="text/css" href="style.css">
    <link rel="icon" type="image/png" href="./images/img-icon.png">
</head>

<body>
	<div id="GlobalHeaderContainer">
		<div id="GlobalHeader">
			<div class="logo">
				<a href="http://www.powervrinsider.com" target="_blank"><img src="./images/PVRlogo.png" width="40%" height="40%" /></a>
            </div>
			<div class="sitetitle">PowerVR SDK Browser</div>
		</div>
	</div>
	<div id="NavContainer">
		<nav>
			<div class="navlink">
				<a href="Home.html">Home</a>
			</div>
			<div class="navlink">
				<a href="GettingStarted.html">Getting Started</a>
			</div>
			<div class="navlink">
				<a href="Examples.html">Examples</a>
			</div>
			<div class="navlink">
				<a href="Framework.html" class="current">Framework</a>
			</div>
			<div class="navlink">
				<a href="Documentation.html">Documentation</a>
			</div>
			<div class="navlink">
				<a href="PowerVRTools.html">PowerVR Tools</a>
			</div>
			<div class="navlink">
				<a href="ReleaseNotes.html">Release Notes</a>
			</div>
			<div class="navlink">
				<a href="Contact.html">Contact Us</a>
			</div>
		</nav>
	</div>

    <div class="content">
        <h1>Framework</h1>
		<p>The PowerVR Graphics SDK provides a framework which is made up of PVRShell and PVRTools. 
		PVRShell is a simple, light-weight architecture for the barebones of application setup, shutdown and event handling. 
		It is designed to streamline the process of writing cross-platform graphics applications. 
		PVRTools, on the other hand, is a cross-platform tools library containing the most commonly used functionality in a 3D graphics application.</p>
		<hr/>
		<p><a href="#PVRShell" class="link">PVRShell</a>  |  <a href="#PVRTools" class="link">PVRTools</a></p>
		<div id="PVRShell">
			<h2>PVRShell</h2>
			<p>PVRShell is used in all our <a href="Examples.html">Examples</a> (except for HelloAPI) to provide a common framework for developing OpenGL ES applications on any PowerVR platform. The shell takes a set of command-line arguments which allow items like the position and size of the example to be controlled. The table below identifies these options.</p>
			<table>
				<thead>
					<th>Option</th><th>Description</th>
				</thead>
				<tr>
					<td>-aasamples=N</td><td>Sets the number of samples to use for full screen anti-aliasing, e.g., 0, 2, 4, 8.</td>
				</tr>
				<tr>
					<td>-c=N</td><td>Save a single screenshot or a range, for a given frame or frame range, e.g., -c=14, -c=1-10.</td>
				</tr>
				<tr>
					<td>-colourbpp=N or -cbpp=N</td><td>Frame buffer colour bits per pixel. When choosing an EGL config, N will be used as the value for EGL_BUFFER_SIZE.</td>
				</tr>
				<tr>
					<td>-config=N</td><td>Force the shell to use the EGL config with ID N.</td>
				</tr>
				<tr>
					<td>-depthbpp=N or -dbpp=N</td><td>Depth buffer bits per pixel. When choosing an EGL config, N will be used as the value for EGL_DEPTH_SIZE.</td>
				</tr>
				<tr>
					<td>-discardframeall</td><td>Selects whether to explicitly request a discard of all contents of the relevant framebuffer at the end of every frame to save bandwidth.</td>
				</tr>
				<tr>
					<td>-discardframecolour</td><td>Selects whether to explicitly request a discard of the frame colour of the relevant framebuffer at the end of every frame to save bandwidth. Default: false.</td>
				</tr>
				<tr>
					<td>-discardframedepth</td><td>Selects whether to explicitly request a discard of the frame depth of the relevant framebuffer at the end of every frame to save bandwidth. Default: true.</td>
				</tr>
				<tr>
					<td>-discardframestencil</td><td>Selects whether to explicitly request a discard of the frame stencil of the relevant framebuffer at the end of every frame to save bandwidth. Default: true.</td>
				</tr>
				<tr>
					<td>-display</td><td>EGL only. Allows specifying the native display to use if the device has more than one.</td>
				</tr>
				<tr>
					<td>-forcefra