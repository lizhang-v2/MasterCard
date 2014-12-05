// Arduino as load cell amplifier
// by Christian Liljedahl 
// christian.liljedahl.dk

// Load cells are linear. So once you have established two data pairs, you can interpolate the rest.

// Step 1: Upload this sketch to your arduino board

// You need two loads of well know weight. In this example A = 10 kg. B = 30 kg
// Put on load A 
// read the analog value showing (this is analogvalA)
// put on load B
// read the analog value B

#include <Process.h>

// Enter you own analog values here
float loadA = .06; // kg
int analogvalA = 16; // analog reading taken with load A on the load cell

float loadB = 1.623; // kg 
int analogvalB = 861; // analog reading taken with load B on the load cell

// Upload the sketch again, and confirm, that the kilo-reading from the serial output now is correct, using your known loads
float analogValueAverage = 0;

float threshold = 0.22;

// How often do we do readings?
long time = 0; // 
int timeBetweenReadings = 200; // We want a reading every 200 ms;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  Serial.println("setup");
  
}

int flag=0;
void loop() {
  int analogValue = analogRead(0);

  // running average - We smooth the readings a little bit
  analogValueAverage = 0.99*analogValueAverage + 0.01*analogValue;

  // Is it time to print? 
  if(millis() > time + timeBetweenReadings){
    float load = analogToLoad(analogValueAverage);
    
    //HACK first time load is low, about 0.03
    if(load > 0.04) {
    
      if(load < threshold){
        if(flag == 0) {
          postData();
          flag=1;
        }
      } else {
        flag=0;
      }
    
    }

    Serial.print("analogValue: ");Serial.println(analogValueAverage);
    Serial.print("             load: ");Serial.println(load,5);
    time = millis();
  }
  
}

float analogToLoad(float analogval){
  // using a custom map-function, because the standard arduino map function only uses int
  float load = mapfloat(analogval, analogvalA, analogvalB, loadA, loadB);
  return load;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void postData()
{
  Process phant; // Used to send command to Shell, and view response
  String curlCmd; // Where we'll put our curl command
  
  //make the Yo notification
  curlCmd = "curl --data \"api_token=9fd5efd2-deee-4061-8f88-1943701261fd&username=lizhang919&&link=http://www.amazon.com/Audubon-Whole-Coffee-Shade-French/dp/B001ELL42C/ref=sr_1_1?ie=UTF8&qid=1414781474&sr=8-1&keywords=estate+select+coffee\" http://api.justyo.co/yo/";
  // Send the curl command:
  Serial.print("Sending command: ");
  Serial.println(curlCmd); // Print command for debug
  phant.runShellCommand(curlCmd); // Send command through Shell
  
  curlCmd = "curl --data \"api_token=9fd5efd2-deee-4061-8f88-1943701261fd&username=athomas3187&&link=http://www.amazon.com/Audubon-Whole-Coffee-Shade-French/dp/B001ELL42C/ref=sr_1_1?ie=UTF8&qid=1414781474&sr=8-1&keywords=estate+select+coffee\" http://api.justyo.co/yo/";
  // Send the curl command:
  Serial.print("Sending command: ");
  Serial.println(curlCmd); // Print command for debug
  phant.runShellCommand(curlCmd); // Send command through Shell
  
  curlCmd = "curl --data \"api_token=9fd5efd2-deee-4061-8f88-1943701261fd&username=lguo&&link=http://www.amazon.com/Audubon-Whole-Coffee-Shade-French/dp/B001ELL42C/ref=sr_1_1?ie=UTF8&qid=1414781474&sr=8-1&keywords=estate+select+coffee\" http://api.justyo.co/yo/";
  // Send the curl command:
  Serial.print("Sending command: ");
  Serial.println(curlCmd); // Print command for debug
  phant.runShellCommand(curlCmd); // Send command through Shell
  
  //make the payment via Simplify API
  curlCmd = "curl http://54.172.31.190/ChargeWithCardDetails.php";
  // Send the curl command:
  Serial.print("Sending command: ");
  Serial.println(curlCmd); // Print command for debug
  phant.runShellCommand(curlCmd); // Send command through Shell

  // Read out the response:
  Serial.print("Response: ");
  // Use the phant process to read in any response from Linux:
  while (phant.available())
  {
    char c = phant.read();
    Serial.write(c);
  }
}
