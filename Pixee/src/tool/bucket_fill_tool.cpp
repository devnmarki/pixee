#include "bucket_fill_tool.hpp"

#include "layers/ui_layer.hpp"

namespace pixee
{
	BucketFillTool::BucketFillTool(Canvas& canvas)
		: Tool("Bucket", ToolType::BucketFill, canvas)
	{

	}

	void BucketFillTool::render()
	{
		glm::ivec2 placeholderPixelPos;
		if (!m_Canvas.mouseToCanvasPosition(m_MousePosition, placeholderPixelPos))
			return;

		SDL_Renderer* renderer = core::Application::getInstance().getRenderer();

		int screenX = static_cast<int>(m_Canvas.getPosition().x) + (placeholderPixelPos.x * m_Canvas.getZoom());
		int screenY = static_cast<int>(m_Canvas.getPosition().y) + (placeholderPixelPos.y * m_Canvas.getZoom());

		SDL_Rect placeholderPixelRect = {
			.x = screenX,
			.y = screenY,
			.w = m_Canvas.getZoom(),
			.h = m_Canvas.getZoom()
		};

		UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();
		ui::ColorPickerPanel& colorPicker = uiLayer->getColorPickerPanel();
		glm::vec4 activeColor = colorPicker.getSelectedColor();

		SDL_SetRenderDrawColor(
			renderer,
			static_cast<uint8_t>(activeColor.r * 255),
			static_cast<uint8_t>(activeColor.g * 255),
			static_cast<uint8_t>(activeColor.b * 255),
			static_cast<uint8_t>(activeColor.a * 255)
		);
		SDL_RenderFillRect(renderer, &placeholderPixelRect);
	}

	bool BucketFillTool::onMouseButtonPressed(event::MouseButtonPressedEvent& e)
	{
		glm::ivec2 canvasMousePos;
		if (!m_Canvas.mouseToCanvasPosition(m_MousePosition, canvasMousePos))
			return false;

		if (e.getButton() == event::MouseButton::Left)
		{
			glm::vec4 newColor = core::Application::getInstance().getLayer<UILayer>()->getColorPickerPanel().getSelectedColor();
			uint32_t newColorARGB = utils::ARGB(
				static_cast<uint8_t>(newColor.r * 255),
				static_cast<uint8_t>(newColor.g * 255),
				static_cast<uint8_t>(newColor.b * 255),
				static_cast<uint8_t>(newColor.a * 255)
			);
			uint32_t targetColor = m_Canvas.getPixel(canvasMousePos);

			floodFill(canvasMousePos.x, canvasMousePos.y, targetColor, newColorARGB);
		}

		return false;
	}

	void BucketFillTool::floodFill(int x, int y, uint32_t targetColor, uint32_t newColor)
	{
		if (targetColor == newColor)
			return;

		std::stack<glm::ivec2> stack;
		stack.push({ x, y });

		while (!stack.empty())
		{
			glm::ivec2 p = stack.top();
			stack.pop();

			int lx = p.x;
			while (lx >= 0 && m_Canvas.getPixel(glm::ivec2(lx, p.y)) == targetColor)
			{
				m_Canvas.setPixel(glm::ivec2(lx, p.y), newColor);
				lx--;
			}

			int rx = p.x + 1;
			while (rx < m_Canvas.getWidth() && m_Canvas.getPixel(glm::ivec2(rx, p.y)) == targetColor)
			{
				m_Canvas.setPixel(glm::ivec2(rx, p.y), newColor);
				rx++;
			}

			scanNeighbors(lx + 1, rx - 1, p.y + 1, targetColor, stack);
			scanNeighbors(lx + 1, rx - 1, p.y - 1, targetColor, stack);
		}
	}

	void BucketFillTool::scanNeighbors(int lx, int rx, int y, uint32_t targetColor, std::stack<glm::ivec2>& stack)
	{
		if (y < 0 || y >= m_Canvas.getHeight())
			return;

		bool addedLast = false;
		for (int x = lx; x <= rx; x++)
		{
			if (m_Canvas.getPixel(glm::ivec2(x, y)) == targetColor)
			{
				if (!addedLast)
				{
					stack.push({ x, y });
					addedLast = true;
				}
			}
			else 
			{
				addedLast = false;
			}
		}
	}
}