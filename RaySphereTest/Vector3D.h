#pragma once
#include<math.h>
#include<iostream>

struct Vector3D
{
	Vector3D();

	Vector3D(float _x, float _y, float _z);

	Vector3D operator-(const Vector3D& other) const;

	Vector3D operator+=(const Vector3D& other);

	Vector3D operator+(const Vector3D& other) const;

	Vector3D operator*(float scalar) const;

	Vector3D operator/(float scalar) const;

	float Length() const;

	Vector3D Normalize() const;

	float Distance(const Vector3D& vec) const;

	friend std::ostream& operator<<(std::ostream& stream, const Vector3D& vec);
	friend Vector3D operator*(float scalar, const Vector3D& vec);

	float x, y, z;
};

float DotProduct(const Vector3D& vec1, const Vector3D& vec2);
std::ostream& operator<<(std::ostream& stream, const Vector3D& vec);