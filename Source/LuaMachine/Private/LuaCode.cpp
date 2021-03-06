// Copyright 2018 - Roberto De Ioris

#include "LuaCode.h"
#include "LuaMachine.h"

ULuaCode::ULuaCode()
{
	bCookAsBytecode = true;
	bCooked = false;
}

void ULuaCode::Serialize(FArchive& Ar)
{
	if (Ar.IsCooking() && bCookAsBytecode && !Code.IsEmpty())
	{
		bCooked = true;
		FString ErrorString;
		ByteCode = ULuaState::ToByteCode(Code.ToString(), GetPathName(), ErrorString);
		if (!ErrorString.IsEmpty())
		{
			UE_LOG(LogLuaMachine, Error, TEXT("Unable to generate bytecode: %s"), *ErrorString);
		}
		Code = FText::GetEmpty();
	}

	UObject::Serialize(Ar);

	Ar << bCooked;
	Ar << Code;
	Ar << bCookAsBytecode;
	Ar << ByteCode;
}

void ULuaCode::PreSave(const ITargetPlatform* TargetPlatform)
{
	Super::PreSave(TargetPlatform);

	for (ULuaState* LuaState : FLuaMachineModule::Get().GetRegisteredLuaStates())
	{
		if (LuaState->LuaCodeAsset == this)
		{
			FLuaMachineModule::Get().UnregisterLuaState(LuaState);
		}
	}
}

