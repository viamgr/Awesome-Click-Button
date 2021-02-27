# Arduino awesome click button
Handle click on a button with useful functions.

Simple Usage: 

```c++
#include "AwesomeClickButton.h"
#define BUTTON_PIN 2


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

## APIs

```c++
void setSingleClickTime(int value);
 
void setMultipleClickTime(int value);
 
void setLongClickTime(int value);
 
void setDebounceTime(int value);
 
void setOnClickListener(OnClickListener listener);

void setOnMultiClickListener(OnMultiClickListener listener);

void setOnLongClickListener(OnLongClickListener listener);

void setOnPressingListener(OnPressingListener listener);

void setOnClickingListener(OnClickingListener listener);

void setOnWaitForClickListener(OnWaitForClickListener listener);
```
