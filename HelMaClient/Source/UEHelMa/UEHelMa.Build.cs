// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class UEHelMa : ModuleRules
{
	public UEHelMa(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//����ʿ��� ����� �༮���� �ǹ�,���߿� inventory���ϰԵǸ� �����߰���,ai�� 
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		//�ܺ�������Ʈ���� ������� ���ϴ� �༮���� ���⿡ �ִ´�
		PrivateDependencyModuleNames.AddRange(new string[] { "Sockets", "Networking", "Slate", "SlateCore" });

		//�� ��⿡ ���� ���� �����Ϸ� ����
		PublicDefinitions.Add("UNREALDEFINE=1");

		//�𸮾� ���̺귯��� ����� �������ִ� c#���α׷���
		//�ڽ��� �ڵ带�ļ� ���̺귯���� ����� �߰��ϴ¹���Դϴ�.
		//�̰� �ϱ����ؼ� �ϴ� �𸮾��� �ֿܼ��� ������ ����װ� �ƴ� �������������� �ν��մϴ�
		//�׷��� ������ �������尡 ���� �ֿܼ��� �Ǵ°� ���� �մϴ� 
		//����� �̺κ��� �ڵ��ϼ��� �ȵ˴ϴ�
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
