/*
 * Library: Settings
 *
 * Description: Short library to store settings.
 *
 * Author: Vereshchynskyi Nazar
 * Email: verechnazar12@gmail.com
 * Version: 1.0.0
 * Date: 08.09.2024
 */

#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "Arduino.h"

/* --- Max length of the number in the form of a string --- */
#define MAX_VALUE_ARRAY_LEN 20

/* --- Functions to save parameters --- */
template <typename T>
bool setParameter(char* buffer, String code, T value);
template <typename T>
bool setParameter(char* buffer, String code, T* array, uint16_t size);
bool setParameter(char* buffer, String code, const char* string);

/* --- Functions for reading parameters --- */
template <typename T>
bool getParameter(char* buffer, String code, T* variable);
template <typename T>
bool getParameter(char* buffer, String code, T* array, uint16_t size);
bool getParameter(char* buffer, String code, char* string, uint16_t size);

/* --- Functions to manage parameters --- */
bool deleteParameter(char* buffer, String code);
char* searchParameter(char* buffer, String code);


/* --- Functions to save parameters --- */
template <typename T>
bool setParameter(char* buffer, String code, T value) {
	if (buffer == NULL) {
		return false;
	}

	char value_array[MAX_VALUE_ARRAY_LEN + 1] = "";
	deleteParameter(buffer, code);

	strcat(buffer, code.c_str());
	strcat(buffer, ":<");

	sprintf(value_array, "%.2f", (double)value);

	strcat(buffer, value_array);
	strcat(buffer, ">\n");

	return true;
}
template <typename T>
bool setParameter(char* buffer, String code, T* array, uint16_t size) {
	if (buffer == NULL) {
		return false;
	}

	char value_array[MAX_VALUE_ARRAY_LEN + 1] = "";
	deleteParameter(buffer, code);

	strcat(buffer, code.c_str());
	strcat(buffer, ":<");
	
	for (uint16_t i = 0; i < size; i++) {
		*value_array = 0;

		sprintf(value_array, "%.2f", (double)array[i]);
		strcat(buffer, value_array);

		if (i != size - 1) {
			strcat(buffer, ":");
		}

		yield();
	}

	strcat(buffer, ">\n");
	return true;
}


/* --- Functions for reading parameters --- */
template <typename T>
bool getParameter(char* buffer, String code, T* variable) {
	char* parameter_begin = searchParameter(buffer, code);

	if (parameter_begin == NULL) {
		return false;
	}
	
	parameter_begin += code.length() + 2;
	if (!isdigit(*parameter_begin) && *parameter_begin != '-') {
		return false;
	}

	*variable = (T) atof(parameter_begin);
	return true;
}
template <typename T>
bool getParameter(char* buffer, String code, T* array, uint16_t size) {
	char* parameter_begin = searchParameter(buffer, code);
	uint16_t array_index = 0;

	if (parameter_begin == NULL) {
		return false;
	}

	parameter_begin += code.length() + 1;

	while (*parameter_begin != '>' && array_index != size) {
		parameter_begin++;
		if (!isdigit(*parameter_begin) && *parameter_begin != '-') {
			return false;
		}

		array[array_index] = strtod(parameter_begin, &parameter_begin);
		array_index++;

		yield();
	}

	return true;
}

#endif