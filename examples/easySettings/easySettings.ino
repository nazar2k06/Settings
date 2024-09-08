#include <Settings.h>

#define SETTINGS_BUFFER_SIZE 100

char buffer[SETTINGS_BUFFER_SIZE];
int int_value = 100;
float float_value = -12.138;
bool bool_value = true;
const char* string = "stars in the sky";
int array[6] = {12, 13, 34, 12, 23, 2};

void setup() {
  int int_value_read = 0;
  float float_value_read = 0;
  bool bool_value_read = 0;
  char string_read[100] = "";
  int array_read[6];

  Serial.begin(9600);

  /* --- saving settings --- */
  setParameter(buffer, "code1", int_value);
  setParameter(buffer, "code2", float_value);
  setParameter(buffer, "code3", bool_value);
  setParameter(buffer, "code4", (const char*) string);
  setParameter(buffer, "code5", array, 6);
  /* --- saving settings --- */

  Serial.println("Saved.");
  Serial.println(buffer);

  /* --- reading settings --- */
  getParameter(buffer, "code1", &int_value_read);
  getParameter(buffer, "code2", &float_value_read);
  getParameter(buffer, "code3", &bool_value_read);
  getParameter(buffer, "code4", string_read, 100);
  getParameter(buffer, "code5", array_read, 6);
  /* --- reading settings --- */

  Serial.println("\nRead.");
  Serial.println(String("int_value_read: ") + int_value_read);
  Serial.println(String("float_value_read: ") + float_value_read);
  Serial.println(String("bool_value_read: ") + bool_value_read);
  Serial.println(String("string_read: ") + string_read);
  Serial.println("array_read: ");
  for (uint8_t i = 0;i < 6;i++) {
    Serial.print(array_read[i]);
    Serial.print(" ");
  }
}

void loop() {

}
