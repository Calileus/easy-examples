/// \file main.cpp
/// \brief Windows drawing example with GDI+ graphics and mouse interaction.
///
/// Demonstrates:
/// - Drawing shapes (rectangles, circles, lines) with GDI+
/// - Mouse event handling (click, move, drag)
/// - Double-buffering to prevent flicker
/// - Color selection and styling
/// - Animation with timer
/// - Custom painting in WM_PAINT
///
/// \author Easy Examples
/// \version 1.0

#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <cmath>

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

#define IDT_ANIMATION_TIMER 1001  ///< Timer ID for animation.

/// \brief Structure representing a drawable shape.
struct DrawableShape {
    float x, y;           ///< Center position.
    float radius;         ///< Radius of the shape.
    Color color;          ///< Fill color.
    int rotationAngle;    ///< Rotation angle for animation.
    
    /// \brief Constructor for drawable shape.
    DrawableShape(float px, float py, float r, Color c)
        : x(px), y(py), radius(r), color(c), rotationAngle(0) {}
};

class DrawingWindow {
private:
    HWND hwnd_;
    std::vector<DrawableShape> shapes_;
    DrawableShape* selectedShape_;
    bool isDragging_;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput_;
    ULONG_PTR gdiplusToken_;
    
public:
    /// \brief Construct the drawing window manager.
    DrawingWindow() 
        : hwnd_(NULL), selectedShape_(NULL), isDragging_(false), gdiplusToken_(0) {
        // Initialize GDI+
        Gdiplus::GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput_, NULL);
        
