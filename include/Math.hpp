#pragma once

#include "Dialogs.hpp"

namespace pMath {

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Vector 4
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	constexpr int VECTOR_4_LENGTH = 4;

	union alignas(16) vec4 {
		float data[4];
		struct {	
			// if it was just variables it would be another 
			// possible member in the union, using struct 
			// they will be read as a group of variables
			float x, y, z, w;
		};

		vec4();
		vec4(const float& a_);
		vec4(const vec4& vec4_);
		vec4(const float& x_, const float& y_, const float& z_, const float& w_);

		// vec4
		void operator=(const vec4& target) noexcept;
		bool operator==(const vec4& target) noexcept;
		vec4 operator+(const vec4& target) noexcept;
		void operator+=(const vec4& target) noexcept;
		vec4 operator-(const vec4& target) noexcept;
		void operator-=(const vec4& target) noexcept;
		vec4 operator*(const vec4& target) noexcept;
		void operator*=(const vec4& target) noexcept;
		vec4 operator/(const vec4& target) noexcept;
		void operator/=(const vec4& target) noexcept;

		// scalar
		void operator=(const float& target) noexcept;
		vec4 operator+(const float& target) noexcept;
		void operator+=(const float& target) noexcept;
		vec4 operator-(const float& target) noexcept;
		void operator-=(const float& target) noexcept;
		vec4 operator*(const float& target) noexcept;
		void operator*=(const float& target) noexcept;
		vec4 operator/(const float& target) noexcept;
		void operator/=(const float& target) noexcept;
	};

	vec4::vec4() {
		x = y = z = w = 0;
	}

	vec4::vec4(const float& x_, const float& y_, const float& z_, const float& w_) {
		x = x_;
		y = y_;
		z = z_;
		w = w_;
	}

	vec4::vec4(const float& a_) {
		x = y = z = w = a_;
	}

