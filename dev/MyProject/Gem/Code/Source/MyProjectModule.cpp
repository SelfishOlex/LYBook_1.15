
#include "MyProject_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "MyProjectSystemComponent.h"
#include "MyComponent.h"
#include "OscillatorComponent.h"
#include "MySpawnerComponent.h"
#include "StartingMapSystemComponent.h"
#include "TransformSyncComponent.h"
#include "MyScriptHelperComponent.h"
#include "MyUIStatusComponents.h"
#include "MyScriptSystemComponent.h"
#include "ScriptCanvas/MyNodeLibrary.h"

#include <IGem.h>

namespace MyProject
{
    class MyProjectModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(MyProjectModule, "{02A57994-A41C-4670-B51C-39BCC2F7ACEE}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(MyProjectModule, AZ::SystemAllocator, 0);

        MyProjectModule()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MyProjectSystemComponent::CreateDescriptor(),
                StartingMapSystemComponent::CreateDescriptor(),
                MyComponent::CreateDescriptor(),
                OscillatorComponent::CreateDescriptor(),
                MySpawnerComponent::CreateDescriptor(),
                TransformSyncComponent::CreateDescriptor(),
                MyUIForwardComponent::CreateDescriptor(),
                MyUIBackwardComponent::CreateDescriptor(),
                MyUIStrafeLeftComponent::CreateDescriptor(),
                MyUIStrafeRightComponent::CreateDescriptor(),
                MyScriptSystemComponent::CreateDescriptor(),
                MyScriptHelperComponent::CreateDescriptor(),
            });

            auto desc = MyNodeLibrary::GetComponentDescriptors();
            m_descriptors.insert(m_descriptors.end(),
                desc.begin(), desc.end());
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyProjectSystemComponent>(),
                azrtti_typeid<StartingMapSystemComponent>(),
                azrtti_typeid<MyScriptSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(MyProject_737482b19b5f426da338061a064a8ee0, MyProject::MyProjectModule)
