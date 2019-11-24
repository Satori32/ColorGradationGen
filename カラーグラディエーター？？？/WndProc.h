#pragma once
#include <tuple>
#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include "WindowClass.h"

class GradationProc :public Window::EventHandler {

	typedef std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> Color;

	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

		switch (msg)
		{
			case WM_CREATE:
				GB = CreateWindow(
					TEXT("BUTTON"), TEXT("ColotSelect"),
					WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
					0, 0, 112, 120,
					hWnd, NULL, ((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				CB = CreateWindow(
					TEXT("BUTTON"), TEXT("•ÏXI"),
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					//110, 22, 82 , 48,
					456, 420, 82 ,112,
					hWnd, (HMENU)1, ((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				CreateWindow(
					TEXT("STATIC"), TEXT("Sep") ,
					WS_CHILD | WS_VISIBLE | SS_CENTER,
					46, 94, 24, 22,
					GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				SP=CreateWindow(
					TEXT("EDIT"), TEXT("16"),
					WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
					72, 94, 28, 22, 
					GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				CreateWindow(
					TEXT("STATIC"), TEXT("R") ,
					WS_CHILD | WS_VISIBLE | SS_CENTER,
					12, 24, 12, 16,
					GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				R0=CreateWindow(
					TEXT("EDIT"), TEXT("0"),
					WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
					24, 22, 28, 22, GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				CreateWindow(
					TEXT("STATIC"), TEXT("G") ,
					WS_CHILD | WS_VISIBLE | SS_CENTER,
					12, 48, 12, 16,
					GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				G0=CreateWindow(
					TEXT("EDIT"), TEXT("0"),
					WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
					24, 46, 28, 22, GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				CreateWindow(
					TEXT("STATIC"), TEXT("B") ,
					WS_CHILD | WS_VISIBLE | SS_CENTER,
					12, 72, 12, 16,
					GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				B0=CreateWindow(
					TEXT("EDIT"), TEXT("0"),
					WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
					24, 70, 28, 22, GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				//---**
				CreateWindow(
					TEXT("STATIC"), TEXT("R") ,
					WS_CHILD | WS_VISIBLE | SS_CENTER,
					60, 24, 12, 16,
					GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);

				R1=CreateWindow(
					TEXT("EDIT"), TEXT("255"),
					WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
					72, 22, 28, 22, GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				CreateWindow(
					TEXT("STATIC"), TEXT("G") ,
					WS_CHILD | WS_VISIBLE | SS_CENTER,
					60, 48, 12, 16,
					GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				G1=CreateWindow(
					TEXT("EDIT"), TEXT("255"),
					WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
					72, 46, 28, 22, GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				CreateWindow(
					TEXT("STATIC"), TEXT("B") ,
					WS_CHILD | WS_VISIBLE | SS_CENTER,
					60, 72, 12, 16,
					GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);
				B1=CreateWindow(
					TEXT("EDIT"), TEXT("255"),
					WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
					72, 70, 28, 22, GB, 0,
					((LPCREATESTRUCT)(lp))->hInstance, NULL
				);	
				{
					RECT rt = { 0, };
					GetWindowRect(hWnd, &rt);
					std::size_t WW = rt.right - rt.left;
					std::size_t WH = rt.bottom - rt.top;
					GetWindowRect(GB, &rt);
					std::size_t GW = rt.right - rt.left;
					std::size_t GH = rt.bottom - rt.top;
					GetClientRect(hWnd, &rt);
					std::size_t CW = rt.right - rt.left;
					std::size_t CH = rt.bottom - rt.top;
					MoveWindow(hWnd, (WW - CW) + WW, WH + (WH - CH)+16, WW, WH, TRUE);
					MoveWindow(GB, WW / 2-GW/2, WH-(GH+(WH-CH)+8), GW, GH, TRUE);
				}
				break;
			case WM_COMMAND: {
				if (LOWORD(wp) == 1) {
					char Ch[4] = { 0, };
					GetWindowTextA(R0, Ch, 4);
					std::get<0>(First) = std::atoi(Ch);
					GetWindowTextA(G0, Ch, 4);
					std::get<1>(First) = std::atoi(Ch);
					GetWindowTextA(B0, Ch, 4);
					std::get<2>(First) = std::atoi(Ch);
					//--
					GetWindowTextA(R1, Ch, 4);
					std::get<0>(Last) = std::atoi(Ch);
					GetWindowTextA(G1, Ch, 4);
					std::get<1>(Last) = std::atoi(Ch);
					GetWindowTextA(B1, Ch, 4);
					std::get<2>(Last) = std::atoi(Ch);
					GetWindowTextA(SP, Ch, 4);
					Sep = std::atoi(Ch);

					InvalidateRect(hWnd, nullptr, TRUE);
				}
			}
				break;
			case WM_PAINT: {
				PAINTSTRUCT ps;
				HDC hDC = BeginPaint(hWnd, &ps);

				std::size_t RD = std::get<0>(Last) - std::get<0>(First);
				std::size_t GD = std::get<1>(Last) - std::get<1>(First);
				std::size_t BD = std::get<2>(Last) - std::get<2>(First);
				double D = 1.0 / Sep;

				RECT rt = { 0, };

				GetWindowRect(GB, &rt);
				std::size_t GW = rt.right - rt.left;
				std::size_t GH = rt.bottom - rt.top;
				RECT crt = { 0, };
				
				GetClientRect(hWnd, &crt);
				std::size_t CW = crt.right - crt.left;
				std::size_t CH = crt.bottom - crt.top;
				
				Rectangle(hDC, 16, 16, CW-16, CH-(GH+32));
				double P = (CW - (16.0*2)) / Sep;
				for (std::size_t i = 0; i < Sep; i++) {
					double R = std::get<0>(First) + (RD / (double)Sep) * i;
					double G = std::get<1>(First) + (GD / (double)Sep) * i;
					double B = std::get<2>(First) + (BD / (double)Sep) * i;
					HBRUSH Br=CreateSolidBrush(RGB(std::abs(R),std::abs(G),std::abs(B)));
					HBRUSH O = SelectBrush(hDC, Br);
					Rectangle(hDC, 16+(P*(i)),16, 16+P*(i+1),  CH-(GH+16+8));
					SelectBrush(hDC, O);
					DeleteBrush(Br);
				}
				PF = true;
				EndPaint(hWnd, &ps);

			}		
				break;
			case WM_SIZE:
			case WM_SIZING:
			{

				if (!PF) { return DefWindowProc(hWnd, msg, wp, lp); }
				RECT rt = { 0, };
				GetWindowRect(hWnd, &rt);
				std::size_t WW = rt.right - rt.left;
				std::size_t WH = rt.bottom - rt.top;
				RECT grt = { 0, };
				GetWindowRect(GB, &grt);
				std::size_t GW = grt.right - grt.left;
				std::size_t GH = grt.bottom - grt.top;

				RECT crt = { 0, };
				GetClientRect(hWnd, &crt);
				std::size_t CW = crt.right - crt.left;
				std::size_t CH = crt.bottom - crt.top;

				RECT brt = { 0, };
				GetWindowRect(CB, &brt);
				std::size_t BW = brt.right - brt.left;
				std::size_t BH = brt.bottom - brt.top;
				std::size_t BX = WW/2+GW/2;
				std::size_t BY = WH-(BH+(WH-CH+16));
				MoveWindow(GB, WW / 2-GW/2, WH-(GH+(WH-CH)+16), GW, GH, TRUE);
				MoveWindow(CB, BX, BY, BW, BH,TRUE);
			}
			break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(hWnd, msg, wp, lp);
		}
		return 0;
	}
protected:
	HWND R0 = nullptr, R1 = nullptr;
	HWND G0 = nullptr, G1 = nullptr;
	HWND B0 = nullptr, B1 = nullptr;
	HWND GB = nullptr;
	HWND SP = nullptr;
	HWND CB = nullptr;

	Color First;
	Color Last;
	std::uint8_t Sep = 16;
	bool PF = false;
};


