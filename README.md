## Setup
Steps needed to setup the environment
1. Install `arduino-cli` and `make`
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

## Build
The provided script `build.sh` contains most useful commands.
You can specify additional arguments after the subcommand.

You can run `./build.sh compile` to only compile the code, without uploading.

Run `./build.sh upload <port>` to compile and upload the code to the board.
You can retrieve the port by connecting the board to your computer and running `arduino-cli board list`.
