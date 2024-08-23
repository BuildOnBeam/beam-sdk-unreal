#include "BeamApiError.h"

DEFINE_LOG_CATEGORY_STATIC(LogBeamApiError, Log, All);

bool FBeamApiError::FromJson(const FString& InJsonString, FBeamApiError& OutBeamApiError)
{
	if (FBeamUtils::JsonToStruct(InJsonString, OutBeamApiError))
	{
		return true;
	}
	return false;
}


bool FBeamApiError::FromJson(const FString& InJsonString)
{
	return FromJson(InJsonString, *this);
}
