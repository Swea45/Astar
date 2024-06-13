#pragma once
#include <cmath>
#include <cassert>
namespace CommonUtilities
{
	template<class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;
		
		Vector3<T>();   

		Vector3<T>(const T& aX, const T& aY, const T& aZ);  

		Vector3<T>(const Vector3<T>& aVector) = default;

		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;

		~Vector3<T>() = default;
		T LengthSqr() const;
		T Length() const;

		Vector3<T> GetNormalized() const;
		void Normalize();

		T Dot(const Vector3<T>& aVector) const;

		Vector3<T> Cross(const Vector3<T>& aVector) const;
	};

	template <class T>
	Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> calc{ aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z };
		return calc; 
	}
	template <class T>
	void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}

	template <class T>
	Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> calc{ aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z };
		return calc; 
	}
	template <class T>
	void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0 = aVector0 - aVector1;
	}

	template <class T>
	Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		Vector3<T> calc{ aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar };
		return calc;
	}
	template <class T>
	Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		Vector3<T> calc{ aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar };
		return calc;
	}
	template <class T>
	Vector3<T> operator*(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> calc{ aVector0.x * aVector1.x, aVector0.y * aVector1.y, aVector0.z * aVector1.z };
		return calc;
	}
	template <class T>
	void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector = aScalar * aVector;
	}

	template <class T>
	Vector3<T> operator/(const Vector3<T>& aVector, T& aScalar)
	{
		assert(aScalar != 0 && "Scalar can't be 0");
		Vector3<T> calc{ aVector.x / aScalar, aVector.y / aScalar, aVector.z / aScalar };
		return calc; 
	}
	template <class T>
	void operator/=(Vector3<T>& aVector, const  T& aScalar)
	{
		assert(aScalar != 0 && "Scalar can't be 0");
		Vector3<T> calc{ aVector.x / aScalar, aVector.y / aScalar, aVector.z / aScalar };
		aVector = calc;
	}

	template<class T>
	inline Vector3<T>::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	template<class T>
	inline Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template<class T>
	inline T Vector3<T>::LengthSqr() const
	{
		T calc = (x * x) + (y * y) + (z * z);  
		return calc;
	}

	template<class T>
	inline T Vector3<T>::Length() const
	{
		T calc = static_cast<T>(sqrt(static_cast<double>(LengthSqr())));
		return calc;
	}

	template<class T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		if (Length() != 0)
		{
			T length = Length();
			Vector3<T> calc(x / length, y / length, z / length);
			return calc;
		}
		else
		{
			Vector3<T> calc(0, 0, 0);
			return calc;
		}
	}

	template<class T>
	inline void Vector3<T>::Normalize()
	{
		if (Length() != 0)
		{
			T length = Length();
			x = x / length;
			y = y / length;
			z = z / length;
		}
	}

	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		T calc = x * aVector.x + y * aVector.y + z * aVector.z;
		return calc;
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		Vector3<T> calc(y * aVector.z - z * aVector.y, z * aVector.x - x * aVector.z, x * aVector.y - y * aVector.x);
		return calc;
	}

}