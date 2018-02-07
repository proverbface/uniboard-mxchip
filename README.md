# uniboard-mxchip
`UniboardMXChip` is a [Uniboard](https://uniboard.io) client library for MXChip, the Microsoft [Azure IoT DevKit](https://microsoft.github.io/azure-iot-developer-kit/) device.
With `UniboardMXChip`, sending data to Uniboard system through HTTP or MQTT protocol would be pretty easy and simple.
Due to chip restriction, all code is contained in one `UniboardMXChip.h` file.

## Usage
Include `UniboardMXChip.h` and create a client object:
```c
#include "UniboardMXChip.h"

// Pass token when creating client object. The token is used for client authentication and can be found in Uniboard's Settings tab.
UniboardMXChip mxClient("25f6db34-9ff1-47f4-b7bb-000000fb2e23");

// If the device does not need authentication, just omit the token.
UniboardMXChip mxClient;
```

Send data through HTTP protocol (HTTPS is not supported):
```c
// clientObject.http(<deviceId>, <dataString>);
mxClient.http("59db5cd3d6000000cb346b0b", "{\"temp\":21.2, \"humidity\":29.8}");
```

Send data through MQTT protocol:
```c
// clientObject.connectMQTT();
// clientObject.mqtt(<deviceTopic>, <dataString>);
bool mqttConnected = mxClient.connectMQTT()==0;
if (mqttConnected) {
    mxClient.mqtt("/data_api/device/59db5cd3d6000000cb346b0b", "{\"temp\":21.2, \"humidity\":29.8}");
}
```

## License
(The MIT License)

Copyright (c) 2018 Chuan Shao &lt;shaochuancs@gmail.com&gt;
