﻿using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using UnityEditorInternal;
using System.IO;
using GameData;
using Newtonsoft.Json;

public class AnimationTool : EditorWindow
{
    static Dictionary<string, Dictionary<string, Dictionary<float, GameData.AniEventData>>> AnimAtkFrames = new Dictionary<string, Dictionary<string, Dictionary<float, AniEventData>>>();
    static Dictionary<string, Dictionary<string, GameData.AnimationConfigData>> AnimDurations = new Dictionary<string, Dictionary<string, AnimationConfigData>>();

    [MenuItem("uCool/Animation/Export Config from FBX")]
    public static void ExportFBXAnimationConfig()
    {
        AnimAtkFrames.Clear();
        AnimDurations.Clear();

        if (!EditorUtility.DisplayDialog("Export animation config",
            "This operation will overwrite AnimationConfig.txt and AniEvent.txt!\n\nAre you sure you want to continue?", "Yes", "Do Not Overwrite"))
        {
            return;
        }

        string[] folders = Directory.GetDirectories("Assets/Units", "*", SearchOption.TopDirectoryOnly);
        int i = 0, total = folders.Length;
        foreach (string folder in folders)
        {
            EditorUtility.DisplayProgressBar("Process Animation", "process " + folder, i / total);
            //枚举每个目录下的动画资源
            ProcessFolder(folder);
        }
        JsonSerializerSettings setting = new JsonSerializerSettings();
        setting.Formatting = Formatting.Indented;
        setting.NullValueHandling = NullValueHandling.Ignore;
        string dura = JsonConvert.SerializeObject(AnimDurations, Formatting.Indented, setting);
        string atkframe = JsonConvert.SerializeObject(AnimAtkFrames, Formatting.Indented, setting);
        File.WriteAllText("Assets/BuildOnlyAssets/Data/AnimationConfig.txt", dura);
        File.WriteAllText("Assets/BuildOnlyAssets/Data/AniEvent.txt", atkframe);
        EditorUtility.ClearProgressBar();
        EditorUtility.DisplayDialog("", "Animation process completed", "OK");
    }

    static void ProcessFolder(string folder)
    {
        string name = Path.GetFileName(folder);
        AnimDurations[name] = new Dictionary<string, AnimationConfigData>();
        AnimAtkFrames[name] = new Dictionary<string, Dictionary<float, AniEventData>>();

        string[] anim_files = Directory.GetFiles("Assets/Units/" + name, "*.fbx");

        foreach (string anim_file in anim_files)
        {
            ProcessFBX(anim_file);
        }
    }

    static void ProcessFBX(string path)
    {
        string anim_name = System.IO.Path.GetFileNameWithoutExtension(path);
        Object[] objs = AssetDatabase.LoadAllAssetsAtPath(path);
        AnimDurations[anim_name] = new Dictionary<string, AnimationConfigData>();
        AnimAtkFrames[anim_name] = new Dictionary<string, Dictionary<float, AniEventData>>();
        foreach (Object o in objs)
        {
            if (o is AnimationClip)
            {
                AnimationClip clip = (AnimationClip)o;
                if (clip.name.Contains("__preview__"))
                    continue;
                ProcessClip(anim_name, clip);
            }
        }
    }

    static void ProcessClip(string anim_name, AnimationClip clip)
    {
        AnimationEvent[] events = AnimationUtility.GetAnimationEvents(clip);
        AnimationClipCurveData[] caveDatas = AnimationUtility.GetAllCurves(clip);

        string clipname = clip.name.Replace(anim_name, "");
        //生成动画周期数据
        AnimDurations[anim_name][clipname] = new AnimationConfigData();
        AnimDurations[anim_name][clipname].Role = anim_name;
        AnimDurations[anim_name][clipname].Animation = clipname;
        AnimDurations[anim_name][clipname].TotalTime = clip.length;

        //在这里获得动作的事件
        Dictionary<float, AniEventData> datas = new Dictionary<float, AniEventData>();

        foreach (AnimationEvent evt in events)
        {
            if (evt.functionNam﻿
Microsoft Visual Studio Solution File, Format Version 11.00
# Visual Studio 2010
Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "OGLES2ChameleonMan", "OGLES2ChameleonMan.vcxproj", "{9DAFEE32-19F6-4410-AA09-2B564FB86F62}"
	ProjectSection(ProjectDependencies) = postProject
		{09ABE661-9BC0-4152-A820-1FB0522CAC01} = {09ABE661-9BC0-4152-A820-1FB0522CAC01}
	EndProjectSection
EndProject
Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "OGLES2Tools", "..\..\..\..\..\..\Tools\OGLES2\Build\WindowsVC2010\OGLES2Tools.vcxproj", "{09ABE661-9BC0-4152-A820-1FB0522CAC01}"
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|Win32 = Debug|Win32
		Debug|x64 = Debug|x64
		Release|Win32 = Release|Win32
		Release|x64 = Release|x64
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{9DAFEE32-19F6-4410-AA09-2B564FB86F62}.Debug|Win32.ActiveCfg = Debug|Win32
		{9DAFEE32-19F6-4410-AA09-2B564FB86F62}.Debug|Win32.Build.0 = Debug|Win32
		{9DAFEE32-19F6-4410-AA09-2B564FB86F62}.Debug|x64.ActiveCfg = Debug|x64
		{9DAFEE32-19F6-4410-AA09-2B564FB86F62}.Debug|x64.Build.0 = Debug|x64
		{9DAFEE32-19F6-4410-AA09-2B564FB86F62}.Release|Win32.ActiveCfg = Release|Win32
		{9DAFEE32-19F6-4410-AA09-2B564FB86F62}.Release|Win32.Build.0 = Release|Win32
		{9DAFEE32-19F6-4410-AA09-2B564FB86F62}.Release|x64.ActiveCfg = Release|x64
		{9DAFEE32-19F6-4410-AA09-2B564FB86F62}.Release|x64.Build.0 = Release|x64
		{09ABE661-9BC0-4152-A820-1FB0522CAC01}.Debug|Win32.ActiveCfg = Debug|Win32
		{09ABE661-9BC0-4152-A820-1FB0522CAC01}.Debug|Win32.Build.0 = Debug|Win32
		{09ABE661-9BC0-4152-A820-1FB0522CAC01}.Debug|x64.ActiveCfg = Debug|x64
		{09ABE661-9BC0-4152-A820-1FB0522CAC01}.Debug|x64.Build.0 = Debug|x64
		{09ABE661-9BC0-4152-A820-1FB0522CAC01}.Release|Win32.ActiveCfg = Release|Win32
		{09ABE661-9BC0-4152-A820-1FB0522CAC01}.Release|Win32.Build.0 = Release|Win32
		{09ABE661-9BC0-4152-A820-1FB0522CAC01}.Release|x64.ActiveCfg = Release|x64
		{09ABE661-9BC0-4152-A820-1FB0522CAC01}.Release|x64.Build.0 = Release|x64
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
EndGlobal
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 