# README:



## <u>About</u>

This project is meant to be an kinetic sculpture, utilizing a servo and stepper motor. The sculpture itself has 2 parts, the spaceship as well as the battle over a lego "power reactor. For the spaceship, I built it from scratch and it has a functioning full-auto brickshooter that the user can control via a push button as well as the given API. Next to the spaceship is a power plant where a mini fighter is flying overhead while 2 lego minfigues (one flying) fights another.

## <u>Installation/Setup</u>

### Program Installations

1. Clone this github repo

   ```
   git clone https://github.com/bnhwa/Kinetic-Art.git
   ```

   

3. Arduino needs to be installed. Go [here](https://www.arduino.cc/en/software) to download the latest version. Open the Arduino IDE and follow the instructions [here](https://randomnerdtutorials.com/getting-started-with-esp32/) to configure Arduino for the ESP32 and download the ESP32 board configuration. Once this is done, select board "ESP32 Wrover module." Once this is done, download the following libraries:

   [ESP-32 Async library](https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip)

   [Async TCP library](https://github.com/me-no-dev/AsyncTCP/archive/master.zip)

4. After downloading these libraries in .zip form, go in the Arduino IDE and go to `Sketch->Include Library->Add .zip Library`  and select all 3 of the above libraries that you just downloaded.


### Program Setup 

1. Open the Arduino IDE, modify the `ssid_Router` and `password_Router` fields within `kinetic_diorama.ino`

   

## <u>Running</u>

1. Connect the controller USB to the ESP32 unit
2. Open the Arduino IDE, upload `kinetic_diorama.ino` esp32 board; voila!

