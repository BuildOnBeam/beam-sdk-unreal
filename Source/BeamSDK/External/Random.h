#pragma once

#include "Misc/Paths.h" // For Unreal Engine utilities
#include "HAL/Platform.h" // Platform-specific macros
#include "Logging/LogMacros.h" // For UE_LOG


#if PLATFORM_WINDOWS

#include <bcrypt.h> // For BCryptGenRandom (Windows)
#pragma comment(lib, "bcrypt.lib")

#elif PLATFORM_LINUX || PLATFORM_MAC

#include <fcntl.h>  // For open()
#include <unistd.h> // For read() and close()

#endif


/* Returns 1 on success, and 0 on failure. */
static int fill_random(unsigned char data[], size_t size)
{
#if PLATFORM_WINDOWS
    // Use Windows CryptoAPI
    if (!BCryptGenRandom(nullptr, data, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG))
    {
        UE_LOG(LogBeamClient, Error, TEXT("Failed to generate random bytes on Windows."));
        return 0;
    }

    return 1;
#elif PLATFORM_LINUX || PLATFORM_MAC
    // Use /dev/urandom
    int FD = open("/dev/urandom", O_RDONLY);
    if (FD < 0)
    {
        UE_LOG(LogBeamClient, Error, TEXT("Failed to open /dev/urandom."));
        return 0;
    }

    read(FD, data, size);
    close(FD);
    return 1;
    
#else
    return 0;
#endif
}