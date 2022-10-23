// Copyright Everton 2022

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::FindPhysicsHandle() 
{
	// Check for the physics handle component.
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		// Physics is found.
		UE_LOG(LogTemp, Error, TEXT("No physics handle found on %s!"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() 
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));
	// Try and reach any actors with physics body collision channel set.

	// If we hit something then attach the physics handle.
	//if (HitResult.GetActor())
	if (ActorHit)
	{
		if (!PhysicsHandle)
		{
			return;
		}
		// Attach physics handle.
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			GetThePlayersReach()
		);
	}
}

void UGrabber::Release()
{
	// Remove/release the physics handle.
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// If the physics handle is attach
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent) 
	{
		// Move the object we are holding.
		PhysicsHandle->SetTargetLocation(GetThePlayersReach());
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;
	// Ray-cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPosition(),
		GetThePlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return Hit;
}

FVector UGrabber::GetPlayersWorldPosition() const 
{
	// Get players viewpoint.
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Draw a line from player showing the reach.
	return PlayerViewPointLocation;
}

FVector UGrabber::GetThePlayersReach() const 
{
	// Get players viewpoint.
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Draw a line from player showing the reach.
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
