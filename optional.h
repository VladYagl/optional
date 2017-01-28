#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <memory>
#include <type_traits>

struct nullopt_t {};
constexpr nullopt_t nullopt;

struct implace_t {};
constexpr implace_t implace;

template <typename T>
struct optional {
	
	optional() : valid(false) {}

	optional(T value) : valid(true) {
		new (&storage) T(std::move(value));
	}

	optional (nullopt_t) : valid(false) {}

	optional (optional const& other) : valid(other.valid) {
		if (valid) {
			new (&storage) T(*other);
		}
	}

	optional (optional && other) : valid(false) {
		if (other) {
			emplace(std::move(*other));
		}
	}

	optional& operator=(optional other) {
		swap(other);
		return *this;
	}

	template <typename ... Args>
	optional(implace_t, Args&& ... args) : valid(true) {
		new (&storage) T(std::forward<Args>(args)...);
	}

	void swap(optional& other) {
		if (valid) {
			if (other.valid) {
				std::swap(storage, other.storage);
			} else {
				other.emplace(**this);
				reset();
			}
		} else {
			if (other.valid) {
				emplace(*other);
				other.reset();
			}
		}
	}

	template <typename ... Args>
	void emplace(Args&& ... args) {
		reset();
		new (&storage) T(std::forward<Args>(args)...);
		valid = true;
	}

	T* operator->() {
		return reinterpret_cast<T*>(&storage);
	}

	T& operator* () {
		return *reinterpret_cast<T*>(&storage);
	}

	const T& operator* () const {
		return *reinterpret_cast<T const*>(&storage);
	}

	const T* operator-> () const {
		return reinterpret_cast<T const*>(&storage);
	}

	T value_or(T&& default_value) {
		if (valid) {
			return **this;
		} else {
			return std::move(default_value);
		}
	}

	void reset() {
		if (valid) {
			reinterpret_cast<T*>(&storage)->~T();
			valid = false;
		}
	}

	~optional() {
		reset();
	}

	explicit operator bool() const {
		return valid;
	}

	friend bool operator==(optional const& a, optional const& b) {
		if (!a && !b) {
			return true;
		} else if (a && b) {
			return *a == *b;
		} else {
			return false;
		}
	}

	friend bool operator!=(optional const& a, optional const& b) {
		return !(a == b);
	}

	friend bool operator<(optional const& a, optional const& b) {
		if (a) {
			if (b) {
				return *a < *b;
			} else {
				return false;
			}
		} else {
			if (b) {
				return true;
			} else {
				return false;
			}
		}
	}
	
	friend bool operator<=(optional const& a, optional const& b) {
		return a < b || a == b;
	}
	
	friend bool operator>(optional const& a, optional const& b) {
		return b < a;
	}
	
	friend bool operator>=(optional const& a, optional const& b) {
		return !(a < b);
	}

private: 
	typename std::aligned_storage<sizeof(T), alignof(T)>::type storage;
	bool valid;
};

template <typename T, typename ... Args>
optional<T> make_optional(Args&& ...args) {
	return optional<T> (implace, std::forward<Args>(args)...);
}


#endif // OPTIONAL_H