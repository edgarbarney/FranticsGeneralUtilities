// FranticDreamer 2022
#pragma once

#ifdef _INC_STRING // C String Header. For strlen etc.

#include <limits>

namespace FranUtils
{
	// TODO: Simplify and finish this part. C String part is a bit messy. Because I
	// Wrote this code at 2 AM and I ignored some personal barriers because
	// I was soo sleepy. And I'm a bit lazy to fix a half-joke idea anyway.
	//
	// Cursed String Maths for C Strings. Its mostly unsafe.
	namespace CStringMaths
	{
		// UNUSED - Default Buffer Size for return arrays
		//constexpr size_t defaultBufferSize = 128;

		inline void Add(const char* _str1, const char* _str2, char* _out)
		{
			uint8_t left = 0;

			uint8_t tempDigitAdd = 0;
			char tempCharDigit = 0;

			size_t str1len = std::strlen(_str1);
			size_t str2len = std::strlen(_str2);

			size_t greatestLen = std::max(str1len, str2len);

			// We'll fill the shorter string with leading zeroes

			// Allocate new strings
			char* str1 = new char[greatestLen + 1];
			char* str2 = new char[greatestLen + 1];

			int iter = 0;
			const char* iterchr = _str1;
			const char* iterchr2 = _str2;

			while (*iterchr != '\0')
			{
				if (greatestLen == str1len)
				{
					str1[iter] = *iterchr;
					iterchr++;

					if (iter >= (greatestLen - str2len))
					{
						str2[iter] = *iterchr2;
						iterchr2++;
					}
					else
						str2[iter] = '0'; // Add Leading Zeroes
				}
				else
				{
					str2[iter] = *iterchr2;
					iterchr2++;

					if (iter >= (greatestLen - str1len))
					{
						str1[iter] = *iterchr;
						iterchr++;
					}
					else
						str1[iter] = '0'; // Add Leading Zeroes
				}

				iter++;
			}
			str1[iter] = str2[iter] = '\n'; // Don't forget to null terminate strings;

			for (size_t i = greatestLen - 1; i != std::numeric_limits<size_t>::max(); i--)
			{
				tempDigitAdd = left + (str1[i] - '0') + (str2[i] - '0');

				if (tempDigitAdd >= 10)
					left = (tempDigitAdd % 100) / 10; /* Tens */
				else
					left = 0;

				// Append digit
				tempCharDigit = (tempDigitAdd % 10) /* Ones */ + '0';
				std::strncat(_out, &tempCharDigit, 1);

				// Reset Temp Vars except left
				tempDigitAdd = 0;
			}

			// Remove heap strings
			delete[] str1;
			delete[] str2;

			// Add last left digit if any
			if (left != 0)
			{
				tempCharDigit = left + '0';
				std::strncat(_out, &tempCharDigit, 1);
			}

			// Reverse the result string
			size_t finalStrLen = strlen(_out);
			for (size_t i = 0; i < finalStrLen / 2; i++)
			{
				char tempChar = _out[i];
				_out[i] = _out[finalStrLen - i - 1];
				_out[finalStrLen - i - 1] = tempChar;
			}
		}
	};
};

#endif

#ifdef _STRING_ // C++ String Header.

#include <iomanip>
#include <sstream>

namespace FranUtils
{
	// Cursed String Maths for Standard Strings.
	namespace StringMaths
	{
		constexpr char negativeChar = '-';


		// ============
		// Declarations
		// ============

		// Does string (_str) contain a positive value ?
		inline bool IsPositive(const std::string& _str);

		inline std::string FlipSign(const std::string& _str);
		inline void FlipSignRef(std::string& _str);

		// Sometimes str.size() doesn't return the right value
		// because of the negative sign.
		inline size_t GetDigits(const std::string& _str);

		// Is A (_str1) greater than B (_str2) ?
		inline bool GreaterThan(const std::string& _str1, const std::string& _str2);

		// Is A (_str1) greater than or equal to B (_str2) ?
		inline bool GreaterThanOrEqualTo(const std::string& _str1, const std::string& _str2);

		inline std::string Subtract(std::string _str1, std::string _str2);
		inline std::string Add(std::string _str1, std::string _str2);

		// ============
		// Definitions
		// ============

		// Does string (_str) contain a positive value ?
		bool IsPositive(const std::string& _str)
		{
			return _str[0] != negativeChar;
		}

		std::string FlipSign(const std::string& _str)
		{
			std::string retStr = _str;

			if (IsPositive(_str))
				retStr.insert(0, 1, negativeChar);
			else
				retStr.erase(0, 1);

			return retStr;
		}

		void FlipSignRef(std::string& _str)
		{
			if (IsPositive(_str))
				_str.insert(0, 1, negativeChar);
			else
				_str.erase(0, 1);
		}

		// Sometimes str.size() doesn't return the right value
		// because of the negative sign.
		size_t GetDigits(const std::string& _str)
		{
			return !IsPositive(_str) ? _str.size() - 1 : _str.size();
		}

