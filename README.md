## Build
1. Install `arduino-cli`
2. Initialize config file: `arduino-cli config init`
3. Modify the created config file to contain 
```
board_manager:
  additional_urls:
    - https://dl.espressif.com/dl/package_esp32_index.json
```
4. Update index `arduino-cli update`
5. Install ESP32 board definition `arduino-cli core install esp32:esp32`
6. Install libraries:
    - `arduino-cli lib install PubSubClient`
	- `arduino-cli lib install --zip-path TFT_eSPI.zip`
7. Connect the ESP32 and identify the port with `arduino-cli board list`
8. Compile and upload `arduino-cli -p <port> -b esp32:esp32:esp32doit-devkit-v1 -ut .`
