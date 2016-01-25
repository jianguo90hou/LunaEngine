<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.powervr.OGLES3BinaryShader"
        android:versionCode="1"
        android:versionName="1.0">
    <uses-sdk android:minSdkVersion="18"/>
    <application
            android:icon="@drawable/ic_launcher_icon"
            android:label="@string/app_name" >
        <activity android:name="OGLES3BinaryShader"
                android:theme="@android:style/Theme.NoTitleBar.Fullscreen"
            	android:launchMode="singleTask"
            	android:configChanges="orientation|keyboardHidden"
            	android:screenOrientation="landscape"
            	android:clearTaskOnLaunch="true">
            <meta-data android:name="android.app.lib_name"
                    android:value="OGLES3BinaryShader" />
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>
    <uses-feature android:glEsVersion="0x00030000"/>
    <!-- 
        The INTERNET permission is included to allow PVRTrace and PVRScope to use 
        their renderstate override/remote capabilities with this application 
    -->
    <uses-permission android:name="android.permission.INTERNET"/>
    <!-- 
        The WRITE_EXTERNAL_STORAGE permission is included so PVRTrace 
        can write trace files to external storage when recording this application
    --> 
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE"/>
</manifest>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     