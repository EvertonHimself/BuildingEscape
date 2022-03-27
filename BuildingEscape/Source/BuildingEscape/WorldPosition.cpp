// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	int32 Number = 9;
	FString Log = TEXT("Hello, this is an FSTring.");
	// FSTring: the type of the thing it is pointing to.
	// FSTring* PrtLog is a pointer to something that is a FString.
	// FSTring* PrtLog = &Log, in THIS CASE, the &Log means "the address of" were the Log variable
	// is stored in memory.
	FString* PtrLog = &Log;
	//Log.Len();
	
	// We must use () because the . has precedence over the *, so we use () to force it to run first.
	//(*PtrLog).Len(); this shit doesn't work for some reason.
	// Alternatively, we can (access members) write like below:
	//PtrLog -> Len(); this shit doesn't work for some reason.
	// Obs: use the . when accessing directly.

	// The * in this instance is an overloading operator.
	// The * is not a pointer not reference in this case, it is accessing the content in the text var inside the FString object.
	// which is in itself a pointer, a TCHAR*.
	// ** = dereference AND using the overloading operator.
	UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);

	/* UE_LOG(LogTemp, Warning, TEXT("This is a warning!"));
	UE_LOG(LogTemp, Error, TEXT("This is an error."));
	UE_LOG(LogTemp, Display, TEXT("This is just a log message.")); */
	
	//FString ObjectName = GetOwner() -> GetName();
	UE_LOG(LogTemp, Warning, TEXT("Object name is: %"), *GetOwner() -> GetName());

	FString ObjectPosition = GetOwner() -> GetActorLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("Position in world is: %"), *ObjectPosition);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

