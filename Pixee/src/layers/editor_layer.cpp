#include "editor_layer.hpp"

namespace pixee
{
	EditorLayer::EditorLayer()
	{
		m_CanvasPosition.x = static_cast<float>(core::Application::getInstance().getWindow()->getWidth() / 2 - 32 * 8);
		m_CanvasPosition.y = static_cast<float>(core::Application::getInstance().getWindow()->getHeight() / 2 - 32 * 8);
		m_Canvas = std::make_shared<Canvas>(64, 64, m_CanvasPosition);

		m_CheckerTextureBG = std::make_shared<gfx::CheckerTexture>(16, utils::ARGB(200, 200, 200, 255), utils::ARGB(150, 150, 150, 255));

		m_ToolShortcutMap[SDLK_b] = ToolType::Pen;
		m_ToolShortcutMap[SDLK_e] = ToolType::Eraser;
		m_ToolShortcutMap[SDLK_r] = ToolType::Rect;
		m_ToolShortcutMap[SDLK_g] = ToolType::BucketFill;
	}

	void EditorLayer::onUpdate()
	{
		if (!m_Initialized)
		{
			UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();
			auto penTool = uiLayer->getToolsPanel().getToolByType(ToolType::Pen);
			setActiveTool(penTool);

			setMenuBarContext(uiLayer);

			m_Initialized = true;
		}

		m_OverlayLayer = core::Application::getInstance().getLayer<OverlayLayer>();

		m_ActiveTool->update();
	}

	void EditorLayer::onRender()
	{
		drawBackground();
		m_Canvas->render();
		m_ActiveTool->render();
	}

	void EditorLayer::onEvent(event::Event& event)
	{
		event::EventDispatcher dispatcher(event);
		dispatcher.dispatch<event::KeyPressedEvent>([this](event::KeyPressedEvent& e) { return onKeyPressed(e); });
		dispatcher.dispatch<event::KeyDownEvent>([this](event::KeyDownEvent& e) { return onKeyDown(e); });
		dispatcher.dispatch<event::KeyReleasedEvent>([this](event::KeyReleasedEvent& e) { return onKeyReleased(e); });

		dispatcher.dispatch<event::MouseButtonPressedEvent>([this](event::MouseButtonPressedEvent& e) { return onMousePress(e); });
		dispatcher.dispatch<event::MouseButtonReleasedEvent>([this](event::MouseButtonReleasedEvent& e) { return onMouseReleased(e); });
		dispatcher.dispatch<event::MouseButtonDownEvent>([this](event::MouseButtonDownEvent& e) { return onMouseDown(e); });
		dispatcher.dispatch<event::MouseMovedEvent>([this](event::MouseMovedEvent& e) { return onMouseMoved(e); });
		dispatcher.dispatch<event::MouseScrolledEvent>([this](event::MouseScrolledEvent& e) { return onMouseScroll(e); });
	}

	void EditorLayer::setActiveTool(std::shared_ptr<Tool> tool)
	{
		m_PreviousActiveTool = m_ActiveTool;
		m_ActiveTool = tool;
	}

	void EditorLayer::handlePanning(event::MouseMovedEvent& e)
	{
		glm::vec2 currentMousePos;
		currentMousePos.x = static_cast<float>(e.getX());
		currentMousePos.y = static_cast<float>(e.getY());

		if (m_IsPanning)
		{
			float deltaX = currentMousePos.x - m_LastMousePosition.x;
			float deltaY = currentMousePos.y - m_LastMousePosition.y;

			m_CanvasPosition.x += deltaX;
			m_CanvasPosition.y += deltaY;

			m_Canvas->setPosition(m_CanvasPosition);
		}

		m_LastMousePosition = m_MousePosition;
		m_MousePosition = currentMousePos;
	}

