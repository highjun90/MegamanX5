#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include <assert.h>

//#include <GameEngineBase/GameEngineMath.h>



#define MsgBoxAssert(Text) \
std::string Value = Text; \
MessageBoxA(nullptr, Value.c_str(), "Error", MB_OK); assert(false);

// GameEngineMath.h
// GameEngineMath 클래스와 float4 클래스, GameEngineRact 클래스
class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;

	static const float D2R;
	static const float R2D;

	// 3.14 => 180도
	// float R = 3.14;
	// float Result = R * (180.0f / 3.14);

};

class float4
{
public:
	static const float4 ZERO;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

	// 실수는 기본적으로 == 이 거의 불가능하다. 
	// 해도 정확하지 않는다. 실수를 처리하는 방식이 애초에 정확하지 않기 때문이다.
	// 부동소수점 계산방식은 기본적으로 오차를 가지고 있고
	// + - 등을 할때 여러분들의 생각과는 다른 값이 존재할 가능성이 높다. 
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 1.0f;

	inline int iX() const
	{
		return static_cast<int>(X);
	}

	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	inline float hX() const
	{
		return X * 0.5f;
	}

	inline float hY() const
	{
		return Y * 0.5f;
	}


	inline int ihX() const
	{
		return static_cast<int>(hX());
	}

	inline int ihY() const
	{
		return static_cast<int>(hY());
	}

	inline float4 Half() const
	{
		return { hX(), hY(), Z, W };
	}

	float4 operator-() const
	{
		float4 ReturnValue = *this;

		ReturnValue.X = -ReturnValue.X;
		ReturnValue.Y = -ReturnValue.Y;
		ReturnValue.Z = -ReturnValue.Z;
		return ReturnValue;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X - _Other.X;
		ReturnValue.Y = Y - _Other.Y;
		ReturnValue.Z = Z - _Other.Z;

		return ReturnValue;
	}



	float4 operator+(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X + _Other.X;
		ReturnValue.Y = Y + _Other.Y;
		ReturnValue.Z = Z + _Other.Z;

		return ReturnValue;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Other.X;
		ReturnValue.Y = Y * _Other.Y;
		ReturnValue.Z = Z * _Other.Z;

		return ReturnValue;
	}


	float4 operator*(const float _Value) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Value;
		ReturnValue.Y = Y * _Value;
		ReturnValue.Z = Z * _Value;

		return ReturnValue;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}


	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4& operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	bool operator==(const float4 _Value) const
	{
		return X == _Value.X &&
			Y == _Value.Y &&
			Z == _Value.Z;
	}

	inline void Normalize()
	{
		// 길이를 1로 만드는 함수입니다.
		float Len = Size();

		if (0.0f == Len)
		{
			// MsgBoxAssert("0으로 나누려고 했습니다.");
			return;
		}

		X /= Len;
		Y /= Len;
		Z /= Len;
	}

	inline float4 NormalizeReturn()
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	inline float Size()
	{
		float Value = X * X + Y * Y; // == 빗변 * 빗변

		// 제곱수이다.
		// 제곱을 풀어서 제곱근이라고 합니다.
		Value; // 빗변 * 빗변 => 빗변

		return sqrtf(Value);
	}

	float Max2D() const
	{
		return X > Y ? X : Y;
	}

	POINT WindowPOINT()
	{
		return POINT{ iX(), iY() };
	}

	float4 	GetRotationToDegZ(const float _Angle) const
	{
		return GetRotationToDegZ(*this, _Angle);
	}


