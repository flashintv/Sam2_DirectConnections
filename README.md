# Sam2_DirectConnections
This project was made for restoring server connection by using an IP address and port within Serious Sam 2 as the latest Steam update breaks it, because of this project I have learnt out a ton more about the inner workings of how client<->server communication works in Serious Engine 2.

## Notes about Serious Sam 2 and why this project exists:
Serious Sam 2 in itself supported direct IP connections but after the latest update it switched over to P2P - although using a very old version of Steamworks v125.

The code is held together with hopes and prayers, as there are some parts of the code that still try to support IP connections, but will fail because everything else doesn't or it never calls it. I believe someone tried to port and or fix the IP connections but then gave up halfway through making of the update.

The Specific Server tab can work with SteamID to directly connect to servers because of how the code works, but it doesn't - neither does actual IP connections because they don't get resolved. If you try to connect to a *dedicated server* (based on the SteamID or if you're connecting through an IP address) it sets a flag `int net_bSteamGameserver` to `1`, which tells the `Engine.dll` to not try to get the Lobby owner as client-hosted games use the Lobby system primarily for most forms of communication/information.

Issue being that the flag does absolutely nothing, because there is no instance where the flag can be set to `1` and the `net_idSteamServerLobby` is set to anything but zero. All connection attempts even if done via IP - lead to the `CSteamSocket::Connect( CSteamID const& )` which as the arguments suggest only take a CSteamID. There is a `CSteamSocket::Connect( CIPAddress const& )` but it never gets called, which tries to use `ISteamNetworking::CreateConnectionSocket` and then get the CSteamID from the socket but it will never succeed because the game servers have their listen sockets created with IP and port set to zero during a call to `ISteamNetworking::CreateListenSocket` within `CSteamSocket::Listen( int, ulong ip = 0, long port = 0 )` by `CCommunicationInterface::InitializeNetworkInteface`.

There's also the fact that the dedicated server CANNOT work under normal circumstances as I believe the recent update changed some code within Netricsa resulting in an access violation if a client ever connects to the server, because the player profile is NEVER set under the normal circumstances on the dedicated server and if it is then the server will crash because it's not made to handle them. The access violation happens in a call tree within `CNetricsaHudElement::Initialize` where one of the functions being called in it is trying to get a player profile but not safety checking it (reminder: player profiles don't exist on dedicated servers!), causing the game to try to read an invalid pointer and thus crashes. Both `Sam2Game.dll` and `InSamnity2Game.dll` suffer from this issue.

The Serious Sam 2 networking code in general seems and most likely is very unsafe, as random people/servers can just send a connect to a client and the client without authentication that it even needs it - accepts it and processes the messages.

## How to use this:
- Download the binaries from the Releases tab and then:
  - If you plan on hosting a dedicated server: extract `DedicatedServer_DirectConnections.exe` into the `Serious Sam 2/Bin` folder and launch it with your standard server configuration.
  - If you plan on connecting to a dedicated server: extract `Sam2_DirectConnections.exe` into the `Serious Sam 2/Bin` folder and launch it.

The binaries will automatically extract and inject `DirectConnections.dll` and detour appropriate functions.