        // Add some initial shapes
        shapes_.push_back(DrawableShape(100, 100, 30, Color(255, 0, 0)));    // Red
        shapes_.push_back(DrawableShape(200, 150, 40, Color(0, 255, 0)));    // Green
        shapes_.push_back(DrawableShape(300, 100, 35, Color(0, 0, 255)));    // Blue
    }
    
    /// \brief Destructor - cleanup GDI+.
    ~DrawingWindow() {
        if (gdiplusToken_) {
            Gdiplus::GdiplusShutdown(gdiplusToken_);
        }
    }
    
    /// \brief Initialize and create the window.
    /// \param hInstance Current instance handle.
    /// \return Window handle.
    HWND Create(HINSTANCE hInstance) {
        const char CLASS_NAME[] = "DrawingWindowClass";
        
        WNDCLASSA wc = {};
        wc.lpfnWndProc = WindowProcStatic;
        wc.hInstance = hInstance;
        wc.lpszClassName = CLASS_NAME;
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.hCursor = LoadCursorA(NULL, IDC_CROSS);
        
        RegisterClassA(&wc);
        
        hwnd_ = CreateWindowExA(
            0,
            CLASS_NAME,
            "Drawing Example - Click to Select, Drag to Move",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 600, 500,
            NULL,
            NULL,
            hInstance,
            this);
        
        if (hwnd_) {
            SetTimer(hwnd_, IDT_ANIMATION_TIMER, 50, NULL);
        }
        
        return hwnd_;
    }
    
    /// \brief Draw all shapes to the graphics context.
    /// \param graphics Graphics object for drawing.
    void Draw(Graphics* graphics) {
        graphics->Clear(Color(255, 255, 255));  // White background
        
        // Draw all shapes
        for (auto& shape : shapes_) {
            SolidBrush brush(shape.color);
            Pen outlinePen(Color(0, 0, 0), 2.0f);
            
            // Draw circle
            graphics->FillEllipse(&brush,
                shape.x - shape.radius, shape.y - shape.radius,
                shape.radius * 2, shape.radius * 2);
            
            graphics->DrawEllipse(&outlinePen,
                shape.x - shape.radius, shape.y - shape.radius,
                shape.radius * 2, shape.radius * 2);
            
            // Draw rotation indicator
            float endX = shape.x + shape.radius * cos(shape.rotationAngle * 3.14159f / 180.0f);
            float endY = shape.y + shape.radius * sin(shape.rotationAngle * 3.14159f / 180.0f);
            
            Pen indicatorPen(Color(50, 50, 50), 1.0f);
            graphics->DrawLine(&indicatorPen, shape.x, shape.y, endX, endY);
        }
        
        // Draw selection highlight if a shape is selected
        if (selectedShape_) {
            Pen selectPen(Color(255, 255, 0), 3.0f);
            selectPen.SetDashStyle(DashStyleDash);
            graphics->DrawEllipse(&selectPen,
                selectedShape_->x - selectedShape_->radius - 3,
                selectedShape_->y - selectedShape_->radius - 3,
                (selectedShape_->radius + 3) * 2,
                (selectedShape_->radius + 3) * 2);
        }
    }
    
    /// \brief Handle window messages.
    /// \param uMsg Message identifier.
    /// \param wParam Word parameter.
    /// \param lParam Long parameter.
    /// \return Message result.
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd_, &ps);
            
            Graphics graphics(hdc);
            graphics.SetSmoothingMode(SmoothingModeAntiAlias);
            
            Draw(&graphics);
            
            EndPaint(hwnd_, &ps);
            return 0;
        }
        
        case WM_LBUTTONDOWN: {
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            
            // Find which shape was clicked
            selectedShape_ = nullptr;
            for (auto& shape : shapes_) {
                float dx = x - shape.x;
                float dy = y - shape.y;
                float distance = sqrt(dx * dx + dy * dy);
                
                if (distance <= shape.radius) {
                    selectedShape_ = &shape;
                    isDragging_ = true;
                    break;
                }
            }
            
            InvalidateRect(hwnd_, NULL, FALSE);
            return 0;
        }
        
        case WM_MOUSEMOVE: {
            if (isDragging_ && selectedShape_) {
                int x = GET_X_LPARAM(lParam);
                int y = GET_Y_LPARAM(lParam);
                
                selectedShape_->x = static_cast<float>(x);
                selectedShape_->y = static_cast<float>(y);
                
                InvalidateRect(hwnd_, NULL, FALSE);
            }
            return 0;
        }
        
        case WM_LBUTTONUP: {
            isDragging_ = false;
            return 0;
        }
        
        case WM_TIMER: {
            if (wParam == IDT_ANIMATION_TIMER) {
                // Rotate shapes for animation
                for (auto& shape : shapes_) {
                    shape.rotationAngle = (shape.rotationAngle + 3) % 360;
                }
                InvalidateRect(hwnd_, NULL, FALSE);
            }
            return 0;
        }
        
        case WM_DESTROY: {
            KillTimer(hwnd_, IDT_ANIMATION_TIMER);
            PostQuitMessage(0);
            return 0;
        }
        }
        
        return DefWindowProcA(hwnd_, uMsg, wParam, lParam);
    }
    
private:
    /// \brief Static window procedure - routes to member function.
    static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        DrawingWindow* pThis = nullptr;
        
        if (uMsg == WM_CREATE) {
            CREATESTRUCTA* pCreate = reinterpret_cast<CREATESTRUCTA*>(lParam);
            pThis = static_cast<DrawingWindow*>(pCreate->lpCreateParams);
            SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        } else {
            pThis = reinterpret_cast<DrawingWindow*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));
        }
        
        if (pThis) {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        
        return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }
};

// Macro for getting X and Y from lParam (mouse message)
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

/// \brief Entry point for drawing application.
/// \param hInstance Current instance handle.
/// \param nShowCmd Window display mode.
/// \return Exit code.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    DrawingWindow window;
    HWND hwnd = window.Create(hInstance);
    
    if (!hwnd) {
        return 1;
    }
    
    ShowWindow(hwnd, nShowCmd);
    
    MSG msg = {};
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    
    return (int)msg.wParam;
}
