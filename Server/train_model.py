import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.preprocessing import LabelEncoder
import joblib

# Step 1: Load Data
data = pd.read_csv('dataset.csv')

# Step 2: Features (X) and Target (y)
X = data[['pulse', 'respiration', 'temperature', 'force', 'light', 'sleep_angle']]
y = data['condition']

# Step 3: Encode Labels (Normal => 0, Insomnia => 1, PTSD => 2)
le = LabelEncoder()
y_encoded = le.fit_transform(y)

# Save label encoder to use during prediction
joblib.dump(le, 'label_encoder.pkl')

# Step 4: Split Dataset
X_train, X_test, y_train, y_test = train_test_split(X, y_encoded, test_size=0.2, random_state=42)

# Step 5: Train ML Model
model = RandomForestClassifier(n_estimators=100, random_state=42)
model.fit(X_train, y_train)

# Step 6: Save Model
joblib.dump(model, 'model.pkl')

print("Model trained and saved as model.pkl")