#include"Vector3D.h"

Vector3D::Vector3D() :x(0), y(0), z(0)
{}

Vector3D::Vector3D(float _x, float _y, float _z) :x(_x), y(_y), z(_z)
{}

Vector3D Vector3D::operator - (const Vector3D& other) const
{
	Vector3D temp;
	temp.x = x - other.x;
	temp.y = y - other.y;
	temp.z = z - other.z;

	return temp;
}

Vector3D Vector3D::operator += (const Vector3D& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3D Vector3D::operator + (const Vector3D& other) const
{
	return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator*(float scalar) const
{
	Vector3D temp;
	temp.x = scalar*x;
	temp.y = scalar*y;
	temp.z = scalar*z;

	return temp;
}

Vector3D Vector3D::operator / (float scalar) const
{
	Vector3D temp;
	temp.x = x / scalar;
	temp.y = y / scalar;
	temp.z = z / scalar;

	return temp;
}

float Vector3D::Length() const
{
	return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::Normalize() const
{
	Vector3D temp(x, y, z);
	float length = temp.Length();
	temp.x /= length;
	temp.y /= length;
	temp.z /= length;

	return temp;
}

float Vector3D::Distance(const Vector3D& vec) const
{
	return sqrt((x - vec.x)*(x - vec.x) + (y - vec.y)*(y - vec.y) + (z - vec.z)*(z - vec.z));
}

Vector3D operator*(float scalar, const Vector3D& vec)
{
	Vector3D temp;
	temp.x = scalar*vec.x;
	temp.y = scalar*vec.y;
	temp.z = scalar*vec.z;

	return temp;
}

float DotProduct(const Vector3D& vec1, const Vector3D& vec2)
{
	return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}

std::ostream& operator<<(std::ostream& stream, const Vector3D& vec)
{
	stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";

	return stream;
}