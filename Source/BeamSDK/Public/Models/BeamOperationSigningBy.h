#pragma once

#include "BeamOperationSigningBy.generated.h"

UENUM()
enum class EBeamOperationSigningBy : uint8
{
	/// Will use Session if there is one, otherwise fallback to opening Browser
	Auto,

	/// Will always open Browser to sign an operation
	Browser,

	/// Will always try to use local Session, fail if there is no valid Sessions
	Session
};
