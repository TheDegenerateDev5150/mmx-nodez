/*
 * bytes_t.hpp
 *
 *  Created on: Dec 2, 2021
 *      Author: mad
 */

#ifndef INCLUDE_MMX_BYTES_T_HPP_
#define INCLUDE_MMX_BYTES_T_HPP_

#include <array>
#include <vector>
#include <string>
#include <cstdint>

#include <vnx/Variant.hpp>
#include <vnx/Hash64.hpp>


namespace mmx {

template<size_t N>
class bytes_t {
public:
	static constexpr size_t size_ = N;

	std::array<uint8_t, N> bytes = {};

	bytes_t() = default;

	bytes_t(const std::vector<uint8_t>& data);

	bytes_t(const std::array<uint8_t, N>& data);

	bytes_t(const void* data, const size_t num_bytes);

	explicit bytes_t(const std::string& str);

	uint8_t* data();

	const uint8_t* data() const;

	size_t size() const;

	bool is_zero() const;

	vnx::Hash64 crc64() const;

	std::string to_string() const;

	std::vector<uint8_t> to_vector() const;

	void from_string(const std::string& str);

	template<typename T>
	T to_uint(const bool big_endian = false) const;

	template<typename T>
	bytes_t<N>& from_uint(T value, const bool big_endian = false);

	uint8_t& operator[](size_t i) {
		return bytes[i];
	}
	const uint8_t& operator[](size_t i) const {
		return bytes[i];
	}

	bool operator==(const bytes_t& other) const {
		return bytes == other.bytes;
	}

	bool operator!=(const bytes_t& other) const {
		return bytes != other.bytes;
	}

};


template<size_t N>
bytes_t<N>::bytes_t(const void* data, const size_t num_bytes)
{
	if(num_bytes != N) {
		throw std::logic_error("bytes_t(): length mismatch ("
				+ std::to_string(num_bytes) + " != " + std::to_string(N) + ")");
	}
	::memcpy(bytes.data(), data, num_bytes);
}

template<size_t N>
bytes_t<N>::bytes_t(const std::vector<uint8_t>& data)
	:	bytes_t(data.data(), data.size())
{
}

template<size_t N>
bytes_t<N>::bytes_t(const std::array<uint8_t, N>& data)
	:	bytes_t(data.data(), data.size())
{
}

template<size_t N>
bytes_t<N>::bytes_t(const std::string& str)
{
	const auto tmp = vnx::from_hex_string(str);
	if(tmp.size() != N) {
		throw std::logic_error("bytes_t(std::string&): length mismatch ("
				+ std::to_string(tmp.size()) + " != " + std::to_string(N) + ")");
	}
	::memcpy(bytes.data(), tmp.data(), N);
}

template<size_t N>
uint8_t* bytes_t<N>::data() {
	return bytes.data();
}

template<size_t N>
const uint8_t* bytes_t<N>::data() const {
	return bytes.data();
}

template<size_t N>
size_t bytes_t<N>::size() const {
	return N;
}

template<size_t N>
bool bytes_t<N>::is_zero() const {
	return *this == bytes_t();
}

template<size_t N>
template<typename T>
T bytes_t<N>::to_uint(const bool big_endian) const
{
	T out = T();
	for(size_t i = 0; i < N; ++i) {
		out <<= 8;
		if(big_endian) {
			out |= bytes[i];
		} else {
			out |= bytes[N - i - 1];
		}
	}
	return out;
}

template<size_t N>
template<typename T>
bytes_t<N>& bytes_t<N>::from_uint(T value, const bool big_endian)
{
	for(size_t i = 0; i < N; ++i) {
		if(big_endian) {
			bytes[N - i - 1] = value;
		} else {
			bytes[i] = value;
		}
		value >>= 8;
	}
	return *this;
}

template<size_t N>
std::string bytes_t<N>::to_string() const {
	return vnx::to_hex_string(bytes.data(), bytes.size(), false, false);
}

template<size_t N>
vnx::Hash64 bytes_t<N>::crc64() const {
	return vnx::Hash64(bytes.data(), bytes.size());
}

template<size_t N>
std::vector<uint8_t> bytes_t<N>::to_vector() const {
	return std::vector<uint8_t>(bytes.begin(), bytes.end());
}

template<size_t N>
void bytes_t<N>::from_string(const std::string& str) {
	*this = bytes_t<N>(str);
}

template<size_t N>
bool operator<(const bytes_t<N>& lhs, const bytes_t<N>& rhs) {
	return ::memcmp(lhs.data(), rhs.data(), N) < 0;
}

template<size_t N>
bool operator>(const bytes_t<N>& lhs, const bytes_t<N>& rhs) {
	return ::memcmp(lhs.data(), rhs.data(), N) > 0;
}

template<size_t N>
std::ostream& operator<<(std::ostream& out, const bytes_t<N>& bytes) {
	return out << bytes.to_string();
}

template<size_t N, size_t M>
bytes_t<N + M> operator+(const bytes_t<N>& lhs, const bytes_t<M>& rhs) {
	bytes_t<N + M> res;
	::memcpy(res.data(), lhs.data(), N);
	::memcpy(res.data() + N, rhs.data(), M);
	return res;
}

template<size_t N>
std::vector<uint8_t> operator+(const std::vector<uint8_t>& lhs, const bytes_t<N>& rhs) {
	auto res = lhs;
	res.insert(res.end(), rhs.bytes.begin(), rhs.bytes.end());
	return res;
}

template<size_t N>
std::vector<uint8_t> operator+(const bytes_t<N>& lhs, const std::vector<uint8_t>& rhs) {
	auto res = lhs.to_vector();
	res.insert(res.end(), rhs.begin(), rhs.end());
	return res;
}

template<size_t N>
std::vector<uint8_t> operator+(const std::string& lhs, const bytes_t<N>& rhs) {
	std::vector<uint8_t> res(lhs.begin(), lhs.end());
	res.insert(res.end(), rhs.bytes.begin(), rhs.bytes.end());
	return res;
}

template<size_t N>
std::vector<uint8_t> operator+(const bytes_t<N>& lhs, const std::string& rhs) {
	auto res = lhs.to_vector();
	res.insert(res.end(), rhs.begin(), rhs.end());
	return res;
}

} // mmx


