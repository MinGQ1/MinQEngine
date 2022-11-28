#include "LayerManager.h"
#include <MinQDefines.h>
#include <Logger/Log.h>

LayerManager g_LayerManager;
std::vector<Layer*> LayerManager::s_UpdatableLayers(kUpdatableLayerCount, NULL);

void LayerManager::RegisterUpdatableLayer(UpdatableLayer layerType, Layer* layer)
{
	if (s_UpdatableLayers[layerType])
	{
		LogFatal("UpdatableLayer: Register failed");
		return;
	}
	s_UpdatableLayers[layerType] = layer;
}

void LayerManager::UnregisterUpdatableLayer(UpdatableLayer layerType, Layer* layer)
{
	if (layer == s_UpdatableLayers[layerType])
	{
		s_UpdatableLayers[layerType] = NULL;
	}
}
void LayerManager::CallUpdatableLayer(UpdatableLayer layerType)
{
	if (s_UpdatableLayers[layerType])
	{
		s_UpdatableLayers[layerType]->Update();
	}
}


