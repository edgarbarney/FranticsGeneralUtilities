// FranticDreamer 2022
#pragma once

// TODO?: Implement Operations for C Strings

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
		inline std::string Absolute(const std::string& _str);
		inline void FlipSignRef(std::string& _str);
		inline void AbsoluteRef(std::string& _str);

		// Sometimes str.size() doesn't return the right value
		// because of the negative sign.
		inline size_t GetDigitCount(const std::string& _str);

		// Is A (_str1) greater than B (_str2) ?
		inline bool GreaterThan(const std::string& _str1, const std::string& _str2);
		// Is A (_str1) greater than or equal to B (_str2) ?
		inline bool GreaterThanOrEqualTo(const std::string& _str1, const std::string& _str2);
		// Is A (_str1) less than B (_str2) ?
		inline bool LessThan(const std::string& _str1, const std::string& _str2);
		// Is A (_str1) less than or equal to B (_str2) ?
		inline bool LessThanOrEqualTo(const std::string& _str1, const std::string& _str2);

		inline std::string Max(const std::string& _str1, const std::string& _str2);
		inline std::string Min(const std::string& _str1, const std::string& _str2);

		// Operations

		//_str1 + _str2
		inline std::string Add(std::string _str1, std::string _str2);
		//_str1 - _str2
		inline std::string Subtract(std::string _str1, std::string _str2);
		//_str1 * _str2
		inline std::string Multiply(std::string _str1, std::string _str2);

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

		std::string Absolute(const std::string& _str)
		{
			std::string retStr = _str;

			if (IsPositive(_str))
				return retStr;
			
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

		void AbsoluteRef(std::string& _str)
		{
			if (IsPositive(_str))
				return;

			_str.erase(0, 1);
		}

		// Sometimes str.size() doesn't return the right value
		// because of the negative sign.
		size_t GetDigitCount(const std::string& _str)
		{
			return IsPositive(_str) ? _str.size() : _str.size() - 1;
		}

		// Is A (_str1) greater than B (_str2) ?
		bool GreaterThan(const std::string& _str1, const std::string& _str2)
		{
			// Positive one is always greater
			if (IsPositive(_str1) != IsPositive(_str2))
				return IsPositive(_str1);

			if (GetDigitCount(_str1) != GetDigitCount(_str2))
				return GetDigitCount(_str1) > GetDigitCount(_str2); // str.size() would work but just in case

			for (size_t i = !IsPositive(_str1); i < GetDigitCount(_str1); i++)
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

			if (GetDigitCount(_str1) != GetDigitCount(_str2))
				return GetDigitCount(_str1) > GetDigitCount(_str2); // str.size() would work but just in case

			for (size_t i = !IsPositive(_str1); i < GetDigitCount(_str1); i++)
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

		bool LessThan(const std::string& _str1, const std::string& _str2)
		{
			return !GreaterThanOrEqualTo(_str1, _str2);
		}

		bool LessThanOrEqualTo(const std::string& _str1, const std::string& _str2)
		{
			return !GreaterThan(_str1, _str2);
		}

		std::string Max(const std::string& _str1, const std::string& _str2)
		{
			if (GreaterThan(_str1, _str2))
				return _str1;

			return _str2;
		}

		std::string Min(const std::string& _str1, const std::string& _str2)
		{
			if (LessThan(_str1, _str2))
				return _str1;

			return _str2;
		}

		std::string Add(std::string _str1, std::string _str2)
		{
			bool isPositive = !(GreaterThan(Absolute(_str1), Absolute(_str2)) && !IsPositive(_str1));

			// Do subtraction if signs are different
			if (IsPositive(_str1) != IsPositive(_str2))
			{
					std::string retStr = Subtract(Max(Absolute(_str1), Absolute(_str2)), Min(Absolute(_str1), Absolute(_str2)));
					return isPositive ? retStr : FlipSign(retStr);
			}
			
			// Signs are not different, so we can get just one's sign
			isPositive = IsPositive(_str1);

			AbsoluteRef(_str1); 
			AbsoluteRef(_str2);

			std::string finalStr = "";

			uint8_t left = 0;
			uint8_t tempDigitAdd = 0;

			std::string* bigStrPtr = std::max(GetDigitCount(_str1), GetDigitCount(_str2)) == GetDigitCount(_str1) ? &_str1 : &_str2;
			std::string* smolStrPtr = std::max(GetDigitCount(_str1), GetDigitCount(_str2)) == GetDigitCount(_str1) ? &_str2 : &_str1;

			// Add leading zeroes to the "smaller" string
			std::ostringstream ss;
			ss << std::setw(std::max(GetDigitCount(_str1), GetDigitCount(_str2))) << std::setfill('0') << *smolStrPtr;
			*smolStrPtr = ss.str();

			// Reverse both strings
			std::reverse(_str1.begin(), _str1.end());
			std::reverse(_str2.begin(), _str2.end());

			for (size_t i = 0; i < GetDigitCount(_str1); i++)
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

			// Add sign if needed then return
			return isPositive ? finalStr : finalStr.insert(0, 1, negativeChar);
		}

		std::string Subtract(std::string _str1, std::string _str2)
		{
			bool isPositive = !(GreaterThan(Absolute(_str1), Absolute(_str2)) && !IsPositive(_str1));

			// Do addition if signs are different
			if (IsPositive(_str1) != IsPositive(_str2))
			{
				std::string retStr = Add(Max(Absolute(_str1), Absolute(_str2)), Min(Absolute(_str1), Absolute(_str2)));
				return isPositive ? retStr : FlipSign(retStr);
			}

			// Signs are not different, so we can get just one's sign
			isPositive = IsPositive(_str1);

			if (LessThan(Absolute(_str1), Absolute(_str2)))
			{
				std::swap(_str1, _str2);
				isPositive = !isPositive;
			}

			AbsoluteRef(_str1);
			AbsoluteRef(_str2);

			std::string finalStr = "";

			uint8_t need = 0;
			uint8_t tempDigitSubt = 0;

			std::string* bigStrPtr = std::max(GetDigitCount(_str1), GetDigitCount(_str2)) == GetDigitCount(_str1) ? &_str1 : &_str2;
			std::string* smolStrPtr = std::max(GetDigitCount(_str1), GetDigitCount(_str2)) == GetDigitCount(_str1) ? &_str2 : &_str1;

			// Add leading zeroes to the "smaller" string
			std::ostringstream ss;
			ss << std::setw(std::max(GetDigitCount(_str1), _str2.size())) << std::setfill('0') << *smolStrPtr;
			*smolStrPtr = ss.str();

			// Reverse both strings
			std::reverse(_str1.begin(), _str1.end());
			std::reverse(_str2.begin(), _str2.end());

			for (size_t i = 0; i < GetDigitCount(_str1); i++)
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

			// Remove leading zeroes
			finalStr.erase(0, std::min(finalStr.find_first_not_of('0'), finalStr.size() - 1));

			// Add sign if needed then return
			return isPositive ? finalStr : finalStr.insert(0, 1, negativeChar);
		}

		std::string Multiply(std::string _str1, std::string _str2)
		{
			bool isPositive = IsPositive(_str1) == IsPositive(_str2);

			AbsoluteRef(_str1);
			AbsoluteRef(_str2);

			uint8_t left = 0;
			uint8_t tempDigitMult = 0;

			std::string resultaddend1;

			std::string* bigStrPtr = std::max(GetDigitCount(_str1), GetDigitCount(_str2)) == GetDigitCount(_str1) ? &_str1 : &_str2;
			std::string* smolStrPtr = std::max(GetDigitCount(_str1), GetDigitCount(_str2)) == GetDigitCount(_str1) ? &_str2 : &_str1;

			// Add leading zeroes to the "smaller" string
			std::ostringstream ss;
			ss << std::setw(std::max(GetDigitCount(_str1), GetDigitCount(_str2))) << std::setfill('0') << *smolStrPtr;
			*smolStrPtr = ss.str();

			// Reverse both strings
			std::reverse(_str1.begin(), _str1.end());
			std::reverse(_str2.begin(), _str2.end());

			// std::vector???
			std::string* addends = new std::string[GetDigitCount(_str1)];

			for (size_t i = 0; i < GetDigitCount(_str2); i++) // Multiplicator Digits
			{
				// Append X zeroes for allignment
				addends[i].insert(0, i, '0');

				for (size_t k = 0; k < GetDigitCount(_str1); k++) // Multiplicand Digits
				{
					tempDigitMult = left + ((_str1[k] - '0') * (_str2[i] - '0'));

					if (tempDigitMult >= 10)
						left = (tempDigitMult % 100) / 10; /* Tens */
					else
						left = 0;

					// Prepend digit
					addends[i].insert(0, 1, (tempDigitMult % 10) /* Ones */ + '0');

					// Last left digit if any
					if (k == GetDigitCount(_str1) - 1 && left != 0)
						addends[i].insert(0, 1, left + '0');

					// Reset Temp Vars except left
					tempDigitMult = 0;
				}
			}

			std::string finalResult = "0";

			for (size_t i = 0; i < GetDigitCount(_str1); i++)
			{
				finalResult = Add(finalResult, addends[i]);
			}

			delete[] addends;

			// Remove leading zeroes
			finalResult.erase(0, std::min(finalResult.find_first_not_of('0'), finalResult.size() - 1));

			// Add sign if needed then return
			return isPositive ? finalResult : finalResult.insert(0, 1, negativeChar);
		}
	};
};

#endif


//#endif