#ifndef AWESOME_CLICK_BUTTON_H
#define AWESOME_CLICK_BUTTON_H
typedef std::function<void()> OnClickListener;
typedef std::function<void(int clickCount)> OnMultiClickListener;
typedef std::function<void(int duration)>   OnLongClickListener;
typedef std::function<void(int duration)>   OnPressingListener;
typedef std::function<void(int clickCount)> OnClickingListener;
typedef std::function<void(int clickCount)> OnWaitForClickListener;

class AwesomeClickButton {
  private:

    byte buttonPin;     // the number of the pushbutton pin

    int buttonState = 0;         // variable for reading the pushbutton status
    int clickCount = 0;
    long lastClickTime = 0;
    long lastDebouceTime = 0;


    int singleClickTime = 500;
    int multipleClickTime = singleClickTime * 2;
    int longClickTime = 1000;
    int debounceTime = 50;


    OnClickListener onClickListener = NULL;
    OnMultiClickListener onMultiClickListener = NULL;
    OnLongClickListener onLongClickListener = NULL;
    OnPressingListener onPressingListener = NULL;
    OnClickingListener onClickingListener = NULL;
    OnWaitForClickListener onWaitForClickListener = NULL;

    void onClickHappened() {
      if (onClickListener != NULL) {
        onClickListener();
      }
    }

    void onMultiClickHappend(int count) {
      if (onMultiClickListener != NULL) {
        onMultiClickListener(count);
      }
    }

    void onLongClickHappened(int duration) {
      if (onLongClickListener != NULL) {
        onLongClickListener(duration);
      }
    }

    void onPressingHappened(int duration) {
      if (onPressingListener != NULL) {
        onPressingListener(duration);
      }
    }
    void onClickingHappened(int clickCount) {
      if (onClickingListener != NULL) {
        onClickingListener(clickCount);
      }
    }
    void onWaitForClickHappened(int clickCount) {
      if (onWaitForClickListener != NULL) {
        onWaitForClickListener(clickCount);
      }
    }
    void resetClick() {
      clickCount = 0;
      lastClickTime = 0;
    }

  public:
    AwesomeClickButton(byte buttonPin) {
      this->buttonPin = buttonPin;
      pinMode(buttonPin, INPUT);
    }

    void setSingleClickTime(int value) {
      singleClickTime = value;
    }

    void setMultipleClickTime(int value) {
      multipleClickTime = value;
    }

    void setLongClickTime(int value) {
      longClickTime = value;
    }

    void setDebounceTime(int value) {
      debounceTime = value;
    }

    void setOnClickListener(OnClickListener listener) {
      onClickListener =  listener;
    }
    void setOnMultiClickListener(OnMultiClickListener listener) {
      onMultiClickListener =  listener;
    }
    void setOnLongClickListener(OnLongClickListener listener) {
      onLongClickListener =  listener;
    }
    void setOnPressingListener(OnPressingListener listener) {
      onPressingListener =  listener;
    }
    void setOnClickingListener(OnClickingListener listener) {
      onClickingListener =  listener;
    }
    void setOnWaitForClickListener(OnWaitForClickListener listener) {
      onWaitForClickListener =  listener;
    }

    void update() {

      if (millis() - lastDebouceTime > debounceTime) {
        lastDebouceTime = millis();

        int currentButtonState = digitalRead(buttonPin);

        if (buttonState != currentButtonState && currentButtonState == HIGH) {
          clickCount++;
          lastClickTime = millis();
          onClickingHappened(clickCount);
        }
        else {
          int deltaTime = millis() - lastClickTime;
          if (currentButtonState == LOW) {
            if (clickCount == 1 && deltaTime > singleClickTime) {
              if (deltaTime > longClickTime) {
                onLongClickHappened((millis() - lastClickTime));
              }
              else {
                onClickHappened();
              }
              resetClick();
            }
            else if (lastClickTime > 0 && deltaTime > multipleClickTime)  {
              onMultiClickHappend(clickCount);
              resetClick();
            } else if (lastClickTime > 0) {
              onWaitForClickHappened(clickCount);
            }
          }
          else {
            if (clickCount == 1)
            {
              onPressingHappened(deltaTime);
            }
            else if (clickCount > 1) {
              onWaitForClickHappened(clickCount);
            }
          }
        }

        // read the state of the pushbutton value:
        buttonState = digitalRead(buttonPin);
      }
    }

};

#endif