namespace vnx {

template<size_t N>
void read(vnx::TypeInput& in, mmx::bytes_t<N>& value, const vnx::TypeCode* type_code, const uint16_t* code) {
	switch(code[0]) {
		case CODE_STRING:
		case CODE_ALT_STRING: {
			std::string tmp;
			vnx::read(in, tmp, type_code, code);
			try {
				value.from_string(tmp);
			} catch(...) {
				value = mmx::bytes_t<N>();
			}
			break;
		}
		case CODE_UINT64:
		case CODE_ALT_UINT64: {
			uint64_t tmp = 0;
			vnx::read(in, tmp, type_code, code);
			value.from_uint(tmp);
			break;
		}
		case CODE_DYNAMIC:
		case CODE_ALT_DYNAMIC: {
			vnx::Variant tmp;
			vnx::read(in, tmp, type_code, code);
			if(tmp.is_string()) {
				try {
					value.from_string(tmp.to<std::string>());
				} catch(...) {
					value = mmx::bytes_t<N>();
				}
			} else {
				tmp.to(value.bytes);
			}
			break;
		}
		default:
			vnx::read(in, value.bytes, type_code, code);
	}
}

template<size_t N>
void write(vnx::TypeOutput& out, const mmx::bytes_t<N>& value, const vnx::TypeCode* type_code = nullptr, const uint16_t* code = nullptr) {
	vnx::write(out, value.bytes, type_code, code);
}

template<size_t N>
void read(std::istream& in, mmx::bytes_t<N>& value) {
	std::string tmp;
	vnx::read(in, tmp);
	value.from_string(tmp);
}

template<size_t N>
void write(std::ostream& out, const mmx::bytes_t<N>& value) {
	vnx::write(out, value.to_string());
}

template<size_t N>
void accept(vnx::Visitor& visitor, const mmx::bytes_t<N>& value) {
	visitor.visit(value.data(), value.size());
}

} // vnx

#endif /* INCLUDE_MMX_BYTES_T_HPP_ */
