#include <Arduino.h>

// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// In this example the one_wire_bus is connected to GPIO 2 - You can change this value if you want
// to use another pin.
#define ONE_WIRE_BUS 2

//set resolution of all devices to 9, 10, 11, or 12 bits
//setting the resolution to 9 basically gives .5 degrees of resolution which is probably dandy
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Declate a DallasTemperature object, passing it the address of the OneWire object
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress insideThermometer, outsideThermometer;


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
  Serial.println("Startup");

  // Start sensors object
  sensors.begin();

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  

  // This code assigns the addresses of the two temperature sensors in the order they are discovered
  // Each sensor has a unique ID - and the getAddress() function scans  through the possible ID's till
  // it finds one - so if you ask for the first device, it will always return whichever sensor has the 
  // lower ID.
 if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
 if (!sensors.getAddress(outsideThermometer, 1)) Serial.println("Unable to find address for Device 1");

  
  // report the addresses we found
  Serial.print("Inside Thermometer Address: ");
  printAddress2(insideThermometer);
  Serial.println();

  Serial.print("Outside Thermometer Address: ");
  printAddress2(outsideThermometer);
  Serial.println();

  // set the resolution of the device to the TEMPERATURE_PRECISION value we defined above
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);

  
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

  //  Serial1.println("I'm awake, but I'm going into deep sleep mode for 10 seconds");
 // ESP.deepSleep(10e6);
 delay(1000);
  
  
}