// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff.h"
#include "SnakeBase.h"
// Sets default values
ABuff::ABuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuff::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BuferTime += DeltaTime;
	if (BuferTime > LifeTime)
	{
		Destroy(true, true);
	}
}

void ABuff::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake))
	{
		float NewSpeed = Snake->GetActorTickInterval() - 0.1f;
		if (Snake->GetActorTickInterval() > 0.2)
		{
			Snake->SetActorTickInterval(NewSpeed);
		}
	}
	Destroy();
}

