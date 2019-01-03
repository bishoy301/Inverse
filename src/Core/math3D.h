#ifndef MATH3D_H
#define MATH3D_H

#include <math.h>

#define MATH_PI 3.1415926535897932384626433832795
#define to_radians(x) (float)(((x) * MATH_PI / 180.0f))
#define to_degrees(x) (float)(((x) * 180.0f / MATH_PI))

template<typename T, unsigned int D>
class Vec {
	public:
		Vec() {}

		inline T dot(const Vec<T, D>& r) const {
			T result = T(0);
			for (unsigned int i = 0; i < D; i++) {
				result += (*this)[i] * r[i];
			}

			return result;
		}

		inline Vec<T, D> max(const Vec<T, D>& r) const {
			Vec<T, D> result;
			for (unsigned int i = 0; i < D; i++) {
				result[i] = values[i] > r[i] ? values[i] : r[i];
			}

			return result;
		}

		inline T max() const {
			T max_val = (*this)[0];

			for (int i = 0; i < D; i++) {
				if ((*this)[i] > max_val) {
					max_val = (*this)[i];
				}
			}

			return max_val;
		}

		inline T lenth_sq() const { return this->dot(*this); }
		inline T length() const { return sqrt(lenth_sq()); }
		inline Vec<T, D> normalized() const { return *this / length(); }
		inline Vec<T, D> lerp(const Vec<T, D>& r, T lerp_factor) const {
			return (r - *this) * lerp_factor + *this;
		}

		inline Vec<T, D> reflect(const Vec<T, D>& normal) const {
			return *this - (normal * (this->dot(normal) * 2));
		}

		inline Vec<T, D> operator+(const Vec<T, D>& r) const {
			Vec<T, D> result;
			for (unsigned int i = 0; i < D; i++) {
				result[i] = values[i] + r[i];
			}

			return result;
		}

		inline Vec<T, D> operator-(const Vec<T, D>& r) const {
			Vec<T, D> result;
			for (unsigned int i = 0; i < D; i++) {
				result[i] = values[i] - r[i];
			}

			return result;
		}

		inline Vec<T, D> operator*(const T& r) const {
			Vec<T, D> result;
			for (unsigned int i = 0; i < D; i++) {
				result[i] = values[i] * r;
			}

			return result;
		}

		inline Vec<T, D> operator/(const T& r) const {
			Vec<T, D> result;
			for (unsigned int i = 0; i < D; i++) {
				result[i] = values[i] / r;
			}

			return result;
		}

		inline Vec<T, D> operator+=(const Vec<T, D>& r) const {
			Vec<T, D> result;
			for (unsigned int i = 0; i < D; i++) {
				(*this)[i] = values[i] + r[i];
			}

			return *this;
		}

		inline Vec<T, D> operator-=(const Vec<T, D>& r) const {
			Vec<T, D> result;
			for (unsigned int i = 0; i < D; i++) {
				(*this)[i] = values[i] - r[i];
			}

			return *this;
		}

		inline Vec<T, D> operator*=(const T& r) const {
			Vec<T, D> result;
			for (unsigned int i = 0; i < D; i++) {
				(*this)[i] = values[i] * r;
			}

			return *this;
		}

		inline Vec<T, D> operator/=(const T& r) const {
			Vec<T, D> result;
			for (unsigned int i = 0; i < D; i++) {
				(*this)[i] = values[i] / r;
			}

			return *this;
		}

		T& operator [] (unsigned int i) { return values[i]; }
		T operator [] (unsigned int i) const {return values[i]; }

		inline bool operator==(const Vec<T, D>& r) const {
			for (unsigned int i = 0; i < D; i++) {
				if ((*this)[i] != r[i]) {
					return false;
				}
			}
			
			return true;
		}

		inline bool operator!=(const Vec<T, D>& r) const { return !operator==(r); }

	private:
		T values[D];
};

template<typename T>
class Vec2 : public Vec<T, 2> {
	public:
		Vec2() {}

		Vec2(const Vec<T, D>& r) {
			(*this)[0] = r[0];
			(*this)[1] = r[1];
		}

		Vec2(T x, T y) {
			(*this)[0] = x;
			(*this)[1] = y;
		}

		T cross(const Vec2<T>& r) const {
			return get_x() * r.get_y() - get_y() * r.get_x();
		}

		inline T get_x() const { return (*this)[0]; };
		inline T get_y() const { return (*this)[1]; };

		inline void set_x(const T& x) { (*this)[0] = x; }
		inline void set_y(const T& y) { (*this)[1] = y; }

	private:
};

typedef Vec2<float> Vec2f;

#endif
