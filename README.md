# Arduino-Awesome-Click-Button
Handle click on a button with useful functions.

Simple Usage: 

```
#include "AwesomeClickButton.h"
#define BUTTON_PIN D2


AwesomeClickButton awesomeClickButton(BUTTON_PIN);

void onButtonClicked() {
  Serial.println((String)"Single Click Happened" );
}
void onMultiClickListener(int count) {
  Serial.println((String)"onMultiClickListener " + count );
}
void onLongClickListener(int duration) {
  Serial.println((String)"onLongClickListener " + duration );
}

void setup() {
  Serial.begin(115200);
  awesomeClickButton.setOnClickListener(onButtonClicked);
  awesomeClickButton.setOnMultiClickListener(onMultiClickListener);
  awesomeClickButton.setOnLongClickListener(onLongClickListener);
}

void loop() {
  awesomeClickButton.update();
}
```
