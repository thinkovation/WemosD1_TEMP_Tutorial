#include <Arduino.h>

// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses - Use this if you do not know  the addresses of the devices
//DeviceAddress insideThermometer, outsideThermometer;

// Once you know the addresses of the devices you can hard-code the address.
// 
// You can assign address manually. The addresses below will need to be changed
// to valid device addresses on your bus. Device address can be retrieved
// by using either oneWire.search(deviceAddress) or individually via
// sensors.getAddress(deviceAddress, index)
// 28-4A-8A-76-E0-01-3C-6D
// 28-98-D4-76-E0-FF-3C-B5
DeviceAddress insideThermometer = { 0x28, 0x4A, 0x8A, 0x76, 0xE0, 0x01, 0x3C, 0x6D };
DeviceAddress outsideThermometer   = { 0x28, 0x98, 0xD4, 0x76, 0xE0, 0xFF, 0x3C, 0xB5 };
void printAddress2(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // Search for devices on the bus and assign based on an index. Ideally,
  // you would do this to initially discover addresses on the bus and then
  // use those addresses and manually assign them (see above) once you know
  // the devices on your bus (and assuming they don't change).
  //
  // 
 
 /*
 // if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
 // if (!sensors.getAddress(outsideThermometer, 1)) Serial.println("Unable to find address for Device 1");

  
  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress2(insideThermometer);
  Serial.println();

  Serial.print("Device 1 Address: ");
  printAddress2(outsideThermometer);
  Serial.println();
*/
  // set the resolution to 9 bit per device
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC);
  Serial.println();

  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(outsideThermometer), DEC);
  Serial.println();
}



// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
}



// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  //Serial.print("Device Address: ");
  //printAddress2(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

/*
   Main function, calls the temperatures in a loop.
*/
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  // print the device information
  Serial.print("InSide ");

  printTemperature(insideThermometer);
  Serial.println();
  Serial.print("OutsideSide ");

  printTemperature(outsideThermometer);
  Serial.println();

    Serial1.println("I'm awake, but I'm going into deep sleep mode for 10 seconds");
 // ESP.deepSleep(10e6);
  
  
}