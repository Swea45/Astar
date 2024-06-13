#pragma once
#include <cmath>
#include <cassert>
namespace CommonUtilities
{
	template<class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;

		Vector4<T>();

		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);

		Vector4<T>(const Vector4<T>& aVector) = default;

		Vector4<T>& operator=(const Vector4<T>& aVector3) = default;

		~Vector4<T>() = default;
		T LengthSqr() const;
		T Length() const;

		Vector4<T> GetNormalized() const;
		void Normalize();

		T Dot(const Vector4<T>& aVector) const;
	};

	template <class T>
	Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> calc{ aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z, aVector0.w + aVector1.w};
		return calc;
	}
	template <class T>
	void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}

	template <class T>
	Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> calc{ aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z, aVector0.w - aVector1.w };
		return calc;
	}
	template <class T>
	void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0 = aVector0 - aVector1;
	}

	template <class T>
	Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		Vector4<T> calc{ aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar, aVector.w * aScalar };
		return calc;
	}
	template <class T>
	Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		Vector4<T> calc{ aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar , aVector.w * aScalar};
		return calc;
	}
	template <class T>
	Vector4<T> operator*(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> calc{ aVector0.x * aVector1, aVector0.y * aVector1.y, aVector0.z * aVector1.z, aVector0.w * aVector1.w };
		return calc;
	}
	template <class T>
	void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector = aScalar * aVector;
	}

	template <class T>
	Vector4<T> operator/(const Vector4<T>& aVector, T& aScalar)
	{
		assert(aScalar != 0 && "Scalar can't be 0");
		Vector4<T> calc{ aVector.x / aScalar, aVector.y / aScalar, aVector.z / aScalar, aVector.w / aScalar};
		return calc;
	}
	template <class T>
	void operator/=(Vector4<T>& aVector, const  T& aScalar)
	{
		assert(aScalar != 0 && "Scalar can't be 0");
		Vector4<T> calc{ aVector.x / aScalar, aVector.y / aScalar, aVector.z / aScalar, aVector.w / aScalar };
		aVector = calc;
	}

	template<class T>
	inline Vector4<T>::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template<class T>
	inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}

	template<class T>
	inline T Vector4<T>::LengthSqr() const
	{
		T calc = (x * x) + (y * y) + (z * z) + (w * w);
		return calc;
	}

	template<class T>
	inline T Vector4<T>::Length() const
	{
		T calc = static_cast<T>(sqrt(static_cast<double>(LengthSqr())));
		return calc;
	}

	template<class T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		if (Length() != 0)
		{
			T length = Length();
			Vector4<T> calc(x / length, y / length, z / length, w / length);
			return calc;
		}
		else
		{
			Vector4<T> calc(0, 0, 0, 0);
			return calc;
		}
	}

	template<class T>
	inline void Vector4<T>::Normalize()
	{
		if (Length() != 0)
		{
			T length = Length();
			x = x / length;
			y = y / length;
			z = z / length;
			w = w / length;
		}
	}
	template<class T>
	inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		T calc = x * aVector.x + y * aVector.y + z * aVector.z + w * aVector.w;
		return calc;
	}
}