	vec4::vec4(const vec4& vec4_) {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] = vec4_.data[i];
		}
	}

	///////////////////////////////////////////////////////////////
	// Vec4

	void vec4::operator=(const vec4& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] = target.data[i];
		}
	};

	bool vec4::operator==(const vec4& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			if (this->data[i] != target.data[i]) {
				return false;
			}
		}
		return true;
	};

	vec4 vec4::operator+(const vec4& target) noexcept {
		vec4 ret = vec4();
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			ret.data[i] = this->data[i] + target.data[i];
		}
		return ret;
	};

	void vec4::operator+=(const vec4& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] += target.data[i];
		}
	};

	vec4 vec4::operator-(const vec4& target) noexcept {
		vec4 ret = vec4();
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			ret.data[i] = this->data[i] - target.data[i];
		}
		return ret;
	};

	void vec4::operator-=(const vec4& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] -= target.data[i];
		}
	};

	vec4 vec4::operator*(const vec4& target) noexcept {
		vec4 ret = vec4();
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			ret.data[i] = this->data[i] * target.data[i];
		}
		return ret;
	};

	void vec4::operator*=(const vec4& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] *= target.data[i];
		}
	};

	vec4 vec4::operator/(const vec4& target) noexcept {
		vec4 ret = vec4();
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			ret.data[i] = this->data[i] / target.data[i];
		}
		return ret;
	};

	void vec4::operator/=(const vec4& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] /= target.data[i];
		}
	};

	///////////////////////////////////////////////////////////////
	// Scalar

	void vec4::operator=(const float& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] = target;
		}
	};

	vec4 vec4::operator+(const float& target) noexcept {
		vec4 ret = vec4();
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			ret.data[i] = this->data[i] + target;
		}
		return ret;
	};

	void vec4::operator+=(const float& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] += target;
		}
	};

	vec4 vec4::operator-(const float& target) noexcept {
		vec4 ret = vec4();
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			ret.data[i] = this->data[i] - target;
		}
		return ret;
	};

	void vec4::operator-=(const float& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] -= target;
		}
	};

	vec4 vec4::operator*(const float& target) noexcept {
		vec4 ret = vec4();
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			ret.data[i] = this->data[i] * target;
		}
		return ret;
	};

	void vec4::operator*=(const float& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] *= target;
		}
	};

	vec4 vec4::operator/(const float& target) noexcept {
		vec4 ret = vec4();
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			ret.data[i] = this->data[i] / target;
		}
		return ret;
	};

	void vec4::operator/=(const float& target) noexcept {
		for (int i = 0; i < VECTOR_4_LENGTH; i++) {
			this->data[i] /= target;
		}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Matrix 4x4
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	constexpr int MATRIX_4X4_SIDE = 4;
	constexpr int MATRIX_4X4_SIZE = 16;

	// Column Major
	union alignas(64) mat4 {
		float mat4a[16];
		float mat4d[4][4];

		mat4();
		mat4(const float& a_);

		// Mat4
		void operator=(const mat4& target) noexcept;
		bool operator==(const mat4& target) noexcept;
		mat4 operator+(const mat4& target) noexcept;
		void operator+=(const mat4& target) noexcept;
		mat4 operator-(const mat4& target) noexcept;
		void operator-=(const mat4& target) noexcept;
		mat4 operator*(const mat4& target) noexcept;
		void operator*=(const mat4& target) noexcept;


		// Scalar
		void operator=(const float& target) noexcept;
		mat4 operator+(const float& target) noexcept;
		void operator+=(const float& target) noexcept;
		mat4 operator-(const float& target) noexcept;
		void operator-=(const float& target) noexcept;
		mat4 operator*(const float& target) noexcept;
		void operator*=(const float& target) noexcept;
		mat4 operator/(const float& target) noexcept;
		void operator/=(const float& target) noexcept;
	};

	mat4::mat4() {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			this->mat4d[i][i] = 1.0f;
		}
	}

	mat4::mat4(const float& a_) {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				this->mat4d[i][j] = a_;
			}
		}
	}

	///////////////////////////////////////////////////////////////
	// Matrix 4x4

	void mat4::operator=(const mat4& target) noexcept {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				this->mat4d[i][j] =  target.mat4d[i][j];
			}
		}
	}

	bool mat4::operator==(const mat4& target) noexcept {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				if (this->mat4d[i][j] != target.mat4d[i][j]) 
					return false;
			}
		}
		return true;
	}

	mat4 mat4::operator+(const mat4& target) noexcept {
		mat4 ret = mat4();
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				ret.mat4d[i][j] = this->mat4d[i][j] + target.mat4d[i][j];
			}
		}
		return ret;
	}

	void mat4::operator+=(const mat4& target) noexcept {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				this->mat4d[i][j] = this->mat4d[i][j] + target.mat4d[i][j];
			}
		}
	}

	mat4 mat4::operator-(const mat4& target) noexcept {
		mat4 ret = mat4();
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				ret.mat4d[i][j] = this->mat4d[i][j] - target.mat4d[i][j];
			}
		}
		return ret;
	}

	void mat4::operator-=(const mat4& target) noexcept {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				this->mat4d[i][j] = this->mat4d[i][j] - target.mat4d[i][j];
			}
		}
	}

	mat4 mat4::operator*(const mat4& target) noexcept {
		mat4 ret;
		float element{0};
		/*
			Linha por coluna. Para A multiplique todos da sua linha por todos da coluna.
			mat4d[Y][X]
		*/
		for (int y = 0; y < MATRIX_4X4_SIDE; y++) {
			// ja percorre todos Y

			for (int x = 0; x < MATRIX_4X4_SIDE; x++) {
				// ja percorre todos da linha do Y

				for (int k = 0; k < MATRIX_4X4_SIDE; k++) {
					 element += this->mat4d[y][k] * target.mat4d[k][x];	// reside no A.
					 
				}
				//logs::errm(std::to_string(element));
				ret.mat4d[y][x] = element;
				element = 0.0f;
			}
		}

		return ret;
	}

	void mat4::operator*=(const mat4& target) noexcept {
		float element{0};

		for (int y = 0; y < MATRIX_4X4_SIDE; y++) {
		// ja percorre todos Y

			for (int x = 0; x < MATRIX_4X4_SIDE; x++) {
				// ja percorre todos da linha do Y

				for (int k = 0; k < MATRIX_4X4_SIDE; k++) {
					element += this->mat4d[y][k] * target.mat4d[k][x];	
					/*
						M1: estamos na linha Y, passamos todos elementos da linha com k
						M2: estamos na coluna X, passamos todos elementos da coluna com k
						Element: soma suas multiplicações.

						Pula pra próxima linha e repete. 
					*/

				}
				//logs::errm(std::to_string(element));
				this->mat4d[y][x] = element;
				element = 0.0f;
			}
		}
	}

	///////////////////////////////////////////////////////////////
	// Scalar

	void mat4::operator=(const float& target) noexcept {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				this->mat4d[i][j] = target;
			}
		}
	}

	mat4 mat4::operator+(const float& target) noexcept {
		mat4 ret = mat4();
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				ret.mat4d[i][j] = this->mat4d[i][j] + target;
			}
		}
		return ret;
	}

	void mat4::operator+=(const float& target) noexcept {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				this->mat4d[i][j] = this->mat4d[i][j] + target;
			}
		}
	}

	mat4 mat4::operator-(const float& target) noexcept {
		mat4 ret = mat4();
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				ret.mat4d[i][j] = this->mat4d[i][j] - target;
			}
		}
		return ret;
	}

	void mat4::operator-=(const float& target) noexcept {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				this->mat4d[i][j] = this->mat4d[i][j] - target;
			}
		}
	}

	mat4 mat4::operator*(const float& target) noexcept {
		mat4 ret;
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				ret.mat4d[i][j] = this->mat4d[i][j] * target;
			}
		}
		return ret;
	}

	void mat4::operator*=(const float& target) noexcept {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				this->mat4d[i][j] = this->mat4d[i][j] * target;
			}
		}
	}

	mat4 mat4::operator/(const float& target) noexcept {
		mat4 ret;
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				ret.mat4d[i][j] = this->mat4d[i][j] / target;
			}
		}
		return ret;
	}

	void mat4::operator/=(const float& target) noexcept {
		for (int i = 0; i < MATRIX_4X4_SIDE; i++) {
			for (int j = 0; j < MATRIX_4X4_SIDE; j++) {
				this->mat4d[i][j] = this->mat4d[i][j] / target;
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Functions
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void rotate(mat4& target, float degree, const vec4& axis) {

	}
	
}

