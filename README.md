# capmeter
Capacitance, ESR, and leakage current measurements with Arduino

```
[- Capacitor Measurement Menu -]
1) Measure capacitance
2) Measure ESR
3) Measure leakage current
4) Charge capacitor
5) Discharge capacitor
Enter your choice: 
1
Capacitor discharged.
Measuring capacitance...
1 ms    99 nanoFarads
Discharging capacitor...
Capacitor discharged.
```

## Algorithm
1. **Capacitance Measurement:**
   - Charge the capacitor through a known resistor. (10k)
   - Measure the time taken to reach 63.2% of the supply voltage.
   - elapsedTime is measured in milliseconds and we want capacitance in microfarads (µF), we multiply by 1000 to convert:
      C (µF) = (elapsedTime / R) * 1000
2. **ESR Measurement:**
   - Charge the capacitor through a known series resistor.
   - Measure the voltage drop across the resistor to calculate ESR.
   - This is likely very inaccurate. Learn more about Equivalent Series Resistance here: [All About Circuits - Determining Equivalent Series Resistance (ESR) of Capacitors](https://www.allaboutcircuits.com/technical-articles/determining-equivalent-series-resistance-esr-of-capacitors/)
3. **Leakage Current Measurement:**
   - Charge the capacitor to a known voltage.
   - Measure the current flowing through the capacitor over time.
4. **Charge the Capacitor:**
   - Manually charge the capacitor.
5. **Discharge the Capacitor:**
   - Optionally discharge the capacitor for the next measurement.

## Wiring Setup
- **Capacitor:** Connect between the common point and ground (positive side of an electrolytic capacitor to common).
- **Charging Resistor:** Connect a known resistor (e.g., 10kΩ) between `chargePin` (digital pin 13) and the common point.
- **Discharging Resistor:** Connect a 220Ω resistor between `dischargePin` (digital pin 11) and the common point.
- **Analog Pin:** Connect a wire between the common point and `analogPin` (analog pin A0).

## Todo:
 Measure the capacitance at different intervals to observe how it changes over time.
 Measure temperature dependency and frequency response?
