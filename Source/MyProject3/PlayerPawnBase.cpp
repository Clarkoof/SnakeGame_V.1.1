// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "Components/InputComponent.h"
#include "math.h"
#include "Food.h"
#include "Buff.h"
#include "Debuf.h"


// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;

	

}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorRotation(FRotator(-90, 0, 0));
	
	
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	BuferTime += DeltaTime;
	if (BuferTime > DelayDebuf)
	{
		SpawnDebuf();
		BuferTime = 0;
	}
	BuferTimeBuff += DeltaTime;
	if (BuferTimeBuff > DelayBuff)
	{
		SpawnBuff();
		BuferTimeBuff = 0;
	}
	
}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontalInput);
}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
	GameMode = 1;
}

void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection!=EMovementDirection::DOWN)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::UP;
		}
		else if (value < 0 && SnakeActor->LastMoveDirection!=EMovementDirection::UP)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::DOWN;
		}
	}
}

void APlayerPawnBase::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection!= EMovementDirection::LEFT)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
		}
		else if (value < 0 && SnakeActor->LastMoveDirection!= EMovementDirection::RIGHT)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
		}
	}
}

void APlayerPawnBase::SpawnFood()
{
	float MinX = -610.f;
	float MaxX = 610.f;
	float MinY = -1480.f;
	float MaxY = 1480.f;
	float SpawnZ = 60.f;
	FRotator Rotation = FRotator(0, 0, 0);
	float SpawnX = FMath::FRandRange(MinX, MaxX);
	float SpawnY = FMath::FRandRange(MinY, MaxY);
	FVector SpawnVector = FVector(SpawnX, SpawnY, SpawnZ);

	if (SnakeActor)
	{
		if (GetWorld())
		{
			{
				GetWorld()->SpawnActor<AFood>(FoodActor, SpawnVector, Rotation);
				GameMode = 1;
			}
		}
	}


}

void APlayerPawnBase::SpawnDebuf()
{
	float MinX = -610.f;
	float MaxX = 610.f;
	float MinY = -1480.f;
	float MaxY = 1480.f;
	float SpawnZ = 60.f;
	FRotator Rotation = FRotator(0, 0, 0);
	float SpawnX = FMath::FRandRange(MinX, MaxX);
	float SpawnY = FMath::FRandRange(MinY, MaxY);
	FVector SpawnVector = FVector(SpawnX, SpawnY, SpawnZ);

	if (SnakeActor)
	{
		if (GetWorld())
		{
			GetWorld()->SpawnActor<ADebuf>(DebufActor, SpawnVector, Rotation);
		}
	}
}

void APlayerPawnBase::SpawnBuff()
{
	float MinX = -610.f;
	float MaxX = 610.f;
	float MinY = -1480.f;
	float MaxY = 1480.f;
	float SpawnZ = 60.f;
	FRotator Rotation = FRotator(0, 0, 0);
	float SpawnX = FMath::FRandRange(MinX, MaxX);
	float SpawnY = FMath::FRandRange(MinY, MaxY);
	FVector SpawnVector = FVector(SpawnX, SpawnY, SpawnZ);

	if (SnakeActor)
	{
		if (GetWorld())
		{
			GetWorld()->SpawnActor<ABuff>(BuffActor, SpawnVector, Rotation);

			
		}
	}
}

int32 APlayerPawnBase::GetScore()
{
	if (SnakeActor)
	{
		return SnakeActor->Score;
	}
	return 0;
}

