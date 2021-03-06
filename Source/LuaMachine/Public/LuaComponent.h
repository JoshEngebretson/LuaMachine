// Copyright 2018 - Roberto De Ioris

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LuaState.h"
#include "LuaValue.h"
#include "LuaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLuaComponentError, FString, Message);


UCLASS( ClassGroup=(Scripting), meta=(BlueprintSpawnableComponent) )
class LUAMACHINE_API ULuaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULuaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ULuaState> LuaState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FLuaValue> Table;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FLuaValue> Metatable;

	UPROPERTY(EditAnywhere)
	bool bLazy;

	UPROPERTY(EditAnywhere)
	bool bLogError;

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Args"))
	FLuaValue LuaCallFunction(FString Name, TArray<FLuaValue> Args, bool bGlobal);

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Args"))
	FLuaValue LuaCallValue(FLuaValue Value, TArray<FLuaValue> Args);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FLuaValue LuaGetField(FString Name);

	UFUNCTION(BlueprintCallable)
	void LuaSetField(FString Name, FLuaValue Value);

	UPROPERTY(BlueprintAssignable, Category = "Lua", meta = (DisplayName = "On Lua Error"))
	FLuaComponentError OnLuaError;

	void SetupMetatable();
	
};
