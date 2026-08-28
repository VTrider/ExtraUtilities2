#include "BZCC.h"
#include "ExtraUtils.h"

#include <safetyhook.hpp>

#include <memory>

namespace exu2
{
	using namespace BZCC;

	BuildEventCallback_t buildEventCallback = nullptr;

	SafetyHookInline armoryQueueHook;
	SafetyHookInline constructorQueueHook;
	SafetyHookInline factoryQueueHook;

	SafetyHookInline armoryCancelHook;
	SafetyHookInline constructorCancelHook;
	SafetyHookInline factoryCancelHook;

	SafetyHookInline armoryBuildHook;
	SafetyHookInline constructorBuildHook;
	SafetyHookInline factoryBuildHook;

	bool __fastcall ArmoryQueueHook(GameObject* self, [[maybe_unused]] int edx)
	{
		if (buildEventCallback)
			buildEventCallback(ProducerType::ARMORY, self->handle, BuildEventType::QUEUE, GetBuildClass(self->handle), 0);
		return armoryQueueHook.thiscall<bool>(self);
	}

	// No idea what the magic 3rd GameObject* does, untested probably best not to touch it
	bool __fastcall ConstructorQueueHook(GameObject* self, [[maybe_unused]] int edx, GameObjectClass* buildClass, GameObject* magic)
	{
		if (buildEventCallback)
			buildEventCallback(ProducerType::CONSTRUCTOR, self->handle, BuildEventType::QUEUE, buildClass->odf, 0);
		return constructorQueueHook.thiscall<bool>(self, buildClass, magic);
	}

	// This is janky azz fk, you can't assign a loose function as __thiscall so you need to use __fastcall with a dummy second parameter
	// in edx to get the real second parameter that's on the stack
	bool __fastcall FactoryQueueHook(Factory* self, [[maybe_unused]] int edx, GameObjectClass* buildClass)
	{
		if (buildEventCallback)
			buildEventCallback(ProducerType::FACTORY, self->handle, BuildEventType::QUEUE, buildClass->odf, 0);
		return factoryQueueHook.thiscall<bool>(self, buildClass);
	}

	bool __fastcall ArmoryCancelHook(GameObject* self, [[maybe_unused]] int edx)
	{
		if (buildEventCallback)
			buildEventCallback(ProducerType::ARMORY, self->handle, BuildEventType::CANCEL, GetBuildClass(self->handle), 0);
		return armoryCancelHook.thiscall<bool>(self);
	}

	void __fastcall ConstructorCancelHook(RigBuild* self, [[maybe_unused]] int edx)
	{
		if (buildEventCallback)
			buildEventCallback(ProducerType::CONSTRUCTOR, self->constructor->handle, BuildEventType::CANCEL, self->buildClass->odf, 0);
		return constructorCancelHook.thiscall<void>(self);
	}

	bool __fastcall FactoryCancelHook(Factory* self, [[maybe_unused]] int edx)
	{
		if (buildEventCallback)
		{
			for (int i = 0; i < 10; i++)
			{
				const char* item = GetQueuedItem(self->handle, i);
				if (!item)
					continue;
				std::string odfString = item;
				// This is fking stupid why does that function return the odf with :1 appended instead of .odf?
				odfString = odfString.substr(0, odfString.find(':'));
				odfString += ".odf";

				buildEventCallback(ProducerType::FACTORY, self->handle, BuildEventType::CANCEL, odfString.c_str(), 0);
			}
		}
		return factoryCancelHook.thiscall<bool>(self);
	}

	void DLLAPI SetBuildEventCallback(BuildEventCallback_t callback)
	{
		buildEventCallback = callback;

		// Note that we're actually using StartBuild because this has the expected behavior of triggering when the player
		// confirms a build with space bar, while QueueBuild is fired off every time the player selects a weapon in the armory menu even if they don't confirm it
		if (!armoryQueueHook.target())
			armoryQueueHook = safetyhook::create_inline(BZCC::moduleBase + Offsets::Armory_StartBuild, ArmoryQueueHook);

		if (!constructorQueueHook.target())
			constructorQueueHook = safetyhook::create_inline(BZCC::moduleBase + Offsets::Constructor_QueueBuild, ConstructorQueueHook);

		if (!factoryQueueHook.target())
			factoryQueueHook = safetyhook::create_inline(BZCC::moduleBase + Offsets::Factory_QueueBuild, FactoryQueueHook);

		if (!armoryCancelHook.target())
			armoryCancelHook = safetyhook::create_inline(BZCC::moduleBase + Offsets::Armory_CancelBuild, ArmoryCancelHook);

		if (!constructorCancelHook.target())
			constructorCancelHook = safetyhook::create_inline(BZCC::moduleBase + Offsets::Constructor_CancelBuild, ConstructorCancelHook);

		if (!factoryCancelHook.target())
			factoryCancelHook = safetyhook::create_inline(BZCC::moduleBase + Offsets::Factory_CancelBuild, FactoryCancelHook);
	}
}