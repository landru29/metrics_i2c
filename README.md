# Push Data to OVH metrics timeseries (via I2C)

## Prerequisite

* Have a WEMOS D1 Mini
* Have a sane installation of Arduino IDE
* Have WEMOS toolkit installed (<https://github.com/esp8266/Arduino>)

## Hardware

* Wemos D1 Mini
* Other arduino (for master)

## Arduino

* Create a file `config.h` based on `config.h.sample`
* Compile program

## config.h

The file shold contain the following definition:

```c
#define TOKEN "put the 'write' token in graphana topic in the manager"

#define OPENTSDB_HOST "the host of your metrics plateform (ie 'opentsdb.gra1.metrics.ovh.net')"

#define WARP10_HOST "the host of your metrics plateform (ie 'warp10.gra1.metrics.ovh.net')"

#define FINGERPRINT "XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX"
```

The token is the write token you created in the OVH manager (Cloud > metrics): <https://www.ovh.com/manager/cloud/#/>

## Fingerprint

in `http.cpp`, you must check to have the correct fingerprint:

```bash
echo | openssl s_client -showcerts -servername opentsdb.gra1.metrics.ovh.net -connect opentsdb.gra1.metrics.ovh.net:443 2>/dev/null | openssl x509 -noout -fingerprint -sha1 -inform pem | sed -e "s/.*=//g" | sed -e "s/\:/ /g"
```

## VSCode

Install `Arduino` extension

Create file `.vscode/c_cpp_properties.json`

```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${env:HOME}/Arduino/hardware/esp8266com/esp8266/variants/d1_mini",
                "${env:HOME}/Arduino/hardware/esp8266com/esp8266/**",
                "${env:HOME}/.arduino15/packages/esp8266/hardware/esp8266/2.5.2/libraries/**",
                "${env:HOME}/Arduino/libraries/**",
            ],
            "forcedInclude": [],
            "intelliSenseMode": "gcc-x64",
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c11",
            "cppStandard": "c++17"
        }
    ],
    "version": 4
}
```

Create file `.vscode/arduino.json`

```json
{
    "board": "esp8266com:esp8266:d1_mini",
    "configuration": "xtal=80,vt=flash,exception=legacy,ssl=all,eesz=4M2M,ip=lm2f,dbg=Disabled,lvl=None____,wipe=none,baud=921600",
    "sketch": "four_a_pain_metrics.ino",
    "port": "/dev/ttyUSB0"
}
```

## Slave

Wemos will be the slave. Compile the program and load it in the Wemos. Connect I2C to Master:

* Clock: `D1`
* Data: `D2`

## Master

Include `communication.h` in your code. In your setup, just put:

```cpp
Wire.begin()
```

Then you can use the class `MetricsClient`

Do not forget to connect I2C to the slave:

* Clock: `A5`
* Data: `A4`
