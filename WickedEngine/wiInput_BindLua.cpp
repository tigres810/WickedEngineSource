#include "wiInput_BindLua.h"
#include "wiMath_BindLua.h"

namespace wi::lua
{

	Luna<Input_BindLua>::FunctionType Input_BindLua::methods[] = {
		lunamethod(Input_BindLua, Down),
		lunamethod(Input_BindLua, Press),
		lunamethod(Input_BindLua, Release),
		lunamethod(Input_BindLua, Hold),
		lunamethod(Input_BindLua, GetPointer),
		lunamethod(Input_BindLua, SetPointer),
		lunamethod(Input_BindLua, GetPointerDelta),
		lunamethod(Input_BindLua, HidePointer),
		lunamethod(Input_BindLua, GetAnalog),
		lunamethod(Input_BindLua, GetTouches),
		lunamethod(Input_BindLua, SetControllerFeedback),
		{ NULL, NULL }
	};
	Luna<Input_BindLua>::PropertyType Input_BindLua::properties[] = {
		{ NULL, NULL }
	};

	int Input_BindLua::Down(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::input::BUTTON button = (wi::input::BUTTON)wi::lua::SGetInt(L, 1);
			int playerindex = 0;
			if (argc > 1)
			{
				playerindex = wi::lua::SGetInt(L, 2);
			}
			wi::lua::SSetBool(L, wi::input::Down(button, playerindex));
			return 1;
		}
		else
			wi::lua::SError(L, "Down(int code, opt int playerindex = 0) not enough arguments!");
		return 0;
	}
	int Input_BindLua::Press(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::input::BUTTON code = (wi::input::BUTTON)wi::lua::SGetInt(L, 1);
			int playerindex = 0;
			if (argc > 1)
			{
				playerindex = wi::lua::SGetInt(L, 2);
			}
			wi::lua::SSetBool(L, wi::input::Press(code, playerindex));
			return 1;
		}
		else
			wi::lua::SError(L, "Press(int code, opt int playerindex = 0) not enough arguments!");
		return 0;
	}
	int Input_BindLua::Release(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::input::BUTTON code = (wi::input::BUTTON)wi::lua::SGetInt(L, 1);
			int playerindex = 0;
			if (argc > 1)
			{
				playerindex = wi::lua::SGetInt(L, 2);
			}
			wi::lua::SSetBool(L, wi::input::Release(code, playerindex));
			return 1;
		}
		else
			wi::lua::SError(L, "Release(int code, opt int playerindex = 0) not enough arguments!");
		return 0;
	}
	int Input_BindLua::Hold(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::input::BUTTON button = (wi::input::BUTTON)wi::lua::SGetInt(L, 1);
			uint32_t duration = 30;
			if (argc > 1)
			{
				duration = wi::lua::SGetInt(L, 2);
			}
			bool continuous = false;
			if (argc > 2)
			{
				continuous = wi::lua::SGetBool(L, 3);
			}
			int playerindex = 0;
			if (argc > 3)
			{
				playerindex = wi::lua::SGetInt(L, 4);
			}
			wi::lua::SSetBool(L, wi::input::Hold(button, duration, continuous, playerindex));
			return 1;
		}
		else
			wi::lua::SError(L, "Hold(int code, opt int duration = 30, opt boolean continuous = false, opt int playerindex = 0) not enough arguments!");
		return 0;
	}
	int Input_BindLua::GetPointer(lua_State* L)
	{
		XMFLOAT4 P = wi::input::GetPointer();
		Luna<Vector_BindLua>::push(L, XMLoadFloat4(&P));
		return 1;
	}
	int Input_BindLua::SetPointer(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			Vector_BindLua* vec = Luna<Vector_BindLua>::lightcheck(L, 1);
			if (vec != nullptr)
			{
				wi::input::SetPointer(vec->data);
			}
			else
				wi::lua::SError(L, "SetPointer(Vector props) argument is not a Vector!");
		}
		else
			wi::lua::SError(L, "SetPointer(Vector props) not enough arguments!");
		return 0;
	}
	int Input_BindLua::GetPointerDelta(lua_State* L)
	{
		Luna<Vector_BindLua>::push(L, XMLoadFloat2(&wi::input::GetMouseState().delta_position));
		return 1;
	}
	int Input_BindLua::HidePointer(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::input::HidePointer(wi::lua::SGetBool(L, 1));
		}
		else
			wi::lua::SError(L, "HidePointer(bool value) not enough arguments!");
		return 0;
	}
	int Input_BindLua::GetAnalog(lua_State* L)
	{
		XMFLOAT4 result = XMFLOAT4(0, 0, 0, 0);

		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			wi::input::GAMEPAD_ANALOG type = (wi::input::GAMEPAD_ANALOG)wi::lua::SGetInt(L, 1);
			int playerindex = 0;
			if (argc > 1)
			{
				playerindex = wi::lua::SGetInt(L, 2);
			}
			result = wi::input::GetAnalog(type, playerindex);
		}
		else
			wi::lua::SError(L, "GetAnalog(int type, opt int playerindex = 0) not enough arguments!");

		Luna<Vector_BindLua>::push(L, XMLoadFloat4(&result));
		return 1;
	}
	int Input_BindLua::GetTouches(lua_State* L)
	{
		auto& touches = wi::input::GetTouches();
		for (auto& touch : touches)
		{
			Luna<Touch_BindLua>::push(L, touch);
		}
		return (int)touches.size();
	}
	int Input_BindLua::SetControllerFeedback(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			ControllerFeedback_BindLua* fb = Luna<ControllerFeedback_BindLua>::lightcheck(L, 1); // Ferdinand Braun
			if (fb != nullptr)
			{
				int playerindex = 0;
				if (argc > 1)
				{
					playerindex = wi::lua::SGetInt(L, 2);
				}
				wi::input::SetControllerFeedback(fb->feedback, playerindex);
			}
			else
			{
				wi::lua::SError(L, "SetControllerFeedback(ControllerFeedback feedback, opt int playerindex = 0) first argument is not a ControllerFeedback!");
			}
		}
		else
			wi::lua::SError(L, "SetControllerFeedback(ControllerFeedback feedback, opt int playerindex = 0) not enough arguments!");
		return 0;
	}

	void Input_BindLua::Bind()
	{
		static bool initialized = false;
		if (!initialized)
		{
			initialized = true;
			Luna<Input_BindLua>::Register(wi::lua::GetLuaState());

			wi::lua::RunText(R"(
input = Input()

GAMEPAD_BUTTON_UP			= 257
GAMEPAD_BUTTON_LEFT			= 258
GAMEPAD_BUTTON_DOWN			= 259
GAMEPAD_BUTTON_RIGHT		= 260
GAMEPAD_BUTTON_1			= 261
GAMEPAD_BUTTON_2			= 262
GAMEPAD_BUTTON_3			= 263
GAMEPAD_BUTTON_4			= 264
GAMEPAD_BUTTON_5			= 265
GAMEPAD_BUTTON_6			= 266
GAMEPAD_BUTTON_7			= 267
GAMEPAD_BUTTON_8			= 268
GAMEPAD_BUTTON_9			= 269
GAMEPAD_BUTTON_10			= 270
GAMEPAD_BUTTON_11			= 271
GAMEPAD_BUTTON_12			= 272
GAMEPAD_BUTTON_13			= 273
GAMEPAD_BUTTON_14			= 274

GAMEPAD_BUTTON_XBOX_X = GAMEPAD_BUTTON_1
GAMEPAD_BUTTON_XBOX_A = GAMEPAD_BUTTON_2
GAMEPAD_BUTTON_XBOX_B = GAMEPAD_BUTTON_3
GAMEPAD_BUTTON_XBOX_Y = GAMEPAD_BUTTON_4
GAMEPAD_BUTTON_XBOX_L1 = GAMEPAD_BUTTON_5
GAMEPAD_BUTTON_XBOX_R1 = GAMEPAD_BUTTON_6
GAMEPAD_BUTTON_XBOX_L3 = GAMEPAD_BUTTON_7
GAMEPAD_BUTTON_XBOX_R3 = GAMEPAD_BUTTON_8
GAMEPAD_BUTTON_XBOX_BACK = GAMEPAD_BUTTON_9
GAMEPAD_BUTTON_XBOX_START = GAMEPAD_BUTTON_10

GAMEPAD_BUTTON_PLAYSTATION_SQUARE = GAMEPAD_BUTTON_1
GAMEPAD_BUTTON_PLAYSTATION_CROSS = GAMEPAD_BUTTON_2
GAMEPAD_BUTTON_PLAYSTATION_CIRCLE = GAMEPAD_BUTTON_3
GAMEPAD_BUTTON_PLAYSTATION_TRIANGLE = GAMEPAD_BUTTON_4
GAMEPAD_BUTTON_PLAYSTATION_L1 = GAMEPAD_BUTTON_5
GAMEPAD_BUTTON_PLAYSTATION_R1 = GAMEPAD_BUTTON_6
GAMEPAD_BUTTON_PLAYSTATION_L3 = GAMEPAD_BUTTON_7
GAMEPAD_BUTTON_PLAYSTATION_R3 = GAMEPAD_BUTTON_8
GAMEPAD_BUTTON_PLAYSTATION_SHARE = GAMEPAD_BUTTON_9
GAMEPAD_BUTTON_PLAYSTATION_OPTION = GAMEPAD_BUTTON_10
GAMEPAD_BUTTON_PLAYSTATION_SELECT = GAMEPAD_BUTTON_PLAYSTATION_SHARE
GAMEPAD_BUTTON_PLAYSTATION_START = GAMEPAD_BUTTON_PLAYSTATION_OPTION
			
GAMEPAD_ANALOG_THUMBSTICK_L	= 0
GAMEPAD_ANALOG_THUMBSTICK_R	= 1
GAMEPAD_ANALOG_TRIGGER_L	= 2
GAMEPAD_ANALOG_TRIGGER_R	= 3
			
TOUCHSTATE_PRESSED			= 0
TOUCHSTATE_RELEASED			= 1
TOUCHSTATE_MOVED			= 2

MOUSE_BUTTON_LEFT			= 276
MOUSE_BUTTON_RIGHT			= 277
MOUSE_BUTTON_MIDDLE			= 278

KEYBOARD_BUTTON_UP			= 279
KEYBOARD_BUTTON_DOWN		= 280
KEYBOARD_BUTTON_LEFT		= 281
KEYBOARD_BUTTON_RIGHT		= 282
KEYBOARD_BUTTON_SPACE		= 283
KEYBOARD_BUTTON_RSHIFT		= 284
KEYBOARD_BUTTON_LSHIFT		= 285
KEYBOARD_BUTTON_F1			= 286
KEYBOARD_BUTTON_F2			= 287
KEYBOARD_BUTTON_F3			= 288
KEYBOARD_BUTTON_F4			= 289
KEYBOARD_BUTTON_F5			= 290
KEYBOARD_BUTTON_F6			= 291
KEYBOARD_BUTTON_F7			= 292
KEYBOARD_BUTTON_F8			= 293
KEYBOARD_BUTTON_F9			= 294
KEYBOARD_BUTTON_F10			= 295
KEYBOARD_BUTTON_F11			= 296
KEYBOARD_BUTTON_F12			= 297
KEYBOARD_BUTTON_ENTER		= 298
KEYBOARD_BUTTON_ESCAPE		= 299
KEYBOARD_BUTTON_HOME		= 300
KEYBOARD_BUTTON_RCONTROL	= 301
KEYBOARD_BUTTON_LCONTROL	= 302
KEYBOARD_BUTTON_DELETE		= 303
KEYBOARD_BUTTON_BACK		= 304
KEYBOARD_BUTTON_PAGEDOWN	= 305
KEYBOARD_BUTTON_PAGEUP		= 306
KEYBOARD_BUTTON_NUMPAD0		= 307
KEYBOARD_BUTTON_NUMPAD1		= 308
KEYBOARD_BUTTON_NUMPAD2		= 309
KEYBOARD_BUTTON_NUMPAD3		= 310
KEYBOARD_BUTTON_NUMPAD4		= 311
KEYBOARD_BUTTON_NUMPAD5		= 312
KEYBOARD_BUTTON_NUMPAD6		= 313
KEYBOARD_BUTTON_NUMPAD7		= 314
KEYBOARD_BUTTON_NUMPAD8		= 315
KEYBOARD_BUTTON_NUMPAD9		= 316
KEYBOARD_BUTTON_MULTIPLY	= 317
KEYBOARD_BUTTON_ADD			= 318
KEYBOARD_BUTTON_SEPARATOR	= 319
KEYBOARD_BUTTON_SUBTRACT	= 320
KEYBOARD_BUTTON_DECIMAL		= 321
KEYBOARD_BUTTON_DIVIDE		= 322
KEYBOARD_BUTTON_TAB			= 323
KEYBOARD_BUTTON_TILDE		= 324
)");

		}

		Touch_BindLua::Bind();
		ControllerFeedback_BindLua::Bind();
	}







	Luna<Touch_BindLua>::FunctionType Touch_BindLua::methods[] = {
		lunamethod(Touch_BindLua, GetState),
		lunamethod(Touch_BindLua, GetPos),
		{ NULL, NULL }
	};
	Luna<Touch_BindLua>::PropertyType Touch_BindLua::properties[] = {
		{ NULL, NULL }
	};

	int Touch_BindLua::GetState(lua_State* L)
	{
		wi::lua::SSetInt(L, (int)touch.state);
		return 1;
	}
	int Touch_BindLua::GetPos(lua_State* L)
	{
		Luna<Vector_BindLua>::push(L, XMLoadFloat2(&touch.pos));
		return 1;
	}

	void Touch_BindLua::Bind()
	{
		static bool initialized = false;
		if (!initialized)
		{
			initialized = true;
			Luna<Touch_BindLua>::Register(wi::lua::GetLuaState());
		}
	}







	Luna<ControllerFeedback_BindLua>::FunctionType ControllerFeedback_BindLua::methods[] = {
		lunamethod(ControllerFeedback_BindLua, SetVibrationRight),
		lunamethod(ControllerFeedback_BindLua, SetVibrationLeft),
		lunamethod(ControllerFeedback_BindLua, SetLEDColor),
		{ NULL, NULL }
	};
	Luna<ControllerFeedback_BindLua>::PropertyType ControllerFeedback_BindLua::properties[] = {
		{ NULL, NULL }
	};

	int ControllerFeedback_BindLua::SetVibrationLeft(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			feedback.vibration_left = wi::lua::SGetFloat(L, 1);
		}
		else
		{
			wi::lua::SError(L, "SetVibrationLeft(float value) not enough arguments!");
		}
		return 0;
	}
	int ControllerFeedback_BindLua::SetVibrationRight(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			feedback.vibration_right = wi::lua::SGetFloat(L, 1);
		}
		else
		{
			wi::lua::SError(L, "SetVibrationRight(float value) not enough arguments!");
		}
		return 0;
	}
	int ControllerFeedback_BindLua::SetLEDColor(lua_State* L)
	{
		int argc = wi::lua::SGetArgCount(L);
		if (argc > 0)
		{
			Vector_BindLua* vec = Luna<Vector_BindLua>::lightcheck(L, 1);
			if (vec != nullptr)
			{
				feedback.led_color = wi::Color::fromFloat4(vec->data);
			}
			else
			{
				feedback.led_color.rgba = wi::lua::SGetInt(L, 1);
			}
		}
		else
		{
			wi::lua::SError(L, "SetLEDColor(int hexcolor) not enough arguments!");
		}
		return 0;
	}

	void ControllerFeedback_BindLua::Bind()
	{
		static bool initialized = false;
		if (!initialized)
		{
			initialized = true;
			Luna<ControllerFeedback_BindLua>::Register(wi::lua::GetLuaState());
		}
	}

}