public:
	inline float AngleDeg()
	{
		return AngleRad() * GameEngineMath::R2D;
	}

	inline float AngleRad()
	{
		float4 AngleVector = NormalizeReturn();

		// 라디안 각도만 나오게 된다. = acosf(AngleVector.X);

		float Angle = acosf(AngleVector.X);

		if (0 >= AngleVector.Y)
		{
			Angle = GameEngineMath::PI + GameEngineMath::PI - Angle;
		}

		return Angle;
	}

	static float4 GetRotationToDegZ(const float4& _Value, const float _Deg)
	{
		return GetRotationToRadZ(_Value, _Deg * GameEngineMath::D2R);
	}

	static float4 GetRotationToRadZ(const float4& _Value, const float _Rad)
	{
		float4 Rot;
		Rot.X = _Value.X * cosf(_Rad) - _Value.Y * sinf(_Rad);
		Rot.Y = _Value.X * sinf(_Rad) + _Value.Y * cosf(_Rad);
		return Rot;
	}

	static float4 LerpClimp(const float4& Start, const float4& _End, float _Ratio)
	{

		if (1.0f <= _Ratio)
		{
			_Ratio = 1.0f;
		}

		return (Start * (1.0f - _Ratio)) + (_End * _Ratio);
	}
	// GetUnitVectorFromDeg(45)

	static float4 GetUnitVectorFromDeg(const float _Degree)
	{
		// 90 => 1.57
		return GetUnitVectorFromRad(_Degree * GameEngineMath::D2R);
	}

	//                                       90.0f
	static float4 GetUnitVectorFromRad(const float _Rad)
	{
		// cosf(_Rad)반지름의 길이 1일때의 cosf값이 구해집니다.
		// sinf(_Rad)반지름의 길이 1일때의 sinf값이 구해집니다.
		// => 빗변의 길이가 1일때의 결과가 나온다.

		// 1.57
		return { cosf(_Rad) , sinf(_Rad) };
	}
};


class GameEngineRect
{
public:
	float4 Scale;
	float4 Pos;

public:
	float4 CenterLeftTop()
	{
		return { CenterLeft(), CenterTop() };
	}

	float4 CenterRightTop()
	{
		return{ CenterRight(), CenterTop() };
	}

	float4 CenterLeftBot()
	{
		return{ CenterLeft(), CenterBot() };
	}

	float4 CenterRightBot()
	{
		return{ CenterRight(), CenterBot() };
	}

	float CenterLeft()
	{
		return Pos.X - Scale.hX();
	}

	float CenterRight()
	{
		return Pos.X + Scale.hX();
	}

	float CenterTop()
	{
		return Pos.Y - Scale.hY();
	}

	float CenterBot()
	{
		return Pos.Y + Scale.hY();
	}

	int iCenterLeft()
	{
		return Pos.iX() - Scale.ihX();
	}

	int iCenterRight()
	{
		return Pos.iX() + Scale.ihX();
	}

	int iCenterTop()
	{
		return Pos.iY() - Scale.ihY();
	}

	int iCenterBot()
	{
		return Pos.iY() + Scale.ihY();
	}
};

//GameEngineMath.cpp 
const float4 float4::ZERO = { 0.0f, 0.0f, 0.0f, 0.0f };

const float4 float4::LEFT = { -1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::RIGHT = { 1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::UP = { 0.0f, -1.0f, 0.0f, 0.0f };
const float4 float4::DOWN = { 0.0f, 1.0f, 0.0f, 0.0f };

const float GameEngineMath::PI = 3.14159265358979323846264338327950288419716939937510f;
const float GameEngineMath::PI2 = PI * 2.0f;

// 라디안이 디그리
const float GameEngineMath::R2D = 180.0f / GameEngineMath::PI;
const float GameEngineMath::D2R = GameEngineMath::PI / 180.0f;






// 설명 :
class GameEngineWindowTexture
{
	friend class GDIPlusInit;

private:
	static ULONG_PTR Token;
	static Gdiplus::GdiplusStartupInput Input;

public:
	// constrcuter destructer
	GameEngineWindowTexture();
	~GameEngineWindowTexture();

	// delete Function
	GameEngineWindowTexture(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture(GameEngineWindowTexture&& _Other) noexcept = delete;
	GameEngineWindowTexture& operator=(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture& operator=(GameEngineWindowTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);
	void ResCreate(HDC  _ImageDC) 
	{
		ImageDC = _ImageDC;
		ScaleCheck();
	}

	void ResCreate(const float4& _Scale);


	HDC GetImageDC() 
	{
		return ImageDC;
	}

	float4 GetScale();

	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos);
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale);

	void TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, int _TransColor = RGB(255, 0, 255));

	// 반투명용 카피
	// void AlphaCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale);

	// 회전용 카피
	void PlgCopy(GameEngineWindowTexture* _CopyTexture, GameEngineWindowTexture* _MaskTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, float _Angle);

	//반투명카피
	void AlphaCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, unsigned char _Alpha);

	unsigned int GetColor(unsigned int _DefaultColor, float4 _Pos);

	void FillTexture(unsigned int _Color);

protected:

private:
	HBITMAP BitMap;
	HBITMAP OldBitMap;
	HDC ImageDC;

	BITMAP Info;

	void ScaleCheck();
};

