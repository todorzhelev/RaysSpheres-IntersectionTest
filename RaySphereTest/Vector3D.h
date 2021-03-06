#pragma once
#include<math.h>
#include<iostream>
#include<xmmintrin.h>
#include "Defines.h"

/////////////////////////////////////////////////////////////////

struct Vector3D
{
	Vector3D();

	Vector3D(float _x, float _y, float _z, float _w = 0.0);

	Vector3D operator-(const Vector3D& other) const;

	Vector3D operator+=(const Vector3D& other);

	Vector3D operator+(const Vector3D& other) const;

	Vector3D operator*(float scalar) const;

	Vector3D operator/(float scalar) const;

	float Length() const;

	float LengthSqr() const;

	void Normalize();

	float GetX();

	float GetY();

	float GetZ();

	//not needed for now
	//float Distance(const Vector3D& vec) const;

	friend std::ostream& operator<<(std::ostream& stream, const Vector3D& vec);
	friend Vector3D operator*(float scalar, const Vector3D& vec);

#ifdef INTRINSICS
	//explicitly align at 16 bytes.
	//union __declspec(align(16))
	union m128
	{
		__m128 m_reg128;
		float values[4];
	} reg;
#else
	float x, y, z;
#endif

};

float DotProduct(const Vector3D& vec1, const Vector3D& vec2);
std::ostream& operator<<(std::ostream& stream, const Vector3D& vec);