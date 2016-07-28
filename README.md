#Gardener

![Morris Singer's Hydroponic Garden](http://i.imgur.com/YP2dZa3.jpg)

A WIP demonstrating driving [Atlas Scientific](http://www.atlas-scientific.com/) [Industrial pH sensor](http://www.atlas-scientific.com/product_pages/probes/industrial_ph_probe.html) and [EC sensors](http://www.atlas-scientific.com/product_pages/kits/ec_k0_1_kit.html) through a single Arduino via Atlas's [EZO pH circuit](http://www.atlas-scientific.com/product_pages/circuits/ezo_ph.html) and [EZO EC circuit](http://www.atlas-scientific.com/product_pages/circuits/ezo_ec.html).

Also controls a supply valve through which additional nutrient can be released into the garden, a pump through which spent nutrient can be evacuated, as well as a display that can indicate the status of the garden on-premisis.

## Garden Setup
In setup, the device onto which the firmware is loaded sits connected via USB to a Raspberry Pi,
which is the gateway to the Internet. The Pi receives MQTT, WAMP/JSON-RPC, or other commands from
an IoT service in the cloud, from which it then translates and messages to this device.

The hydroponic garden with which I used this software is described in the following diagram:

![Morris Singer's Hydroponic Garden System Diagram](http://i.imgur.com/pqnGeTb.png)

## API

The Arduino is programmed to receive simple serial commands in the following language:

```
ECCALIL
```

Here, the first two characters represent the module (EC sensor, pH sensor, Valve, or Pump), and the next four characters represent a command to perform on that module, and the final character is a parameter, which some commands require and others do not. So, in this example, `EC` refers to the EC sensor module, `CALI` commands the EC sensor circuit to perform a calibration, and the `L` tells the EC sensor circuit that the type of calibration being performed is a calibration against low-conductivity test solution.

The full API is as follows:


Module | Command | Param   | Description                                                             
-------|---------|---------|-------------------------------------------------------------------------
EC     | READ    |         | Read the value of the sensor                                            
EC     | LEDS    | 0       | Turn the LED on the EZO circuit off
EC     | LEDS    | 1       | Turn the LED on the EZO circuit on
EC     | TYPE    | 0       | Set the circuit to read from K=0.1 devices
EC     | TYPE    | 1       | Set the circuit to read from K=1.0 devices
EC     | TYPE    | 2       | Set the circuit to read from K=10.0 devices
EC     | CALI    | D       | Perform a dry calibration
EC     | CALI    | L       | Perform a calibration with low-conductivity calibration solution
EC     | CALI    | H       | Perform a calibration with high-conductivity calibration colution
PH     | READ    |         | Read the value of the sensor
PH     | LEDS    | 0       | Turn the LED on the EZO circuit off
PH     | LEDS    | 1       | Turn the LED on the EZO circuit on
PH     | CALI    | L       | Perform a calibration with low-pH calibration solution
PH     | CALI    | M       | Perform a calibration with mid-level-pH calibration solution
PH     | CALI    | H       | Perform a calibration with high-pH calibration solution
PH     | CALI    | ?       | Read the calibration status
PM     | STRT    |         | Start the drain pump
PM     | STOP    |         | Stop the drain pump
VL     | OPEN    |         | Open the supply valuve
VL     | CLOS    |         | Close the supply valuve

In addition to returning any values as appropriate, commands may return one of the following status codes:

Status  | Description
--------|--------------------------------------------------------------------------------------------------------------------------------|
ERMODU  | An invalid module has been supplied in the first two characters of the command
ERPARA  | An invalid command or parameter has been supplied in the third through sixth or third through seventh characters of the command
ERCOMM  | The gardener was not able to communicate with the specified device
OK      | Worked

There is cruft in here, as it was a very quick pass to get the job done.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
