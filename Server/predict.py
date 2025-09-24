import sys
import joblib
import numpy as np

# Load trained model & label encoder
model = joblib.load('model.pkl')
le = joblib.load('label_encoder.pkl')

# Get input from Node.js (6 features)
pulse = float(sys.argv[1])
respiration = float(sys.argv[2])
temperature = float(sys.argv[3])
force = float(sys.argv[4])
light = float(sys.argv[5])
sleep_angle = float(sys.argv[6])

# Make prediction
features = np.array([[pulse, respiration, temperature, force, light, sleep_angle]])
predicted_class = model.predict(features)[0]
predicted_label = le.inverse_transform([predicted_class])[0]

print(predicted_label)  # This is the prediction that will be logged by Node.js
