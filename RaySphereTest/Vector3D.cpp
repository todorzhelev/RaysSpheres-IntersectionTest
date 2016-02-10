#include"Vector3D.h"

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D::Vector3D()
{
#ifdef INTRINSICS
	reg.m_reg128 = _mm_set_ps(0, 0, 0, 0);
#else
	x = y = z = 0;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D::Vector3D(float _x, float _y, float _z, float _w)
{
#ifdef INTRINSICS
	//it should be in this order z,y,x,w
	reg.m_reg128 = _mm_set_ps(_z,_y,_x,_w);
#else
	x = _x;
	y = _y;
	z = _z;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator - (const Vector3D& other) const
{
	Vector3D temp;
#ifdef INTRINSICS
	temp.reg.m_reg128 = _mm_sub_ps(reg.m_reg128, other.reg.m_reg128);
#else
	temp.x = x - other.x;
	temp.y = y - other.y;
	temp.z = z - other.z;
#endif
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator += (const Vector3D& other)
{
#ifdef INTRINSICS
	__m128 temp = _mm_sub_ps(reg.m_reg128, other.reg.m_reg128);

	reg.m_reg128 = temp;
#else
	x += other.x;
	y += other.y;
	z += other.z;
#endif
	return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator + (const Vector3D& other) const
{
	Vector3D temp;
#ifdef INTRINSICS
	temp.reg.m_reg128 = _mm_add_ps(reg.m_reg128, other.reg.m_reg128);
#else
	temp.x = x + other.x;
	temp.y = y + other.y;
	temp.z = z + other.z;
#endif
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator*(float scalar) const
{
	Vector3D temp;
#ifdef INTRINSICS
	temp.reg.m_reg128 = _mm_mul_ps(reg.m_reg128, _mm_set_ps(scalar, scalar, scalar, scalar));
#else
	temp.x = x * scalar;
	temp.y = y * scalar;
	temp.z = z * scalar;
#endif
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator / (float scalar) const
{
	Vector3D temp;
#ifdef INTRINSICS
	temp.reg.m_reg128 = _mm_div_ps(reg.m_reg128, _mm_set_ps(scalar, scalar, scalar, scalar));
#else
	temp.x = x / scalar;
	temp.y = y / scalar;
	temp.z = z / scalar;
#endif
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

Vector3D operator*(float scalar, const Vector3D& vec)
{
	Vector3D temp;
#ifdef INTRINSICS
	temp.reg.m_reg128 = _mm_mul_ps(vec.reg.m_reg128, _mm_set_ps(scalar, scalar, scalar, scalar));
#else
	temp.x = vec.x * scalar;
	temp.y = vec.y * scalar;
	temp.z = vec.z * scalar;
#endif
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////

float DotProduct(const Vector3D& vec1, const Vector3D& vec2)
{
	float result;
#ifdef INTRINSICS
	__m128 r1 = _mm_mul_ps(vec1.reg.m_reg128, vec2.reg.m_reg128);

	//horizontal add - (0,3,35,16)+(0,3,35,16) = (3,51,3,51)
	__m128 r2 = _mm_hadd_ps(r1, r1);
	__m128 r3 = _mm_hadd_ps(r2, r2);

	//gets the result. it should be in all the components of the register
	//so we just get the first one
	_mm_store_ss(&result, r3);
#else
	result = vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
#endif
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& stream, const Vector3D& vec)
{
	stream.precision(3);

#ifdef INTRINSICS
	stream << std::fixed << "(" << vec.reg.m_reg128.m128_f32[1] << "," << vec.reg.m_reg128.m128_f32[2] << "," << vec.reg.m_reg128.m128_f32[3] << ")";
#else
	stream << std::fixed << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
#endif
	return stream;
}

////////////////////////////////////////////////////////////////////////////////////////////

float Vector3D::LengthSqr() const
{
	float length;
#ifdef INTRINSICS
	__m128 temp = _mm_mul_ps(reg.m_reg128, reg.m_reg128);

	__m128 r2 = _mm_hadd_ps(temp, temp);
	__m128 r3 = _mm_hadd_ps(r2, r2);

	_mm_store_ss(&length, r3);
#else
	length = x*x + y*y + z*z;
#endif
	return length;
}

////////////////////////////////////////////////////////////////////////////////////////////

float Vector3D::Length() const
{
	float length;
#ifdef INTRINSICS
	__m128 temp = _mm_mul_ps(reg.m_reg128, reg.m_reg128);

	__m128 r2 = _mm_hadd_ps(temp, temp);
	__m128 r3 = _mm_hadd_ps(r2, r2);

	r3 = _mm_sqrt_ps(r3);

	_mm_store_ss(&length, r3);
#else
	length = x*x + y*y + z*z;
	length = sqrt(length);
#endif
	return length;
}

////////////////////////////////////////////////////////////////////////////////////////////

void Vector3D::Normalize()
{
	float length = Length();
#ifdef INTRINSICS
	reg.m_reg128 = _mm_div_ps(reg.m_reg128, _mm_set_ps(length, length, length, length));
#else
	x /= length;
	y /= length;
	z /= length;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////

float Vector3D::GetX()
{
#ifdef INTRINSICS
	return reg.m_reg128.m128_f32[1];
#else
	return x;
#endif
}

float Vector3D::GetY()
{
#ifdef INTRINSICS
	return reg.m_reg128.m128_f32[2];
#else
	return y;
#endif
}

float Vector3D::GetZ()
{
#ifdef INTRINSICS
	return reg.m_reg128.m128_f32[3];
#else
	return z;
#endif
}
//float Vector3D::Distance(const Vector3D& vec) const
//{
//	return sqrt((x - vec.x)*(x - vec.x) + (y - vec.y)*(y - vec.y) + (z - vec.z)*(z - vec.z));
//}

////////////////////////////////////////////////////////////////////////////////////////////