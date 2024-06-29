/*  Advanced Cap Meter using Arduino
 *  Measures capacitance, ESR, and leakage current of a capacitor.
 *  
 *  Expanding on code/idea from https://docs.arduino.cc/tutorials/generic/capacitance-meter/

 *  Wiring Setup:
 *  - Capacitor between common point and ground (positive side of an electrolytic capacitor to common).
 *  - Known resistor (e.g., 10kΩ) between chargePin and common point.
 *  - 220Ω resistor between dischargePin and common point.
 *  - Wire between common point and analogPin (A0).
 */

#define analogPin A0          // Analog pin for measuring capacitor voltage
#define chargePin 13          // Pin to charge the capacitor - connected to one end of the charging resistor
#define dischargePin 11       // Pin to discharge the capacitor
#define resistorValue 10000.0F // Resistor value in ohms (10kΩ)

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;
float nanoFarads;
float leakageCurrent;
float esr;

void setup() {
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);  
  digitalWrite(dischargePin, LOW);
  Serial.begin(9600);             
}

void loop() {
  showMenu();
}

void showMenu() {
  Serial.println("\n[- Capacitor Measurement Menu -]");
  Serial.println("1) Measure capacitance");
  Serial.println("2) Measure ESR");
  Serial.println("3) Measure leakage current");
  Serial.println("4) Charge capacitor");
  Serial.println("5) Discharge capacitor");
  Serial.println("Enter your choice: ");
  
  while (Serial.available() == 0) {
    // wait
  }

  int choice = Serial.parseInt();
  performAction(choice);
}

void performAction(int choice) {
  switch (choice) {
    case 1:
      measureCapacitance();
      break;
    case 2:
      measureESR();
      break;
    case 3:
      measureLeakageCurrent();
      break;
    case 4:
      chargeCapacitor();
      break;
    case 5:
      dischargeCapacitor("Discharging capacitor...");
      break;
    default:
      Serial.println("Invalid choice. Please select a valid option.");
  }
}

void measureCapacitance() {
  dischargeCapacitor("");
  Serial.println("Measuring capacitance...");
  digitalWrite(chargePin, HIGH);  
  startTime = millis();
  while (analogRead(analogPin) < 648) {
  }
  elapsedTime = millis() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) * 1000;
  Serial.print(elapsedTime);       
  Serial.print(" ms    ");        

  if (microFarads > 1) { 
    Serial.print((long)microFarads);       
    Serial.println(" microFarads");         
  } else {
    nanoFarads = microFarads * 1000.0;      
    Serial.print((long)nanoFarads);         
    Serial.println(" nanoFarads");          
  }

  digitalWrite(chargePin, LOW);
  dischargeCapacitor("Discharging capacitor...");
}

void measureESR() {
  Serial.println("Measuring ESR...");
  digitalWrite(chargePin, HIGH);  
  delay(100); 
  int voltageDrop = analogRead(analogPin);
  esr = ((5.0 - (voltageDrop * 5.0 / 1023.0)) / (5.0 / 10000.0));
  Serial.print("ESR: ");
  Serial.print(esr);
  Serial.println(" ohms");
  digitalWrite(chargePin, LOW);
  dischargeCapacitor("Discharging capacitor...");
}

void measureLeakageCurrent() {
  Serial.println("Measuring leakage current...");
  digitalWrite(chargePin, HIGH);  
  delay(1000);
  digitalWrite(chargePin, LOW);   
  delay(1000);
  int leakageVoltage = analogRead(analogPin);
  leakageCurrent = (leakageVoltage * 5.0 / 1023.0) / 10000.0;
  Serial.print("Leakage current: ");
  Serial.print(leakageCurrent);
  Serial.println(" A");
  dischargeCapacitor("Discharging capacitor...");
}

void chargeCapacitor() {
  Serial.println("Charging capacitor...");
  digitalWrite(chargePin, HIGH);  
  Serial.println("Capacitor charged.");
}

void dischargeCapacitor(const char* dischargeMsg) {
  Serial.println(dischargeMsg);
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);
  
  while (analogRead(analogPin) > 0) {
    // Wait for capacitor to discharge
  }
  
  pinMode(dischargePin, INPUT);
  Serial.println("Capacitor discharged.");
}