	void EditorLayer::handleCanvasZooming(event::MouseScrolledEvent& e)
	{
		float oldZoom = static_cast<float>(m_Canvas->getZoom());
		float newZoom = static_cast<float>(std::clamp(m_Canvas->getZoom() + e.getY(), 1, 15));

		if (oldZoom == newZoom)
			return;

		glm::vec2 before = (glm::vec2(m_MousePosition) - m_Canvas->getPosition()) / oldZoom;

		m_Canvas->setZoom(newZoom);

		glm::vec2 after = (glm::vec2(m_MousePosition) - m_Canvas->getPosition()) / newZoom;
		glm::vec2 delta = (after - before) * newZoom;

		m_CanvasPosition += delta;
		m_Canvas->setPosition(m_CanvasPosition);
	}

	void EditorLayer::drawBackground()
	{
		SDL_Renderer* r = core::Application::getInstance().getRenderer();
		int w, h;
		SDL_GetRendererOutputSize(r, &w, &h);

		SDL_Rect clipRect = {
			.x = static_cast<int>(m_Canvas->getPosition().x),
			.y = static_cast<int>(m_Canvas->getPosition().y),
			.w = m_Canvas->getWidth() * m_Canvas->getZoom(),
			.h = m_Canvas->getHeight() * m_Canvas->getZoom()
		};

		SDL_RenderSetClipRect(r, &clipRect);
		m_CheckerTextureBG->draw(glm::vec2(0, 0), w, h);
		SDL_RenderSetClipRect(r, nullptr);
	}

	bool EditorLayer::onKeyPressed(event::KeyPressedEvent& e)
	{
		UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();

		auto it = m_ToolShortcutMap.find(e.getKeyCode());
		if (it != m_ToolShortcutMap.end())
		{
			auto nextTool = uiLayer->getToolsPanel().getToolByType(m_ToolShortcutMap[e.getKeyCode()]);
			
			if (nextTool)
				setActiveTool(nextTool);
		}

		m_ActiveTool->onKeyPressed(e);

		return false;
	}

	bool EditorLayer::onKeyDown(event::KeyDownEvent& e)
	{
		UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();
		if (e.getKeyCode() == SDLK_LALT && !m_ColorPickerToolActive)
		{
			auto colorPickerTool = uiLayer->getToolsPanel().getToolByType(ToolType::ColorPicker);
			if (colorPickerTool)
			{
				setActiveTool(colorPickerTool);
				m_ColorPickerToolActive = true;
			}
		}

		return false;
	}

	bool EditorLayer::onKeyReleased(event::KeyReleasedEvent& e)
	{
		if (e.getKeyCode() == SDLK_LALT && m_ColorPickerToolActive)
		{
			m_ColorPickerToolActive = false;

			if (m_PreviousActiveTool)
			{
				UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();
				auto prevTool = uiLayer->getToolsPanel().getToolByType(m_PreviousActiveTool->getToolType());
				if (prevTool)
					setActiveTool(prevTool);
			}
		}

		return false;
	}

	bool EditorLayer::onMousePress(event::MouseButtonPressedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Middle)
		{
			m_IsPanning = true;
			m_LastMousePosition = m_MousePosition;

			SDL_Cursor* handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			SDL_SetCursor(handCursor);

			return true;
		}

		m_ActiveTool->onMouseButtonPressed(e);

