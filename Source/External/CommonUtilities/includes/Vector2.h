#pragma once
#include <cmath>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

namespace CommonUtilities
{
	template<class T>
	class Vector2
	{
	public:
		T x; 
		T y; 

		Vector2<T>();

		Vector2<T>(const T& aX, const T& aY);

		Vector2<T>(const Vector2<T>& aVector) = default;

		Vector2<T>& operator=(const Vector2<T>& aVector2) = default;

		~Vector2<T>() = default;
		
		T LengthSqr() const;
		T Length() const;

		Vector2<T> GetNormalized() const;
		void Normalize();

		T Dot(const Vector2<T>& aVector) const;

	};

	template <class T>
	Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> calc{ aVector0.x + aVector1.x, aVector0.y + aVector1.y};
		return calc;
	}
	template <class T>
	void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}

	template <class T>
	Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> calc{ aVector0.x - aVector1.x, aVector0.y - aVector1.y };
		return calc;
	}
	template <class T>
	void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0 = aVector0 - aVector1;
	}

	template <class T>
	Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		Vector2<T> calc{ aVector.x * aScalar, aVector.y * aScalar};
		return calc;
	}
	template <class T>
	Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		Vector2<T> calc{ aVector.x * aScalar, aVector.y * aScalar};
		return calc;
	}
	template <class T>
	Vector2<T> operator*(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> calc{ aVector0.x * aVector1.x, aVector0.y * aVector1.y };
		return calc;
	}
	template <class T>
	void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector = aScalar * aVector;
	}

	template <class T>
	Vector2<T> operator/(const Vector2<T>& aVector, T& aScalar)
	{
		assert(aScalar != 0 && "Scalar can't be 0");
		Vector2<T> calc{ aVector.x / aScalar, aVector.y / aScalar};
		return calc;
	}
	template <class T>
	void operator/=(Vector2<T>& aVector, const  T& aScalar)
	{
		assert(aScalar != 0 && "Scalar can't be 0");
		Vector2<T> calc{ aVector.x / aScalar, aVector.y / aScalar };
		aVector = calc;
	}

	template <class T>
	bool operator == (const Vector2<T>& aVectorOne, const Vector2<T> aVectorTwo) 
	{
		return (aVectorOne.x == aVectorTwo.x && aVectorOne.y == aVectorTwo.y); 
	}

	template <class T>
	bool operator != (const Vector2<T>& aVectorOne, const Vector2<T> aVectorTwo)
	{
		return (aVectorOne.x != aVectorTwo.x || aVectorOne.y != aVectorTwo.y);
	}
	
	template <class T>
	bool operator<(const Vector2<T>& aVectorOne, const Vector2<T> aVectorTwo)
	{
		return (aVectorOne.x + aVectorOne.y) < (aVectorTwo.x + aVectorTwo.y);
	}

	template<class T>
	inline Vector2<T>::Vector2() : Vector2(0, 0)
	{
	}

	template<class T>
	inline Vector2<T>::Vector2(const T& aX, const T& aY) : x(aX), y(aY)
	{
	}

	template<class T>
	inline T Vector2<T>::LengthSqr() const
	{
		T calc = (x * x) + (y * y);
		return calc;
	}

	template<class T>
	inline T Vector2<T>::Length() const
	{
		T calc = static_cast<T>(sqrt(static_cast<double>(LengthSqr())));
		return calc;
	}

	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		if (Length() != 0)
		{
			T length = Length();
			Vector2<T> calc(x / length, y / length);
			return calc;
		}
		else
		{
			Vector2<T> calc(0, 0);
			return calc;
		}
	}

	template<class T>
	inline void Vector2<T>::Normalize()
	{
		if (Length() != 0)
		{
			T length = Length();
			x = x / length;
			y = y / length;

		}
	}

	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		T calc = x * aVector.x + y * aVector.y;
		return calc;
	}
}

template<> struct std::hash<CommonUtilities::Vector2<float>>
{
	std::size_t operator()(const CommonUtilities::Vector2<float> aPos) const noexcept
	{
		return std::hash<int>()((int)aPos.x ^ ((int)aPos.y << 16));
	}
};