// FranticDreamer 2022
#pragma once

#include <limits>

namespace FranUtils
{
	// TODO: Simplify this part. C String part is a bit messy. Because I
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
			char* str1 = new char[greatestLen+1];
			char* str2 = new char[greatestLen+1];

			int iter = 0;
			const char* iterchr = _str1;
			const char* iterchr2 = _str2;

			while(*iterchr != '\0')
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
	}
}

//#endif