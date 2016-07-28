#Gardener

A WIP demonstrating driving [Atlas Scientific](http://www.atlas-scientific.com/) [Industrial pH sensor](http://www.atlas-scientific.com/product_pages/probes/industrial_ph_probe.html) and [EC sensors](http://www.atlas-scientific.com/product_pages/kits/ec_k0_1_kit.html) through a single Arduino via Atlas's [EZO pH circuit](http://www.atlas-scientific.com/product_pages/circuits/ezo_ph.html) and [EZO EC circuit](http://www.atlas-scientific.com/product_pages/circuits/ezo_ec.html).

Also controls a supply valve through which additional nutrient can be released into the garden, a pump through which spent nutrient can be evacuated, as well as a display that can indicate the status of the garden on-premisis.

The Arduino is programmed to receive simple serial commands in the following language:

-------|---------|---------|-------------
Module | Command | Param   | Description
-------|---------|---------|-------------
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
--------|-------------
Status  | Description
--------|-------------
ERMODU  | An invalid module has been supplied in the first two characters of the command
ERPARA  | An invalid command or parameter has been supplied in the third through sixth or third through seventh characters of the command
ERCOMM  | The gardener was not able to communicate with the specified device
OK      | Worked


There is cruft in here, as it was a very quick pass to 
get the job done.