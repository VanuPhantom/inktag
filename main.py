from machine import Pin

builtin_led = Pin(15, Pin.OUT)

builtin_led.value(1)
