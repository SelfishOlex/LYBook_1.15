
#include "MultiplayerCharacter_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "MultiplayerCharacterSystemComponent.h"

#include <IGem.h>

namespace MultiplayerCharacter
{
    class MultiplayerCharacterModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(MultiplayerCharacterModule, "{CE435ED7-5CA7-474E-87BA-86B183DA94C2}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(MultiplayerCharacterModule, AZ::SystemAllocator, 0);

        MultiplayerCharacterModule()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MultiplayerCharacterSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MultiplayerCharacterSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(MultiplayerCharacter_e99a702176e54d1ebcddb43fc8b15139, MultiplayerCharacter::MultiplayerCharacterModule)
