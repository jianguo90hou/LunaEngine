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
				<a href="Framework.html">Framework</a>
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
        <h1>Getting Started</h1>
		<p><strong>Platform setup:</strong> <a href="#android" class="link">Android</a>  |  <a href="#ios" class="link">iOS</a>  |  <a href="#windows" class="link">Windows</a>  |  <a href="#osx" class="link">OS X</a>  |  <a href="#linux" class="link">Linux</a>  |  <a href="#webgl" class="link">WebGL</a>
		<p><strong>Tutorials:</strong> <a href="#xcodeoglespvrvframe" class="link">XCode project setup for OpenGL ES using PVRVFrame</a></p>
		
		<hr/>		
		<h3><strong>Platform Setup</strong></h3>
		<p><em><strong>Note:</strong> PVRVFrame PC Emulation is not intended to be a completely accurate replication of the behaviour of PowerVR hardware. This tool is a wrapper around desktop OpenGL so its performance and capabilities will depend on the 3D acceleration present in your system.</em><p>
		<p>The installation instructions contained in this section use various placeholders. The table below identifies the placeholders and their corresponding description.</p>
		<table>
				<thead>
					<th>Placeholder</th><th>Description</th>
				</thead>
				<tr>
					<td>[API]</td><td>Shorthand for the targeted Application Programming Interface, e.g., OGLES2 for OpenGL ES 2.0.</td>
				</tr>
				<tr>
					<td>[ExampleName]</td><td>The name of the example application that you are building.</td>
				</tr>
				<tr>
					<td>[Level]</td><td>The name of the folder the examples are sorted into according to their complexity. These folders are named either Beginner, Intermediate or Advanced.</td>
				</tr>
				<tr>
					<td>[Platform]</td><td>The targeted Application Binary Interface, e.g., x86.</td>
				</tr>
				<tr>
					<td>[PVRVFrameShort]</td><td>Shorthand term used in the file name of a PVRVFrame specific .dll or .lib file, e.g., GLES_CM in libGLES_CM.dll.</td>
				</tr>
				<tr>
					<td>[ReleaseDir]</td><td>This refers to the release directory, which is either ReleaseRaw or ReleaseX11 in the case of Linux.</td>
				</tr>
				<tr>
					<td>[Target]</td><td>ID number of the Android list target.</td>
				</tr>
		</table>
		
		<div id="android">
		<h2>Android</h2>
			<p>The following instructions for building the examples in the Android PowerVR Graphics SDK assume that you have already installed the Android SDK from Google, the NDK and Apache Ant.</p>
			<p>To build individual components go to the <span class="code">/Build/Android</span> sub-directory of the component to build. To create local properties, on the first build you will need to run:</p>
			<ol>
				<li>
				<p><span class="code">android update project -p . -t [Target]</span>, where the list of targets can be found with the following command (<span class="code">[Target]</span> corresponds to the ID number): <span class="code">android list target</span></p>
				</li>
			</ol>
			<p>To use the Android tool you need to have��� �c������|��  �                                                                                                          