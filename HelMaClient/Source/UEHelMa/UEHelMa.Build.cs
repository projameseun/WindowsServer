// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class UEHelMa : ModuleRules
{
	public UEHelMa(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//헤더쪽에서 사용할 녀석들을 의미,나중에 inventory를하게되면 여기추가됨,ai도 
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		//외부프로젝트에서 사용하지 못하는 녀석들을 저기에 넣는다
		PrivateDependencyModuleNames.AddRange(new string[] { "Sockets", "Networking", "Slate", "SlateCore" });

		//이 모듈에 대한 공용 컴파일러 정의
		PublicDefinitions.Add("UNREALDEFINE=1");

		//언리얼 라이브러라와 헤더를 지정해주는 c#프로그램에
		//자신의 코드를쳐서 라이브러리나 헤더를 추가하는방식입니다.
		//이걸 하기위해선 일단 언리얼은 콘솔에서 무조건 디버그가 아닌 릴리즈모드방식으로 인식합니다
		//그러기 때문에 릴리즈모드가 먼저 콘솔에서 되는걸 먼저 합니다 
		//참고로 이부분은 자동완성이 안됩니다
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
		//string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../JamesServer/Worskpace/JamesServerStart/"));
		//string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../ServerStart/"));
		
			string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../HelMaServer/"));
			{
				string IncludePath = ThirdPartyPath + "GameEngineBase/";
				PublicIncludePaths.Add(IncludePath);
			}


			{
				string IncludePath = ThirdPartyPath + "GameEngineNet/";
				PublicIncludePaths.Add(IncludePath);
			}


			{
				string IncludePath = ThirdPartyPath + "GameEngineObject/";
				PublicIncludePaths.Add(IncludePath);
			}


			{
				string IncludePath = ThirdPartyPath + "LogicContent/";
				PublicIncludePaths.Add(IncludePath);
			}

			//string LibraryPath = ThirdPartyPath + "Build/x64/Release";
			string LibraryPath = ThirdPartyPath + "Build/UnRelease/";

			PublicSystemLibraryPaths.Add(LibraryPath);
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "GameEngineBase.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "GameEngineNet.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "GameEngineObject.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "LogicContent.lib"));

		}

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
