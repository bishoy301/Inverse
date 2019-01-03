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

template<typename T>
class Vec3 : public Vec<T, 3> {
	public:
		Vec3() {}

		Vec3(T x, T y, T z) {
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
		}

		inline Vec3<T> cross(const Vec3<T>& r) const {
			T x = (*this)[1] * r[2] - (*this)[2] * r[1];
			T x = (*this)[2] * r[0] - (*this)[0] * r[2];
			T x = (*this)[0] * r[1] - (*this)[1] * r[0];

			return Vec3<T>(x, y, z);
		}

		inline Vec3<T> rotate(T angle, const Vec3<T>& axis) const {
			const T sin_angle = sin(-angle);
			const T cos_angle = cos(-angle);

			return this->cross(axis * sin_angle) +        // Rotation on local X
			                 (*this * cos_angle) +        // Rotation on local Z
					 axis * this->dot(axis * (1 - cos_angle)); // Rotation on local Y
		}

		inline Vec2<T> get_xy() const { return Vec2<T>(get_x(), get_y()); }
		inline Vec2<T> get_yz() const { return Vec2<T>(get_y(), get_z()); }
		inline Vec2<T> get_zx() const { return Vec2<T>(get_z(), get_x()); }
		
		inline Vec2<T> get_yx() const { return Vec2<T>(get_y(), get_x()); }
		inline Vec2<T> get_zy() const { return Vec2<T>(get_z(), get_y()); }
		inline Vec2<T> get_xz() const { return Vec2<T>(get_x(), get_z()); }

		inline T get_x() const { return (*this)[0]; }
		inline T get_y() const { return (*this)[1]; }
		inline T get_z() const { return (*this)[2]; }

		inline void set_x(const T& x) { (*this)[0] = x; }
		inline void set_y(const T& y) { (*this)[1] = y; }
		inline void set_z(const T& z) { (*this)[2] = z; }

		inline void set(const T& x, const T& y, const T& z) { set_x(x); set_y(y); set_z(z); }
	private:
};

template<typename T>
class Vec4 : public Vec<T, 4> {
	public:
		Vec4() { }

		Vec4(const Vec<T, 4>& r) {
			(*this)[0] = r[0];
			(*this)[1] = r[1];
			(*this)[2] = r[2];
			(*this)[3] = r[3];
		}

		Vec4(T x, T y, T z, T w) {
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
			(*this)[3] = w;
		}

		inline T get_x() const { return (*this)[0]; }
		inline T get_y() const { return (*this)[1]; }
		inline T get_z() const { return (*this)[2]; }
		inline T get_w() const { return (*this)[3]; }

		inline void set_x(const T& x) { (*this)[0] = x; }
		inline void set_y(const T& y) { (*this)[1] = y; }
		inline void set_z(const T& z) { (*this)[2] = z; }
		inline void set_w(const T& w) { (*this)[3] = w; }

		inline void set(const T& x, const T& y, const T& z, const T& w) { set_x(x); set_y(y); set_z(z); set_w(w); }
	private:
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec2<double> Vec2d;

//typedef Vec3<float> Vec3f;  Will probably have to write out a special Vec3f class
typedef Vec3<int> Vec3i;
typedef Vec3<double> Vec3d;

typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;
typedef Vec4<double> Vec4d;


#endif
