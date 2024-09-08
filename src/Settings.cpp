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

#include "Settings.h"

 /* --- Function to save parameters --- */
bool setParameter(char* buffer, String code, const char* string) {
	if (buffer == NULL) {
		return false;
	}

	deleteParameter(buffer, code);

	strcat(buffer, code.c_str());
	strcat(buffer, ":<");
	strcat(buffer, string);
	strcat(buffer, ">\n");

	return true;
}


/* --- Function for reading parameters --- */
bool getParameter(char* buffer, String code, char* string, uint16_t size) {
	char* parameter_begin = searchParameter(buffer, code);

	if (parameter_begin == NULL || string == NULL) {
		return false;
	}

	parameter_begin += code.length() + 2;

	while (*parameter_begin != '>' && size > 1) {
		*string = *parameter_begin;

		parameter_begin++;
		string++;
		size--;

		yield();
	}

	*string = 0;
	return true;
}


/* --- Functions to manage parameters --- */
bool deleteParameter(char* buffer, String code) {
	if (buffer == NULL) {
		return false;
	}

	char* parameter_begin = searchParameter(buffer, code);
	char* parameter_end = NULL;

	if (parameter_begin == NULL) {
		return false;
	}

	parameter_end = strchr(parameter_begin, '\n');
	if (parameter_end == NULL) {
		return false;
	}

	strcpy(parameter_begin, parameter_end + 1);
	return true;
}

char* searchParameter(char* buffer, String code) {
	if (buffer == NULL) {
		return NULL;
	}

	char* array_to_search = (char*)calloc(code.length() + 3, sizeof(char));
	char* pointer = NULL;

	if (array_to_search == NULL) {
		return NULL;
	}

	strcat(array_to_search, code.c_str());
	strcat(array_to_search, ":<");

	pointer = strstr(buffer, array_to_search);
	free(array_to_search);

	if (pointer == NULL) {
		return NULL;
	}

	return (strstr(pointer, ">\n") == NULL) ? NULL : pointer;
}