		return false;
	}

	bool EditorLayer::onMouseReleased(event::MouseButtonReleasedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Middle && m_IsPanning)
		{
			m_IsPanning = false;

			SDL_Cursor* arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			SDL_SetCursor(arrowCursor);

			return true;
		}

		m_ActiveTool->onMouseButtonReleased(e);

		return false;
	}

	bool EditorLayer::onMouseDown(event::MouseButtonDownEvent& e)
	{
		glm::ivec2 newPixelPos;
		bool inCanvas = m_Canvas->mouseToCanvasPosition(m_MousePosition, newPixelPos);

		m_ActiveTool->onMouseButtonDown(e);

		return false;
	}

	bool EditorLayer::onMouseMoved(event::MouseMovedEvent& e)
	{
		m_MousePosition.x = e.getX();
		m_MousePosition.y = e.getY();
		m_MouseDelta.x = e.getDeltaX();
		m_MouseDelta.y = e.getDeltaY();

		handlePanning(e);

		m_ActiveTool->onMouseMoved(e);

		return false;
	}

	bool EditorLayer::onMouseScroll(event::MouseScrolledEvent& e)
	{
		handleCanvasZooming(e);

		return false;
	}

	void EditorLayer::setMenuBarContext(UILayer* uiLayer)
	{
		ui::MenuBarContext menuBarCtx;
		menuBarCtx.onOpen = [this]() { openImage(); };
		menuBarCtx.onExportAsPNG = [this]() { exportCanvasImage(); };
		//menuBarCtx.onNew = [this]() { createNewCanvas(); };
		menuBarCtx.onNew = [this]() { m_OverlayLayer->getNewCanvasModal().show(); };

		uiLayer->getMenuBar().setContext(menuBarCtx);
	}

	void EditorLayer::exportCanvasImage()
	{
		nfdfilteritem_t filterItem[1] = { {"PNG", "png"} };
		nfdchar_t* outPath;
		nfdresult_t result = NFD_SaveDialog(&outPath, filterItem, 1, nullptr, "untitled.png");

		if (result == NFD_OKAY)
		{
			std::println("Success! Exporting PNG file to: {}", outPath);

			std::vector<uint8_t> outBytes;
			outBytes.reserve(m_Canvas->getWidth() * m_Canvas->getHeight() * 4);

			for (uint32_t pixel : m_Canvas->getPixels())
			{
				uint8_t a = (pixel >> 24) & 0xFF;
				uint8_t r = (pixel >> 16) & 0xFF;
				uint8_t g = (pixel >> 8) & 0xFF;
				uint8_t b = (pixel >> 0) & 0xFF;

				outBytes.push_back(r);
				outBytes.push_back(g);
				outBytes.push_back(b);
				outBytes.push_back(a);
			}

			int imgResult = stbi_write_png(outPath, m_Canvas->getWidth(), m_Canvas->getHeight(), 4, outBytes.data(), m_Canvas->getWidth() * 4);

			if (imgResult == 0)
			{
				std::println("Failed to export image as PNG!");
			}

			NFD_FreePath(outPath);
		}
		else if (result == NFD_CANCEL)
		{
			std::println("File dialog canceled!");
		}
		else
		{
			std::println("Save File Dialog Error: {}", NFD_GetError());
		}
	}

	void EditorLayer::openImage()
	{
		nfdchar_t* outPath;
		nfdfilteritem_t filterItem[1] = { { "Image Files", "png,jpg,jpeg,bmp" } };
		nfdresult_t dialogResult = NFD_OpenDialog(&outPath, filterItem, 1, nullptr);

		if (dialogResult == NFD_OKAY)
		{
			int width, height, channels;

			unsigned char* data = stbi_load(outPath, &width, &height, &channels, 4);

			if (data)
			{
				m_Canvas->reset(width, height);
				auto& pixelBuffer = m_Canvas->getPixels();
				pixelBuffer.clear();
				pixelBuffer.reserve(width * height);

				for (int i = 0; i < width * height; i++)
				{
					int base = i * 4;
					uint8_t r = data[base + 0];
					uint8_t g = data[base + 1];
					uint8_t b = data[base + 2];
					uint8_t a = data[base + 3];

					uint32_t packedPixel =  (static_cast<uint32_t>(a) << 24) |
											(static_cast<uint32_t>(r) << 16) |
											(static_cast<uint32_t>(g) << 8) |
											(static_cast<uint32_t>(b) << 0);
				
					pixelBuffer.push_back(packedPixel);
				}
			}

			stbi_image_free(data);
			
			std::println("Loaded image successfully!");
		}

		NFD_FreePath(outPath);
	}
	
	void EditorLayer::createNewCanvas()
	{
		glm::vec2 newCanvasPos = m_Canvas->getPosition();

		m_Canvas->reset(64, 64);
	}
}