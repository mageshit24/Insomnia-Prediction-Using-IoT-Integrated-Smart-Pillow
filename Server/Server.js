const express = require("express");
const mongoose = require("mongoose");
const cors = require("cors");
const bodyParser = require("body-parser");
const { exec } = require("child_process");

// Initialize Express App
const app = express();
const PORT = 3000;

// Middleware
app.use(cors());
app.use(bodyParser.json());

// MongoDB Connection
const MONGO_URI = "mongodb://127.0.0.1:27017/IoTData";  // Update for remote DB if needed
mongoose.connect(MONGO_URI, { useNewUrlParser: true, useUnifiedTopology: true })
    .then(() => console.log("Connected to MongoDB"))
    .catch(err => console.error("MongoDB Connection Error:", err));

// Define MongoDB Schema
const SensorSchema = new mongoose.Schema({
    pulse: Number,
    respiration: Number,
    temperature: Number,
    force: Number,
    light: Number,
    sleep_angle: Number,
    timestamp: { type: Date, default: Date.now }
});
const SensorData = mongoose.model("SensorData", SensorSchema);

// API Endpoint to Receive Data from ESP32
app.post("/upload", async (req, res) => {
    try {
        const { pulse, respiration, temperature, force, light, sleep_angle } = req.body;

        // Print incoming data for debugging
        console.log("Received Data:", req.body);

        // Store in MongoDB
        const newData = new SensorData({ pulse, respiration, temperature, force, light, sleep_angle });
        await newData.save();

        // Predict using the Python model
        exec(`python predict.py ${pulse} ${respiration} ${temperature} ${force} ${light} ${sleep_angle}`, (error, stdout, stderr) => {
            if (error) {
                console.error(`exec error: ${error}`);
                return;
            }
            console.log(`Prediction: ${stdout}`);
        });

        res.status(200).json({ message: "Data saved and prediction triggered!" });
    } catch (error) {
        console.error("Error saving data:", error);
        res.status(500).json({ error: "Failed to save data." });
    }
});

// For login
const users = ['user@example.com'];
app.post("/login", (req, res) => {
  const { email } = req.body;
  if (users.includes(email)) return res.status(200).json({ message: "Logged in" });
  res.status(401).json({ message: "Unauthorized" });
});

// For data fetch
app.get("/data", async (req, res) => {
  try {
    const data = await SensorData.find().sort({ timestamp: -1 });
    res.json(data);
  } catch (err) {
    res.status(500).json({ error: "Failed to fetch data" });
  }
});


// Start Server
app.listen(PORT, () => console.log(`Server running at http://192.168.149.200:${PORT}`));