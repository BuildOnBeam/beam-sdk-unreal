# Beam Plugin for Unreal Engine

## Status: `Functional, but in Active Development`

## Setup
1. When in the /.openapi-generator/ folder, run `npm run generate-on-windows` or `npm run generate`
2. This will generate the cpp files in the /Source/PlayerClient/ folder. 
3. Additionally, it will run `generate_unreal_headers.js` if you have node.js installed which will create a header file at /BeamSdk/Public/BeamPlayerClientAPI.h

## Usage

An example implementation compatible with versions of Unreal newer than 5.2.1 is provided at:
[beam-sdk-unreal-example](https://github.com/Merit-Circle/beam-sdk-unreal-example)

### Initialize a Beam Client
Initialize a BeamClient to interact with the Beam API.
```c++
BeamStorage = UBeamSaveGameStorage::LoadOrCreate();
BeamClient = NewObject<UBeamClient>(this)
    ->SetBeamApiKey(BeamApiKey) // Required
    ->SetEnvironment(EBeamEnvironment::Testnet) // Optional, defaults to testnet if not set
    ->SetDebugLogging(true) // Optional, defaults to false if not set
    ->SetStorage(BeamStorage); // Required: Defaults to an Unreal SaveGame if you don't provide your own implementation
BeamStorage->Save();
```

### Checking for an active Session
```c++
BeamClient->GetActiveSessionAsync(EntityId, ChainId)
.Next([&, Callback](const BeamOperationResult& Response) {
    // Do something with response
});

```

### Creating a Session
```c++
BeamClient->CreateSessionAsync(EntityId)
.Next([&, Callback](const BeamSessionResult& Response) {
    // Do something with response
});
```

### Revoking a Session
```c++
BeamClient->RevokeSessionAsync(EntityId, SessionAddress)
.Next([&, Callback](const BeamOperationResult& Response) {
    // Do something with response
});
```
