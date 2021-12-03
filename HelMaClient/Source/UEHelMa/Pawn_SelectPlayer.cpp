// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_SelectPlayer.h"
#include "SelectAnim.h"

// Sets default values
APawn_SelectPlayer::APawn_SelectPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	Body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Body);

	Mesh->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void APawn_SelectPlayer::BeginPlay()
{
	Super::BeginPlay();

	Anim = Cast<USelectAnim>(Mesh->GetAnimInstance());
	
}

// Called every frame
void APawn_SelectPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawn_SelectPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

