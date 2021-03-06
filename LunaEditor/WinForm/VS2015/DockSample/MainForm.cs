PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <OutDir>$(SolutionDir)$(Platform)\$(Configuration)\</OutDir>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <PreprocessorDefinitions>BUILD_OGLES2;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>..\..\..\..\..\..\Shell;..\..\..\..\..\..\Shell\API\KEGL;..\..\..\..\..\..\Shell\OS\Windows;..\..\..\..\..\..\Builds\Include;</AdditionalIncludeDirectories>
      <RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
      <MultiProcessorCompilation>true</MultiProcessorCompilation>
      <MinimalRebuild>false</MinimalRebuild>
    </ClCompile>
    <Link>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalLibraryDirectories>..\..\..\..\..\..\Builds\Windows\x86_32\Lib;</AdditionalLibraryDirectories>
      <AdditionalDependencies>libEGL.lib;libGLESv2.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <PreprocessorDefinitions>BUILD_OGLES2;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>..\..\..\..\..\..\Shell;..\..\..\..\..\..\Shell\API\KEGL;..\..\..\..\..\..\Shell\OS\Windows;..\..\..\..\..\..\Builds\Include;</AdditionalIncludeDirectories>
      <RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
      <MultiProcessorCompilation>true</MultiProcessorCompilation>
      <MinimalRebuild>false</MinimalRebuild>
    </ClCompile>
    <Link>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalLibraryDirectories>..\..\..\..\..\..\Builds\Windows\x86_64\Lib;</AdditionalLibraryDirectories>
      <AdditionalDependencies>libEGL.lib;libGLESv2.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>MaxSpeed</Optimization>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <PreprocessorDefinitions>BUILD_OGLES2;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>..\..\..\..\..\..\Shell;..\..\..\..\..\..\Shell\API\KEGL;..\..\..\..\..\..\Shell\OS\Windows;..\..\..\..\..\..\Builds\Include;</AdditionalIncludeDirectories>
      <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
      <MultiProcessorCompilation>true</MultiProcessorCompilation>
      <MinimalRebuild>false</MinimalRebuild>
    </ClCompile>
    <Link>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <AdditionalLibraryDirectories>..\..\..\..\..\..\Builds\Windows\x86_32\Lib;</AdditionalLibraryDirectories>
      <AdditionalDependencies>libEGL.lib;libGLESv2.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>MaxSpeed</Optimization>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <PreprocessorDefinitions>BUILD_OGLES2;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>..\..\..\..\..\..\Shell;..\..\..\..\..\..\Shell\API\KEGL;..\..\..\..\..\..\Shell\OS\Windows;..\..\..\..\..\..\Builds\Include;</AdditionalIncludeDirectories>
      <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
      <MultiProcessorCompilation>true</MultiProcessorCompilation>
      <MinimalRebuild>false</MinimalRebuild>
    </ClCompile>
    <Link>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <AdditionalLibraryDirectories>..\..\..\..\..\..\Builds\Windows\x86_64\Lib;</AdditionalLibraryDirectories>
      <AdditionalDependencies>libEGL.lib;libGLESv2.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ClCompile Include="..\..\OGLES2BinaryShader.cpp" />
    <ClCompile Include="..\..\..\..\..\..\Shell\PVRShell.cpp" />
    <ClCompile Include="..\..\..\..\..\..\Shell\API\KEGL\PVRShellAPI.cpp" />
    <ClCompile Include="..\..\..\..\..\..\Shell\OS\Windows\PVRShellOS.cpp" />
  </ItemGroup>
  <ItemGroup>
    <ClInclude Include="..\..\..\..\..\..\Shell\PVRShell.h" />
    <ClInclude Include="..\..\..\..\..\..\Shell\PVRShellImpl.h" />
    <ClInclude Include="..\..\..\..\..\..\Shell\API\KEGL\PVRShellAPI.h" />
    <ClInclude Include="..\..\..\..\..\..\Shell\OS\Windows\PVRShellOS.h" />
    <ClInclude Include="..\..\..\..\..\..\Builds\Windows\Resources\resource.h" />
  </ItemGroup>
  <ItemGroup>
    <ResourceCompile Include="..\..\..\..\..\..\Builds\Windows\Resources\shared.rc" />
  </ItemGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          // This file was created by Filewrap 1.2
