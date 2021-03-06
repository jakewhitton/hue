#pragma once

#include "BridgeRenderer.h"
#include "Config.h"
#include <huestream/common/data/Color.h>
#include <thread>
#include <memory>

class MultiBridgeRenderer
{
public:
	MultiBridgeRenderer(const Config & config);

	void start();
	void stop();

protected:
	static constexpr unsigned N = 24;

	void run();
	virtual void prepareFrame();
	void renderFrame();

	bool running_ = false;
	std::thread thread_;
	std::vector<std::unique_ptr<BridgeRenderer>> renderer_;

	huestream::Color colors_[N];

	// Timing
	double fps_ = 30;
	std::chrono::time_point<std::chrono::system_clock> frameStart_;
	std::chrono::time_point<std::chrono::system_clock> frameEnd_;
	std::chrono::duration<double> desiredFrameTime_ =
		std::chrono::milliseconds(33);
};
