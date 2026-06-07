# Smart Energy Monitor

A real-time power consumption monitoring system built on Arduino Uno. Replicates the core logic of a prepaid electricity meter — measuring current, calculating power, and accumulating energy usage over time.

---

## What It Does

- Samples an analog current sensor signal **500 times per cycle** to compute RMS current via numerical integration
- Calculates instantaneous power using **P = IV** (assuming 220V Nigerian mains voltage)
- Accumulates energy consumption in **watt-hours (Wh)** — exactly how electricity bills are calculated
- Displays live current, power, and energy readings on a **16x2 LCD**
- Logs a timestamped data table to the **Serial Monitor** for analysis

---

## Components

| Component | Purpose |
|---|---|
| Arduino Uno | Microcontroller |
| ACS712 Current Sensor (simulated) | Analog current measurement |
| 16x2 LCD Display | Live readings output |
| Potentiometer (x2) | LCD contrast + sensor simulation |
| 220Ω Resistor | LCD backlight current limiting |

---

## How It Works

The ACS712 current sensor outputs a voltage proportional to current flow, centered at 2.5V. The Arduino samples this signal 500 times and computes the **Root Mean Square (RMS)** value:

```
RMS = sqrt( sum(sample²) / n )
Power (W) = RMS Current × Mains Voltage (220V)
Energy (Wh) += Power × Time Elapsed (hours)
```

This is the same mathematical technique used in commercial power meters.

---

## Simulation

The potentiometer simulates the ACS712 analog output — turning the knob mimics different current draw levels. Circuit designed and validated in **Tinkercad Education**.

---

## Technologies

- **Platform:** Arduino Uno
- **Language:** C++ (Arduino IDE)
- **Simulation:** Tinkercad Education
- **Display:** 16x2 LCD (LiquidCrystal library)

---

## Serial Monitor Output

```
Time(s) | Current(A) | Power(W) | Energy(Wh)
--------|------------|----------|----------
1s      | 0.823 A    | 181.06 W | 0.00005 Wh
2s      | 1.241 A    | 273.02 W | 0.00013 Wh
...
```
