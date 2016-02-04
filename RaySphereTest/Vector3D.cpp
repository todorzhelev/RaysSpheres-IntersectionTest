#include"Vector3D.h"

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D::Vector3D()
{
	m_reg128 = _mm_set_ps(0, 0, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D::Vector3D(float _x, float _y, float _z, float _w)
{
	m_reg128 = _mm_set_ps(_z,_y,_x,_w);
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator - (const Vector3D& other) const
{
	Vector3D temp;
	temp.m_reg128 = _mm_sub_ps(m_reg128, other.m_reg128);

	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator += (const Vector3D& other)
{
	__m128 temp = _mm_sub_ps(m_reg128, other.m_reg128);

	m_reg128 = temp;

	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator + (const Vector3D& other) const
{
	Vector3D temp;
	temp.m_reg128 = _mm_add_ps(m_reg128, other.m_reg128);

	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator*(float scalar) const
{
	Vector3D temp;
	temp.m_reg128 = _mm_mul_ps(m_reg128, _mm_set_ps(scalar, scalar, scalar, scalar));
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator / (float scalar) const
{
	Vector3D temp;
	temp.m_reg128 = _mm_div_ps(m_reg128, _mm_set_ps(scalar, scalar, scalar, scalar));
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

float Vector3D::Length() const
{
	//this should be also checked
	const int mask = 0x55;

	__m128 res = _mm_dp_ps(m_reg128, m_reg128, mask);
	res = _mm_sqrt_ps(res);
	return res.m128_f32[0];
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::Normalize() const
{
	Vector3D temp;
	float length = Length();

	temp.m_reg128 = _mm_div_ps(m_reg128, _mm_set_ps(length, length, length, length));

	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

//float Vector3D::Distance(const Vector3D& vec) const
//{
//	return sqrt((x - vec.x)*(x - vec.x) + (y - vec.y)*(y - vec.y) + (z - vec.z)*(z - vec.z));
//}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D operator*(float scalar, const Vector3D& vec)
{
	Vector3D temp;
	temp.m_reg128 = _mm_mul_ps(vec.m_reg128, _mm_set_ps(scalar, scalar, scalar, scalar));
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

float DotProduct(const Vector3D& vec1, const Vector3D& vec2)
{
	const int mask = 0x55;
	//TODO: check if this is valid
	__m128 res = _mm_dp_ps(vec1.m_reg128, vec2.m_reg128, mask);
	return res.m128_f32[0];
}

////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& stream, const Vector3D& vec)
{
	//TODO: check this also
	stream << "(" << vec.m_reg128.m128_f32[0] << "," << vec.m_reg128.m128_f32[1] << "," << vec.m_reg128.m128_f32[2] << ")";

	return stream;
}

////////////////////////////////////////////////////////////////////////////////////////////