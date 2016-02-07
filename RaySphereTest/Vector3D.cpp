#include"Vector3D.h"

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D::Vector3D()
{
	m_reg128 = _mm_set_ps(0, 0, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D::Vector3D(float _x, float _y, float _z, float _w)
{
	//it should be in this order z,y,x,w
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

Vector3D operator*(float scalar, const Vector3D& vec)
{
	Vector3D temp;
	temp.m_reg128 = _mm_mul_ps(vec.m_reg128, _mm_set_ps(scalar, scalar, scalar, scalar));
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

float DotProduct(const Vector3D& vec1, const Vector3D& vec2)
{
	float result;
	__m128 r1 = _mm_mul_ps(vec1.m_reg128, vec2.m_reg128);

	//horizontal add - (0,3,35,16)+(0,3,35,16) = (3,51,3,51)
	__m128 r2 = _mm_hadd_ps(r1, r1);
	__m128 r3 = _mm_hadd_ps(r2, r2);

	//gets the result. it should be in all the components of the register
	//so we just get the first one
	_mm_store_ss(&result, r3);

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& stream, const Vector3D& vec)
{
	stream.precision(3);
	stream << "(" << vec.m_reg128.m128_f32[1] << "," << vec.m_reg128.m128_f32[2] << "," << vec.m_reg128.m128_f32[3] << ")";

	return stream;
}

////////////////////////////////////////////////////////////////////////////////////////////

float Vector3D::LengthSqr() const
{
	float length;
	__m128 temp = _mm_mul_ps(m_reg128, m_reg128);

	__m128 r2 = _mm_hadd_ps(temp, temp);
	__m128 r3 = _mm_hadd_ps(r2, r2);

	_mm_store_ss(&length, r3);

	return length;

}

float Vector3D::Length() const
{
	float length;
	__m128 temp = _mm_mul_ps(m_reg128, m_reg128);

	__m128 r2 = _mm_hadd_ps(temp, temp);
	__m128 r3 = _mm_hadd_ps(r2, r2);

	r3 = _mm_sqrt_ps(r3);

	_mm_store_ss(&length, r3);

	return length;
}

////////////////////////////////////////////////////////////////////////////////////////////

void Vector3D::Normalize()
{
	float length = Length();

	m_reg128 = _mm_div_ps(m_reg128, _mm_set_ps(length, length, length, length));
}

////////////////////////////////////////////////////////////////////////////////////////////

//float Vector3D::Distance(const Vector3D& vec) const
//{
//	return sqrt((x - vec.x)*(x - vec.x) + (y - vec.y)*(y - vec.y) + (z - vec.z)*(z - vec.z));
//}

////////////////////////////////////////////////////////////////////////////////////////////