// Little endian mode
// DO NOT EDIT

#include "../PVRTMemoryFileSystem.h"

// using 32 bit to guarantee alignment.
#ifndef A32BIT
 #define A32BIT static const unsigned int
#endif

// ******** Start: Tang_space_BodyMap.pvr ********

// File data
A32BIT _Tang_space_BodyMap_pvr[] = {
0x3525650,0x0,0x3,0x0,0x0,0x0,0x200,0x200,0x1,0x1,0x1,0x1,0xf,0x3525650,0x3,0x3,0xc0000200,0x23c0c0c0,0xc0ce1e84,0xc0c0c0,0xffc67f80,0x7e0301ff,0x3fc00c2,0x3f7f7f0f,0xc0ba3fb6,0xc0c0c0,0xc0ce1f80,0xc0c0c0,0x6fc63f80,0x1e6f6faf,0x6fbe3fb6,0x3e6f2f6f,0xffbe3fba,0x5e00ffff,0xfc00ba,0x3f555500,0xffbe5fba,0x5e00ffff,0xfc00be,0x5e89e600,0x55c25fc2,0x5f010101,0x59be5ebe,0x3e99a9a9,0x95be5fbe,0x5eaaa9a5,0xaac25fbe,0x5eaaaaaa,0xc0c25fbe,0xc0c0c0,0xc0ca3f80,0x1c0c0c0,0x6fc65f80,0x3e7f6f6f,0x6fbe3fba,0x5e6fafaf,0xc0be3fbe,0xc0c0c0,0xc0c25f80,0xc0c0c0,0x5fc25f80,0x5f5f5f5f,0x6fc25fba,0x5e0f0f5f,
0x55c25fbe,0x5e050545,0x95c25ebe,0x5e06aa7d,0x55be5fbe,0x5f541045,0xe9c25fc2,0x5e92aaaa,0x99c25fc2,0x5e59a95a,0x9abe5fc2,0x5e05ed0d,0x69be5fbe,0x7eb6ae6a,0x59c25fc2,0x5e555546,0xffc27ec2,0x7e00ffff,0xfc00c2,0x5e5a6a00,0xffc27fc2,0x7e00ffff,0xfc00c2,0x7ed5d500,0x9ac67fbe,0x5e5a5656,0x56c27ec2,0x5e56a656,0xd5c27fc6,0x7ed6d6d6,0xd5c25fbe,0x7e5514d5,0xffc67fbe,0x7e00ffff,0xfc00c2,0x7e574300,0xffbe7fc2,0x7e00ffff,0xfc00c2,0x7ea5a900,0x5fc27fc2,0x7f070507,0x4bc67ec2,0x7eafaf9f,0xd5c27fc2,0x7ec555d6,0xedbe7fc2,0x7eaaaafa,0x56c27fbe,0x5e559556,0x55c67ec2,0x5f1d555d,0x65c25fc6,0x5e6e6a6a,0x6fc25fbe,0x7e6b6e6f,0x57c27fbe,0x5f555555,0xaac67ec2,0x7eaaa9aa,0x5ac65fc2,0x7e011515,0x1c65fc2,0x5e060101,
0x5bc65fc2,0x7e4b4b5b,0x4bc67fc2,0x5eab5b5b,0x55c67fc2,0x5f555555,0xa5c29fbe,0x9ea5a5a5,0xabc25fbe,0x5ebfbfaf,0xffc27fbe,0x7ea868ff,0x56c25fc2,0x5e5a5616,0x55c29fbe,0x5f3111fd,0xc0be5fbe,0xc0c0c0,0xc0c67e80,0xc0c0c0,0x4fc65f80,0x7e6f5f5f,0x6fbe5fbe,0x7e6f6f6f,0xc0c27fba,0xc0c0c0,0xc0ca5e80,0xc0c0c0,0x6fca5f80,0x5eafafaf,0x6fbe7fba,0x5e2f2f6f,0x55be5fba,0x7e56aa56,0xa9be5ec2,0x5ea99599,0x55be7fbe,0x5e965655,0xa9c27fc2,0x5eaeaaaa,0xa9c25fbe,0x5e454545,0x54be5ebe,0x5e946455,0xe9be3fba,0x5e9aa995,0x99be5fc2,0x1eaeaaa9,0xc0be3fbe,0xc0c0c0,0xc0ce3f80,0xc0c0c0,0x1fcdff80,0x3f1f1f1f,0x1fbe3fba,0x1f1f1f5f,0xc0be3fb6,0xc0c0c0,0xc0d1df80,0xc0c0c0,0x1fcddf80,0xff1f1f1f,0x2fbe1fb5,0xfe2f2f2f,
0x54bdffb5,0x3e549494,0x54be1fb6,0x1e505454,0xaab9ffb6,0x1eaaaa92,0xaaba1fbe,0x1ea5a9a9,0x50b9dfba,0x1e54a454,0x50b5deb6,0xdf505050,0x55b5feb1,0xdff5d555,0xa9b5dfb5,0xbeaa69aa,0xaab5bfb1,0x9eaaaaaa,0xeac63fc2,0x5eeaeefe,0x46c25fc2,0x7e6aba5a,0x6fc25fc2,0x3eff6a6f,0xd5c25fbe,0x3f414145,0x95c61fc2,0x1eaaaa9a,0x7fc21fbe,0x3eaaaeaf,0x55be3fbe,0xdf555555,0xadc65fb9,0x7eadfdad,0xa8c25fbe,0x5e9c68a8,0xa6c23fbe,0x5e6aaaaa,0x6abe5fba,0x3ea65556,0x9cbe5fba,0x3eac9c9c,0xa1c23fbe,0xfef0faf5,0x65bdffb9,0x3e9aaeda,0x1aba3fba,0xfe5b165a,0xbebe1fb9,0xdebffffe,0xbebdffc1,0xdea6aaaa,0x1ab9dfbd,0xfe555490,0x95b9bfbd,0xbea5a5a5,0x55b9dfbd,0xbf555555,0x55b9beb5,0xbf555555,0xa5b9beb5,0xbea5a5a5,0xeab9bebd,0x9ea9eaea,
0xe4b99fb9,0xde0d0e0e,0xeb9ffbd,0xbe2a2a0a,0x55b5bfbd,0xdf505054,0x50b9dfb9,0xbf305050,0x2ab9bfb9,0xbe3f3f3f,0x3fb59fbd,0x9e3f3f3f,0x10b59fbd,0x9f505454,0xa0b9bfb9,0xbea5e5a4,0xffb99fb9,0x7e00ffff,0xfc00c2,0x7ee9aa00,0xffc27fc2,0x7e00ffff,0xfc00be,0x7e93aa00,0x96be7fbe,0x7e965595,0xdac69ebe,0x7eae26ef,0x51be7fc2,0x7f515551,0xa2ba7fbe,0x7e5b5a5b,0xffbe7fba,0x7e00ffff,0xfc00ba,0x7eaaaa00,0xffba7fba,0x7f00ffff,0xfc00b6,0x5e2a2a00,0xaab67fba,0x7e96aa95,0x9ab67fba,0x7e49695a,0x2fb67fb6,0x7e666a2a,0xaab65fb6,0x5e955596,0xd5b27eb6,0x7f555545,0x9ac27ebe,0x7ee6aaaa,0xabbe7fbe,0x7eea2ea7,0x5aba7fba,0x7e5a5a5a,0x55be7fb6,0x7e545054,0xa5be5ebe,0x7eaaa9a5,0x57be5fba,0x5f5f5557,0xafba7fb6,0x5eff2fbf,
0x56b65fb6,0x7ea55555,0x99b27fb6,0x7ea969a5,0x55b25fb6,0x7f555555,0x55b25eb2,0x5e555555,0xfab27eae,0x5e6a95a9,0x55b27fb2,0x5f555555,0x96ae5fb2,0x5e656a65,0x55ae5eae,0x5f555555,0xffae5eae,0x5ec0ffff,0xfc00ba,0x5e000000,0xfffc00ba,0x3effffff,0xfc00c2,0x5e000000,0xfc00c2,0x5e561500,0x26ba5eb6,0x7efefeba,0xb65fb2,0x3e545500,0x54be7fbe,0x3e6aaa58,0xffba5fbe,0x1effffff,0xfc00d6,0x3e000000,0xfffc00cPropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <OutDir>$(SolutionDir)$(Platform)\$(Configuration)\</OutDir>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <PreprocessorDefinitions>BUILD_OGLES2;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>..\..\..\..\..\..\Shell;..\..\..\..\..\..\Shell\API\KEGL;..\..\..\..\..\..\Shell\OS\Windows;..\..\..\..\..\..\Builds\Include;</AdditionalIncludeDirectories>
      <RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
      <MultiProcessorCompilation>true</MultiProcessorCompilation>
      <MinimalRebuild>false</MinimalRebuild>
    </ClCompile>
    <Link>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalLibraryDirectories>..\..\..\..\..\..\Builds\Windows\x86_32\Lib;</AdditionalLibraryDirectories>
      <AdditionalDependencies>libEGL.lib;libGLESv2.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <PreprocessorDefinitions>BUILD_OGLES2;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>..\..\..\..\..\..\Shell;..\..\..\..\..\..\Shell\API\KEGL;..\..\..\..\..\..\Shell\OS\Windows;..\..\..\..\..\..\Builds\Include;</AdditionalIncludeDirectories>
      <RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
      <MultiProcessorCompilation>true</MultiProcessorCompilation>
      <MinimalRebuild>false</MinimalRebuild>
    </ClCompile>
    <Link>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalLibraryDirectories>..\..\..\..\..\..\Builds\Windows\x86_64\Lib;</AdditionalLibraryDirectories>
      <AdditionalDependencies>libEGL.lib;libGLESv2.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>MaxSpeed</Optimization>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <PreprocessorDefinitions>BUILD_OGLES2;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>..\..\..\..\..\..\Shell;..\..\..\..\..\..\Shell\API\KEGL;..\..\..\..\..\..\Shell\OS\Windows;..\..\..\..\..\..\Builds\Include;</AdditionalIncludeDirectories>
      <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
      <MultiProcessorCompilation>true</MultiProcessorCompilation>
      <MinimalRebuild>false</MinimalRebuild>
    </ClCompile>
    <Link>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <AdditionalLibraryDirectories>..\..\..\..\..\..\Builds\Windows\x86_32\Lib;</AdditionalLibraryDirectories>
      <AdditionalDependencies>libEGL.lib;libGLESv2.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>MaxSpeed</Optimization>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <PreprocessorDefinitions>BUILD_OGLES2;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <AdditionalIncludeDirectories>..\..\..\..\..\..\Shell;..\..\..\..\..\..\Shell\API\KEGL;..\..\..\..\..\..\Shell\OS\Windows;..\..\..\..\..\..\Builds\Include;</AdditionalIncludeDirectories>
      <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
      <MultiProcessorCompilation>true</MultiProcessorCompilation>
      <MinimalRebuild>false</MinimalRebuild>
    </ClCompile>
    <Link>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <AdditionalLibraryDirectories>..\..\..\..\..\..\Builds\Windows\x86_64\Lib;</AdditionalLibraryDirectories>
      <AdditionalDependencies>libEGL.lib;libGLESv2.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ClCompile Include="..\..\OGLES2BinaryShader.cpp" />
    <ClCompile Include="..\..\..\..\..\..\Shell\PVRShell.cpp" />
    <ClCompile Include="..\..\..\..\..\..\Shell\API\KEGL\PVRShellAPI.cpp" />
    <ClCompile Include="..\..\..\..\..\..\Shell\OS\Windows\PVRShellOS.cpp" />
  </ItemGroup>
  <ItemGroup>
    <ClInclude Include="..\..\..\..\..\..\Shell\PVRShell.h" />
    <ClInclude Include="..\..\..\..\..\..\Shell\PVRShellImpl.h" />
    <ClInclude Include="..\..\..\..\..\..\Shell\API\KEGL\PVRShellAPI.h" />
    <ClInclude Include="..\..\..\..\..\..\Shell\OS\Windows\PVRShellOS.h" />
    <ClInclude Include="..\..\..\..\..\..\Builds\Windows\Resources\resource.h" />
  </ItemGroup>
  <ItemGroup>
    <ResourceCompile Include="..\..\..\..\..\..\Builds\Windows\Resources\shared.rc" />
  </ItemGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          <?xml version="1.0" encoding="UTF-8"?>
<project name="OGLES2ChameleonMan" default="help">

    <!-- The local.properties file is created and updated by the 'android' tool.
         It contains the path to the SDK. It should *NOT* be checked into
         Version Control Systems. -->
    <property file="local.properties" />

    <!-- The ant.properties file can be created by you. It is only edited by the
         'android' tool to add properties to it.
         This is the place to change some Ant specific build properties.
         Here are some properties you may want to change/update:

         source.dir
             The name of the source directory. Default is 'src'.
         out.dir
             The name of the output directory. Default is 'bin'.

         For other overridable properties, look at the beginning of the rules
         files in the SDK, at tools/ant/build.xml

         Properties related to the SDK location or the project target should
         be updated using the 'android' tool with the 'update' action.

         This file is an integral part of the build system for your
         application and should be checked into Version Control Systems.

         -->
    <property file="ant.properties" />

    <!-- if sdk.dir was not set from one of the property file, then
         get it from the ANDROID_HOME env var.
         This must be done before we load project.properties since
         the proguard config can use sdk.dir -->
    <property environment="env" />
    <condition property="sdk.dir" value="${env.ANDROID_HOME}">
        <isset property="env.ANDROID_HOME" />
    </condition>

    <!-- The project.properties file is created and updated by the 'android'
         tool, as well as ADT.

         This contains project specific properties such as project target, and library
         dependencies. Lower level build properties are stored in ant.properties
         (or in .classpath for Eclipse projects).

         This file is an integral part of the build system for your
         application and should be checked into Version Control Systems. -->
    <loadproperties srcFile="project.properties" />

    <!-- quick check on sdk.dir -->
    <fail
            message="sdk.dir is missing. Make sure to generate local.properties using 'android update project' or to inject it through the ANDROID_HOME environment variable."
            unless="sdk.dir"
    />

    <!--
        Import per project custom build rules if present at the root of the project.
        This is the place to put custom intermediary targets such as:
            -pre-build
            -pre-compile
            -post-compile (This is typically used for code obfuscation.
                           Compiled code location: ${out.classes.absolute.dir}
                           If this is not done in place, override ${out.dex.input.absolute.dir})
            -post-package
            -post-build
            -pre-clean
    -->
    <import file="custom_rules.xml" optional="true" />

    <!-- Import the actual build file.

         To customize existing targets, there are two options:
         - Customize only one target:
             - copy/paste the target into this file, *before* the
               <import> task.
             - customize it to your needs.
         - Customize the whole content of build.xml
             - copy/paste the content of the rules files (minus the top node)
               into this file, replacing the <import> task.
             - customize to your needs.

         ***********************
         ****** IMPORTANT ******
         *******************