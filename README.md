
# 💤 Insomnia Prediction Using IoT – Integrated Smart Pillow

### 🧩 Experimental IoT & AI-Based Smart Health Monitoring Project  
**Institution:** Hindusthan Institute of Technology, Coimbatore  
**Department:** Information Technology  
**Year:** May 2025
## 📖 Project Overview
This project presents an **IoT-enabled Smart Pillow** designed to detect, analyze, and predict **insomnia** through continuous sleep monitoring.  
The pillow integrates multiple **environmental and physiological sensors** to collect real-time data such as light intensity, body movement, head pressure, heart rate, temperature, and sound levels.  

The collected data is processed by an **ESP32 microcontroller**, stored in **MongoDB**, and analyzed using **Machine Learning models** (Random Forest Classifier in Python). The system predicts sleep quality, identifies disturbances, and notifies users through the **Blynk mobile application**.

By combining IoT with AI, the system provides personalized sleep insights, early detection of insomnia symptoms, and proactive health management.

## 🎯 Objectives
- Develop an **IoT-based Smart Pillow** capable of real-time sleep tracking.  
- Collect data from **LDR, Force, MEMS, Temperature, Pulse, and Sound sensors**.  
- Classify sleep stages and detect insomnia using **Machine Learning**.  
- Provide **real-time alerts and visualizations** through Blynk.  
- Enable **remote data storage and analysis** via MongoDB Cloud.  
- Offer **personalized recommendations** to users based on sleep trends.

## ⚙️ System Architecture
The system operates across four primary layers:

- **Sensor Layer** – Embedded sensors detect body motion, sleep posture, pressure, pulse rate, snoring, and ambient light.  
- **Processing Layer (ESP32)** – Collects, filters, and transmits data via Wi-Fi.  
- **Cloud & Analytics Layer** – Stores data in MongoDB and processes it with Python-based ML models.  
- **User Interaction Layer (Blynk App)** – Displays live data, trends, and alerts for insomnia risk.

## 🧠 Methodology
- **Data Collection:** Sensors record physiological and environmental data during sleep.  
- **Signal Processing:** The ESP32 filters and digitizes signals for transmission.  
- **IoT Communication:** Data is sent to MongoDB and Blynk via HTTP & Wi-Fi.  
- **AI Analysis:** The ML model classifies sleep stages (Normal / Disturbed / Insomnia).  
- **Visualization:** The Blynk app displays live graphs, alerts, and summaries.  
- **Alerting:** Abnormal readings trigger local buzzer alerts and push notifications.  

## 🛠️ Hardware Requirements
| Component | Function |
|------------|-----------|
| **ESP32** | Central controller for data collection and transmission |
| **LDR Sensor** | Detects ambient light conditions |
| **MEMS Sensor (GY-521)** | Tracks sleep angle and posture |
| **Force Sensor (FSR402)** | Measures head pressure on the pillow |
| **Pulse Sensor** | Monitors heart rate |
| **Temperature Sensor** | Records room temperature |
| **Sound Sensor (LM393)** | Detects snoring or irregular sounds |
| **Buzzer + Switch** | Provides real-time emergency alert |
| **12V Transformer & Regulators** | Power management |

## 💻 Software Requirements
| Tool / Framework | Purpose |
|-------------------|----------|
| **Arduino IDE** | ESP32 programming |
| **Blynk IoT Platform** | Mobile visualization & alerting |
| **MongoDB** | Cloud data storage |
| **Node.js + Express.js** | API backend for data upload |
| **Python (Scikit-learn)** | Machine learning model (Random Forest) |
| **Joblib / Pandas / NumPy** | Data preprocessing & model persistence |

## 🧩 Implementation Modules
- **Hardware Integration:** Sensor assembly and ESP32 configuration.
- **Software Development:** Data acquisition and transmission code (Arduino).
- **Cloud Server:** Node.js backend to store and forward data.
- **AI Model:** Random Forest-based classifier (`train_model.py`, `predict.py`).
- **Mobile App:** Blynk dashboard for real-time visualization.  

## 🔬 Testing & Evaluation
- **Unit Testing:** Verified accuracy of each sensor (LDR, Pulse, Temperature, etc.).
- **Integration Testing:** Validated ESP32-to-MongoDB and Blynk communication.
- **System Testing:** Checked real-time data consistency and insomnia prediction accuracy.
- **User Acceptance Testing:** Ensured comfort, usability, and reliability.

## 🧭 Future Scope & Enhancements
- Integration of **advanced AI (CNN, LSTM)** for improved prediction accuracy.
- Addition of **vibration-based silent alerts**.
- **Battery optimization** for extended operation.
- **Cloud data sharing** with medical professionals for remote analysis.
- Support for **multi-user profiles** and **PTSD-related sleep tracking**.

## 🧑‍💻 Contributors
| Name | Role |
|------|------|
| **Magesh Hariram K** | Team Leader & IoT Implementation & Database Connection |
| **Hariharan S** | IoT Implementation (assist) & Documentation |
| **Nisha G** | Software Development & Testing |
| **Sowmiya A** | AI Model & Presentation Making (PPT) |

**Supervisor:** Mr. B. Manikandan, M.E., (Ph.D)

**Head of Department:** Dr. M. Duraipandian, M.E., Ph.D

## Output Snapshots

<img width="506" height="495" alt="Project_Hardware_IoT" src="https://github.com/user-attachments/assets/9a383021-ece5-46b9-b968-b3acd667d5b7" />

<img width="357" height="796" alt="Blynk_Home_Page" src="https://github.com/user-attachments/assets/1834a5df-f2e8-49ef-a482-0278715f3244" />

<img width="459" height="1022" alt="Blynk_Dashboard" src="https://github.com/user-attachments/assets/fccfcb7e-b9a0-4eae-9e7a-200e2aebc64c" />

<img width="474" height="798" alt="Blynk_Notification_Page" src="https://github.com/user-attachments/assets/f4ba24b1-ae18-40a2-b084-b22c0079928d" />

<img width="940" height="486" alt="Server_Connection" src="https://github.com/user-attachments/assets/42d5bafa-2112-447a-8fb1-5bb1f1b146f0" />

<img width="940" height="528" alt="Data_Collection" src="https://github.com/user-attachments/assets/f4dfb6c5-f55a-4bbb-a1ff-72a5668eca6d" />

## 📁 Project Folder Structure

```plaintext
Insomnia_Prediction_Smart_Pillow/
│
├── ESP32/
│   └── sketch_mar19a.ino            # Main ESP32 Arduino code
│
└── Server_Backend/
    ├── node_modules/
    ├── package.json
    ├── predict.py
    ├── Server.js
    └── train_model.py
```

## 📬 Contact

**LinkedIn:** [Magesh Hariram K](https://www.linkedin.com/in/magesh-hariram-k-6011132a4)
