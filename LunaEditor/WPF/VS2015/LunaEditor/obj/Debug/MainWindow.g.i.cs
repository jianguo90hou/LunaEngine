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
				<a href="PowerVRTools.html" class="current">PowerVR Tools</a>
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
        <h1>PowerVR Tools</h1>
		<p>The suite of utilities in the SDK is designed to enable rapid graphics application development. It targets a range of areas including asset exporting and optimization, PC emulation, prototyping environments, online and offline performance analysis tools and many more.</p>
		<p>Each utility supports Windows, OS X and Linux. The minimum requirements are as follows (older versions might still work but limited support will be provided):</p>
		<ul>
			<li>Windows 7</li>
			<li>OS X – An Intel based machine with 10.7 (Lion)</li>
			<li>Linux – Ubuntu 12.04</li>
		</ul>
		<p>Some utilities may have additional requirements, such as minimum version of OpenGL. For more information, please refer to the webpage of the utility you are interested in.</p>		
		<hr/>
		<p><a href="#AssetDeployment" class="link">Asset Deployment Utilities</a>  |  <a href="#Development" class="link">Development Utilities</a>  |  <a href="#PerformanceAnalysis" class="link">Performance Analysis Utilities</a></p>
		<div id="AssetDeployment">
			<h2>Asset Deployment Utilities</h2>
			<ul class="utility">
				<li>
				<img src="./images/PVRTexTool_300x182.png"/>
				<h3>PVRTexTool</h3>
				<p>This is a texture compression tool that supports all OpenGL, OpenGL ES and DirectX formats as well as PowerVR compression formats (PVRTC).</p>
				<p><a href="http://community.imgtec.com/developers/powervr/tools/pvrtextool/" target="_blank">Find out more about PVRTexTool</a></p>
				</li>
				<li>
				<img src="./images/PVRGeoPOD_300x182.png"/>
				<h3>PVRGeoPOD</h3>
				<p>An exporter tool that facilitates exporting 3D scenes and their associated geometry data to the PowerVR Object Data (POD) optimized format.</p>
				<p><a href="http:/