		// Is A (_str1) greater than B (_str2) ?
		bool GreaterThan(const std::string& _str1, const std::string& _str2)
		{
			// Positive one is always greater
			if (IsPositive(_str1) != IsPositive(_str2))
				return IsPositive(_str1);

			if (_str1.size() != _str2.size())
				return GetDigits(_str1) > GetDigits(_str2); // str.size() would work but just in case

			for (size_t i = !IsPositive(_str1); i < GetDigits(_str1); i++)
			{
				if (_str1[i] == _str2[i])
					continue;

				if (_str1[i] > _str2[i])
					return true;

				return false;
			}

			// Strings are equal
			return false;
		}

		// Is A (_str1) greater than or equal to B (_str2) ?
		bool GreaterThanOrEqualTo(const std::string& _str1, const std::string& _str2)
		{
			// Positive one is always greater
			if (IsPositive(_str1) != IsPositive(_str2))
				return IsPositive(_str1);

			if (_str1.size() != _str2.size())
				return GetDigits(_str1) > GetDigits(_str2); // str.size() would work but just in case

			for (size_t i = !IsPositive(_str1); i < GetDigits(_str1); i++)
			{
				if (_str1[i] == _str2[i])
					continue;

				if (_str1[i] > _str2[i])
					return true;

				return false;
			}

			// Strings are equal
			return true;
		}

		std::string Add(std::string _str1, std::string _str2)
		{
			if (IsPositive(_str1) != IsPositive(_str2))
				if (IsPositive(_str1))
					return Subtract(_str1, FlipSign(_str2));
				else
					return Subtract(FlipSign(_str1), _str2);

			std::string finalStr = "";

			uint8_t left = 0;
			uint8_t tempDigitAdd = 0;

			std::string* bigStrPtr = std::max(GetDigits(_str1), GetDigits(_str2)) == GetDigits(_str1) ? &_str1 : &_str2;
			std::string* smolStrPtr = std::max(GetDigits(_str1), GetDigits(_str2)) == GetDigits(_str1) ? &_str2 : &_str1;

			// Add leading zeroes to the "smaller" string
			std::ostringstream ss;
			ss << std::setw(std::max(GetDigits(_str1), GetDigits(_str2))) << std::setfill('0') << *smolStrPtr;
			*smolStrPtr = ss.str();

			// Reverse both strings
			std::reverse(_str1.begin(), _str1.end());
			std::reverse(_str2.begin(), _str2.end());

			for (size_t i = 0; i < GetDigits(_str1) - !IsPositive(_str1); i++)
			{
				tempDigitAdd = left + (_str1[i] - '0') + (_str2[i] - '0');

				if (tempDigitAdd >= 10)
					left = (tempDigitAdd % 100) / 10; /* Tens */
				else
					left = 0;

				// Prepend digit
				finalStr.insert(0, 1, (tempDigitAdd % 10) /* Ones */ + '0');

				// Reset Temp Vars except left
				tempDigitAdd = 0;
			}

			// Add last left digit if any
			if (left != 0)
			{
				finalStr.insert(0, 1, left + '0');
			}

			return finalStr;
		}

		std::string Subtract(std::string _str1, std::string _str2)
		{
			std::string finalStr = "";

			uint8_t need = 0;
			uint8_t tempDigitSubt = 0;

			std::string* bigStrPtr = std::max(GetDigits(_str1), GetDigits(_str2)) == GetDigits(_str1) ? &_str1 : &_str2;
			std::string* smolStrPtr = std::max(GetDigits(_str1), GetDigits(_str2)) == GetDigits(_str1) ? &_str2 : &_str1;

			// Add leading zeroes to the "smaller" string
			std::ostringstream ss;
			ss << std::setw(std::max(GetDigits(_str1), _str2.size())) << std::setfill('0') << *smolStrPtr;
			*smolStrPtr = ss.str();

			// Reverse both strings
			std::reverse(_str1.begin(), _str1.end());
			std::reverse(_str2.begin(), _str2.end());

			for (size_t i = 0; i < GetDigits(_str1) - !IsPositive(_str1); i++)
			{
				uint8_t ch1 = (_str1[i] - '0');
				uint8_t ch2 = (_str2[i] - '0') + need;

				if (ch1 < ch2)
				{
					tempDigitSubt = 10 - (ch2 - ch1);
					need = 1;
				}
				else
				{
					tempDigitSubt = ch1 - ch2;
					need = 0;
				}

				// Prepend digit
				finalStr.insert(0, 1, tempDigitSubt + '0');

				// Reset Temp Vars except left
				tempDigitSubt = 0;
			}

			// Remove leading zeroes then return
			return finalStr.erase(0, std::min(finalStr.find_first_not_of('0'), finalStr.size() - 1));
		}
	};
};

#endif


//#endif