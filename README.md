# Beam Plugin for Unreal Engine

## Setup
1. When in the /.openapi-generator/ folder, run `npm run generate`
2. This will generate the cpp files in the /Source/PlayerClient/ folder. 
3. Additionally, it will run `generate-unreal-header.mjs` if you have node.js installed which will create a header file at /BeamSdk/Public/BeamPlayerClientAPI.h

## Usage

An example implementation compatible with versions of Unreal newer than 5.2.1 is provided at:
[beam-sdk-unreal-example](https://github.com/BuildOnBeam/beam-sdk-unreal-example)

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


#### Overriding LaunchURL method
Beam sometimes has to open a browser in order for the user to sign in to a Beam account and sign transactions/sessions. By default we call `FPlatformProcess::LaunchURL()`.

In some cases you might want to implement your own way of opening URLs, f.e. using a built-in WebView. To do so, you need to override `FString UBeamClient::LaunchURL(const FString& Url)` in your implementation.

#### Selecting AuthProvider
All main BeamClient methods accept an optional argument called `authProvider`. By passing a provider value other than `Any`, you force the User to sign into Beam Identity using that provider. This allows you to skip the initial screen with Social Provider login selection, at the cost of taking the choice away from the User. This can be useful if you want to present Social Providers to choose from within your UI. Please keep in mind that Social Providers we support might change in the future and might then require changes in your UI.
