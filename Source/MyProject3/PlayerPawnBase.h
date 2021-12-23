// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"

class UCameraComponent;
class ASnakeBase;
class AFood;
class ADebuf;
class ABuff;
UCLASS()
class MYPROJECT3_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)
	AFood* Food;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodActor;

	UPROPERTY(BlueprintReadWrite)
	ADebuf* Debuf;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADebuf> DebufActor;

	UPROPERTY(BlueprintReadWrite)
	ABuff* Buff;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABuff> BuffActor;

	UPROPERTY(BlueprintReadWrite)
		UCameraComponent* PawnCamera;

	UPROPERTY(BlueprintReadWrite)
		ASnakeBase* SnakeActor;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASnakeBase> SnakeActorClass;

	
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "SnakePawn")

	void CreateSnakeActor();

	UFUNCTION()
		void HandlePlayerVerticalInput(float value);

	UFUNCTION()
		void HandlePlayerHorizontalInput(float value);
	UFUNCTION(BlueprintCallable, Category = "SnakePawn")
	void SpawnFood();

	void SpawnDebuf();

	void SpawnBuff();

	float BuferTime = 0;
	float BuferTimeBuff = 0;
	float DelayBuff = 7.f;
	float DelayDebuf = 8.f;

	int32 GameMode = 0;

	UFUNCTION(BlueprintCallable, Category = "SnakePawn")
	int32 GetGameMode() const {return GameMode;}

	UFUNCTION(BlueprintCallable, Category = "SnakePawn")
	int32 GetScore();
};