#ifndef BUCKET_FILL_TOOL_HPP
#define BUCKET_FILL_TOOL_HPP

#include <stack>

#include "tool/tool.hpp"
#include "utils.hpp"

namespace pixee
{
	class BucketFillTool : public Tool
	{
	public:
		BucketFillTool(Canvas& canvas);

		void render() override;

		bool onMouseButtonPressed(event::MouseButtonPressedEvent& e) override;

	private:
		void floodFill(int x, int y, uint32_t targetColor, uint32_t newColor);
		void scanNeighbors(int lx, int rx, int y, uint32_t targetColor, std::stack<glm::ivec2>& stack);
	};
}

#endif