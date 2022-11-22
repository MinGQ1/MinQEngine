#pragma once
#include "Layer.h"
#include <vector>

enum UpdatableLayer
{
	kImguiLayer = 0,
	kUpdatableLayerCount
};

class LayerManager
{
public:
	static void RegisterUpdatableLayer(UpdatableLayer layerType, Layer* layer);
	static void UnregisterUpdatableLayer(UpdatableLayer layerType, Layer* layer);
	static void CallUpdatableLayer(UpdatableLayer layerType);
private:
	static std::vector<Layer*> s_UpdatableLayers;
};

extern LayerManager g_LayerManager;

#define REGISTER_UPDATABLE_LAYER(layerType, layer) g_LayerManager.RegisterUpdatableLayer(layerType, layer);
#define UNREGISTER_UPDATABLE_LAYER(layerType, layer) g_LayerManager.UnregisterUpdatableLayer(layerType, layer);
#define CALL_UPDATABLE_LAYER(layerType) g_LayerManager.CallUpdatableLayer(layerType);
