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
// GameEngineMath Ŭ������ float4 Ŭ����, GameEngineRact Ŭ����
class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;

	static const float D2R;
	static const float R2D;

	// 3.14 => 180��
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

	// �Ǽ��� �⺻������ == �� ���� �Ұ����ϴ�. 
	// �ص� ��Ȯ���� �ʴ´�. �Ǽ��� ó���ϴ� ����� ���ʿ� ��Ȯ���� �ʱ� �����̴�.
	// �ε��Ҽ��� ������� �⺻������ ������ ������ �ְ�
	// + - ���� �Ҷ� �����е��� �������� �ٸ� ���� ������ ���ɼ��� ����. 
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
		// ���̸� 1�� ����� �Լ��Դϴ�.
		float Len = Size();

		if (0.0f == Len)
		{
			// MsgBoxAssert("0���� �������� �߽��ϴ�.");
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
		float Value = X * X + Y * Y; // == ���� * ����

		// �������̴�.
		// ������ Ǯ� �������̶�� �մϴ�.
		Value; // ���� * ���� => ����

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

		// ���� ������ ������ �ȴ�. = acosf(AngleVector.X);

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
		// cosf(_Rad)�������� ���� 1�϶��� cosf���� �������ϴ�.
		// sinf(_Rad)�������� ���� 1�϶��� sinf���� �������ϴ�.
		// => ������ ���̰� 1�϶��� ����� ���´�.

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

// ������ ��׸�
const float GameEngineMath::R2D = 180.0f / GameEngineMath::PI;
const float GameEngineMath::D2R = GameEngineMath::PI / 180.0f;






// ���� :
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

	// ������� ī��
	// void AlphaCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale);

	// ȸ���� ī��
	void PlgCopy(GameEngineWindowTexture* _CopyTexture, GameEngineWindowTexture* _MaskTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, float _Angle);

	//������ī��
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

