#include "MultiplayerCloseAllNetworkPeers_precompiled.h"
#include <MultiplayerCloseAllNetworkPeers/ShutdownApplication.h>
#include <ISystem.h>
#include <IConsole.h>

void MultiplayerCloseAllNetworkPeers::ShutdownApplication()
{
    ISystem* system = nullptr;
    CrySystemRequestBus::BroadcastResult(system,
        &CrySystemRequestBus::Events::GetCrySystem);
    if (system)
    {
        system->GetIConsole()->ExecuteString("quit");
    }
}
