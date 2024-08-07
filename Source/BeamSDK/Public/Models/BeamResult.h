#pragma once

#include "BeamApiError.h"

#include "BeamResult.generated.h"


UENUM()
enum class EBeamResultType : uint8
{
	Pending,
	Success,
	Error
};


template<typename TStatusEnum>
struct TBeamResult
{
public:
	/// Overall result status
	UPROPERTY()
	EBeamResultType Status;

	/// Summarized Error message
	UPROPERTY()
	FString Error;

	/// Detailed Error model from the Beam API. Optional.
	UPROPERTY()
	FBeamApiError BeamApiError;

	/// Actual result object
	UPROPERTY()
	TStatusEnum Result;

public:
	TBeamResult()
	{
	}

	TBeamResult(TStatusEnum result)
	{
		Status = EBeamResultType::Success;
		Result = result;
	}

	TBeamResult(EBeamResultType status, FString error)
	{
		Status = status;
		Error = error;
	}

#if 0 // Disabled - No ApiException

	TBeamResult(ApiException e, FString message)
	{
		Status = EBeamResultType::Error;
		Error = message;

		HandleApiException(e);
	}

	TBeamResult(ApiException e)
	{
		Status = EBeamResultType::Error;
		Error = e.Message;

		HandleApiException(e);
	}

private:
	// TODO: Convert remainng C# to C++ if needed.
	void HandleApiException(ApiException e)
	{
		if (e.ErrorContent is FString)
		{
			var text = e.ErrorContent as FString;
			if (!FString.IsNullOrEmpty(text))
			{
				var deserializedError = JsonConvert.DeserializeObject<BeamApiError>(text);
				BeamApiError = deserializedError;
			}
		}
	}
#endif // Disabled - No ApiException
};
