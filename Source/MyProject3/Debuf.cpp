// Fill out your copyright notice in the Description page of Project Settings.


#include "Debuf.h"
#include "SnakeBase.h"
// Sets default values
ADebuf::ADebuf()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ADebuf::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebuf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BuferTime += DeltaTime;
	if (BuferTime > LifeTime)
	{
		Destroy(true, true);
	}
}

void ADebuf::Interact(AActor* Interactor, bool bIsHead)
{
	
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake))
	{
		float NewSpeed = Snake->GetActorTickInterval() + 0.1f;
		
		Snake->SetActorTickInterval(NewSpeed);
	}

	Destroy();
}




