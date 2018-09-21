
#include "MyProject_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "MyProjectSystemComponent.h"

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
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyProjectSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(MyProject_737482b19b5f426da338061a064a8ee0, MyProject::MyProjectModule)
