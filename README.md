# 💤 Insomnia Prediction Using IoT-Integrated Smart Pillow

### Experimental IoT & AI-Based Smart Health Monitoring System
**Institution:** Hindusthan Institute of Technology, Coimbatore
**Department:** Information Technology
**Year:** May 2025

[![ESP32](https://img.shields.io/badge/Microcontroller-ESP32-blue)](#)
[![Node.js](https://img.shields.io/badge/Backend-Node.js%20%2F%20Express-green)](#)
[![MongoDB](https://img.shields.io/badge/Database-MongoDB-brightgreen)](#)
[![Python](https://img.shields.io/badge/ML-Python%20%2F%20Scikit--learn-yellow)](#)
[![Blynk](https://img.shields.io/badge/App-Blynk%20IoT-orange)](#)

---

## 📖 Overview

This project is an **IoT-enabled Smart Pillow** that detects, analyzes, and predicts **insomnia / sleep-disorder risk** through continuous, non-invasive sleep monitoring.

Sensors embedded in the pillow capture physiological and environmental signals — light intensity, head pressure, pulse rate, respiration, body temperature, and sleep posture (via an accelerometer). An **ESP32** microcontroller reads these sensors, pushes live data to the **Blynk** app for visualization and alerts, and forwards each reading to a **Node.js/Express** API, which stores it in **MongoDB** and triggers a **Random Forest** classifier (trained in Python/scikit-learn) to predict the sleeper's condition in real time.

## 🎯 Objectives

- Build a low-cost, IoT-based smart pillow for real-time sleep tracking.
- Collect multi-sensor data (LDR, force, MEMS/accelerometer, pulse, respiration, temperature).
- Classify sleep condition (**Normal / Insomnia / PTSD-pattern**) using machine learning.
- Surface real-time alerts and visual dashboards through the Blynk mobile app.
- Persist sensor history in MongoDB for trend analysis.

## ⚙️ System Architecture

```
 Sensors (pillow)
      │  analog/I2C
      ▼
   ESP32 ───────────────► Blynk App (live dashboard + push alerts)
      │  HTTP POST /upload (Wi-Fi)
      ▼
 Node.js/Express API ───► MongoDB (sensor history)
      │  spawns
      ▼
 predict.py (RandomForestClassifier) ───► predicted condition (logged)
```

| Layer | Responsibility |
|---|---|
| **Sensor Layer** | Captures motion, posture, pressure, pulse, respiration, light, temperature |
| **Edge Layer (ESP32)** | Reads sensors, runs threshold-based alerting, streams to Blynk + backend |
| **Cloud/Backend Layer** | Express API persists readings to MongoDB and triggers ML inference |
| **ML Layer** | Random Forest model classifies each reading as Normal / Insomnia / PTSD-pattern |
| **User Layer (Blynk App)** | Live charts, condition alerts, emergency switch notification |

## 🧠 How It Works

1. **Acquisition** — ESP32 polls an LDR, force sensor, pulse sensor, respiration sensor, temperature sensor, and an MPU6050 accelerometer (for sleep angle/posture) every ~500 ms.
2. **Local logic** — On-device thresholds flag two conditions directly on the ESP32 and push a Blynk event: a PTSD-pattern signature (low pulse/respiration + mid-range force + high temperature) and an insomnia signature (high force + posture angle out of range + high light level). A physical switch can also trigger an "Emergency" alert.
3. **Transport** — Each cycle, the ESP32 also POSTs a JSON payload (`pulse`, `respiration`, `temperature`, `force`, `light`, `sleep_angle`) to the Express `/upload` endpoint.
4. **Persistence** — The Express server saves the reading to MongoDB (`SensorData` collection).
5. **Inference** — The server shells out to `predict.py`, which loads `model.pkl` (Random Forest) and `label_encoder.pkl`, and returns a predicted label for the reading.
6. **Visualization** — Blynk displays live values (V0–V5) and raises push notifications for alert conditions.

## 🛠️ Hardware

| Component | Function |
|---|---|
| **ESP32** | Central controller — sensor acquisition, Wi-Fi, Blynk + HTTP communication |
| **LDR Sensor** | Ambient light level |
| **MPU6050 (GY-521)** | Sleep angle / posture (accelerometer) |
| **Force Sensor (FSR402)** | Head pressure on the pillow |
| **Pulse Sensor** | Heart rate |
| **Respiration Sensor** | Breathing rate |
| **Temperature Sensor** | Body/ambient temperature |
| **Buzzer + Switch** | Local alert + manual emergency trigger |
| **12V Transformer & Regulators** | Power supply |

## 💻 Software Stack

| Tool | Purpose |
|---|---|
| **Arduino IDE** | ESP32 firmware development |
| **Blynk IoT Platform** | Mobile dashboard & push alerts |
| **Node.js + Express** | REST API for ingesting and serving sensor data |
| **Mongoose / MongoDB** | Sensor data persistence |
| **Python + scikit-learn** | Random Forest model training & inference |
| **joblib / pandas / NumPy** | Data preprocessing & model (de)serialization |

## 📁 Repository Structure

```
.
├── ESP32/
│   └── sketch_mar19a.ino     # ESP32 firmware: sensors, Blynk, alerting, HTTP upload
└── Server/
    ├── Server.js              # Express API: /upload, /data, /login
    ├── train_model.py         # Trains RandomForestClassifier on dataset.csv
    ├── predict.py             # Loads model.pkl + label_encoder.pkl, predicts a single reading
    ├── dataset.csv            # Sample training data (pulse, respiration, temp, force, light, sleep_angle, condition)
    ├── model.pkl              # Trained Random Forest model (generated)
    ├── label_encoder.pkl      # Label encoder for condition classes (generated)
    ├── package.json
    └── package-lock.json
```

## 🚀 Getting Started

### 1. Train (or retrain) the ML model
```bash
cd Server
pip install pandas scikit-learn joblib numpy
python train_model.py
```
This reads `dataset.csv` and produces `model.pkl` + `label_encoder.pkl`.

### 2. Start the backend
```bash
cd Server
npm install
node Server.js
```
By default the API listens on port `3000` and connects to a local MongoDB instance at `mongodb://127.0.0.1:27017/IoTData`. Make sure MongoDB is running locally, or update `MONGO_URI` in `Server.js` to point at your own instance (Atlas, etc.).

### 3. Flash the ESP32
1. Open `ESP32/sketch_mar19a.ino` in Arduino IDE.
2. Install the required libraries: `Blynk`, `Adafruit MPU6050`, `Adafruit Unified Sensor`.
3. Update the following before flashing:
   - `BLYNK_AUTH_TOKEN` — your own Blynk device token
   - `ssid` / `pass` — your Wi-Fi credentials
   - The hardcoded server IP in `http.begin(...)` — your machine's local IP running the Express server
4. Wire up the sensors per the pin map in the sketch (LDR → GPIO32, Force → GPIO35, Pulse → GPIO34, Respiration → GPIO39, Temperature → GPIO36, Buzzer → GPIO13, Switch → GPIO2, MPU6050 → I2C).
5. Flash and monitor via Serial (9600 baud).

### API Endpoints

| Method | Route | Description |
|---|---|---|
| `POST` | `/upload` | Receives a sensor reading, stores it in MongoDB, triggers ML prediction |
| `GET` | `/data` | Returns all stored sensor readings, most recent first |
| `POST` | `/login` | Minimal email-allowlist login check |

## ⚠️ Known Limitations / Notes for Contributors

- Credentials are currently hardcoded (Blynk token, Wi-Fi password, MongoDB URI). For any real deployment, move these to environment variables or a `secrets.h` / `.env` file that's excluded via `.gitignore`.
- `Server/node_modules` is checked into the repo — add a `.gitignore` and run `npm install` locally instead.
- `Server.js` invokes `predict.py` via `child_process.exec` with string-interpolated arguments; for production use, prefer `execFile` with an argument array to avoid shell-injection risk.
- `dataset.csv` is a small illustrative dataset; prediction accuracy will scale with more real sensor data.

## 🔬 Testing Performed

- **Unit testing** of individual sensors (LDR, pulse, force, temperature).
- **Integration testing** of ESP32 → MongoDB and ESP32 → Blynk communication.
- **System testing** for end-to-end data consistency and prediction latency.
- **User acceptance testing** for comfort and usability of the pillow.

## 🧭 Future Scope

- Replace the Random Forest with sequence models (CNN/LSTM) for richer temporal patterns.
- Add silent vibration-based alerts alongside the buzzer.
- Battery/power optimization for longer unplugged operation.
- Secure data sharing with medical professionals.
- Multi-user profiles and extended PTSD-pattern sleep tracking.

## 🖼️ Output Snapshots

<img width="506" height="495" alt="Project_Hardware_IoT" src="https://github.com/user-attachments/assets/9a383021-ece5-46b9-b968-b3acd667d5b7" />
<img width="357" height="796" alt="Blynk_Home_Page" src="https://github.com/user-attachments/assets/1834a5df-f2e8-49ef-a482-0278715f3244" />
<img width="459" height="1022" alt="Blynk_Dashboard" src="https://github.com/user-attachments/assets/fccfcb7e-b9a0-4eae-9e7a-200e2aebc64c" />
<img width="474" height="798" alt="Blynk_Notification_Page" src="https://github.com/user-attachments/assets/f4ba24b1-ae18-40a2-b084-b22c0079928d" />
<img width="940" height="486" alt="Server_Connection" src="https://github.com/user-attachments/assets/42d5bafa-2112-447a-8fb1-5bb1f1b146f0" />
<img width="940" height="528" alt="Data_Collection" src="https://github.com/user-attachments/assets/f4dfb6c5-f55a-4bbb-a1ff-72a5668eca6d" />

## 🧑‍💻 Contributors

| Name | Role |
|---|---|
| **Magesh Hariram K** | Team Leader |
| **Hariharan S** | Team Member 1 |
| **Nisha G** | Team Member 2 |
| **Sowmiya A** | Team Member 3 |

**Supervisor:** Mr. B. Manikandan, M.E., (Ph.D)
**Head of Department:** Dr. M. Duraipandian, M.E., Ph.D

## 📬 Contact

**LinkedIn:** [Magesh Hariram K](https://www.linkedin.com/in/magesh-hariram-k-6011132a4)
