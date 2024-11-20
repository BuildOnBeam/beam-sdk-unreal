#include "SecureRandom.h"

#if PLATFORM_WINDOWS
#include <bcrypt.h> // For BCryptGenRandom (Windows)
#pragma comment(lib, "bcrypt.lib")
#elif PLATFORM_LINUX || PLATFORM_MAC
#include <fcntl.h>  // For open()
#include <unistd.h> // For read() and close()
#endif

DEFINE_LOG_CATEGORY(LogSecureRandom);

void GenerateSecureRandomBytes(uint8* Buffer, size_t Length)
{
#if PLATFORM_WINDOWS
	// Use Windows CryptoAPI
	if (!BCryptGenRandom(nullptr, Buffer, Length, BCRYPT_USE_SYSTEM_PREFERRED_RNG))
	{
		UE_LOG(LogSecureRandom, Error, TEXT("Failed to generate random bytes on Windows."));
	}
#elif PLATFORM_LINUX || PLATFORM_MAC
	// Use /dev/urandom
	int FD = open("/dev/urandom", O_RDONLY);
	if (FD < 0)
	{
		UE_LOG(LogSecureRandom, Error, TEXT("Failed to open /dev/urandom."));
	}
	else
	{
		if (read(FD, Buffer, Length) != static_cast<ssize_t>(Length))
		{
			UE_LOG(LogSecureRandom, Error, TEXT("Failed to read enough bytes from /dev/urandom."));
		}
		close(FD);
	}
#else
	// Fallback for other platforms
	UE_LOG(LogSecureRandom, Error, TEXT("Unsupported platform for secure random byte generation."));
#endif
}
