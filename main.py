def load_configuration():
    with open("configuration.json", "r") as config_file:
        from json import load

        return load(config_file)

configuration = load_configuration()

from machine import Pin

builtin_led = Pin(15, Pin.OUT)
builtin_led.value(1)

def connect_to_wifi():
    global builtin_led, configuration
    import network
    from time import sleep

    sta_if = network.WLAN(network.STA_IF)
    sta_if.active(True)

    attempts = 5
    
    while not sta_if.isconnected() and attempts > 0:
        try:
            builtin_led.value(not builtin_led.value())
            sta_if.connect(configuration["wifi"]["ssid"], configuration["wifi"]["password"])
        except OSError as error:
            print(str(error))
            attempts -= 1
            print(f"Failed connection attempt {5 - attempts}")
            sleep(1)

    builtin_led.value(1)

