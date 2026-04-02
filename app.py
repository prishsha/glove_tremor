from flask import Flask, jsonify, render_template
import numpy as np
import time

app = Flask(__name__)

start_time = time.time()

# Generate tremor signal
def generate_tremor():
    t = time.time() - start_time
    
    tremor_freq = 5  # Hz
    tremor = np.sin(2 * np.pi * tremor_freq * t)
    
    noise = np.random.normal(0, 0.2)
    
    return tremor + noise

def generate_motor_pattern(detected):
    if not detected:
        return [0, 0, 0, 0, 0]

    # simple alternating pattern
    return [
        np.random.randint(0, 2),
        np.random.randint(0, 2),
        np.random.randint(0, 2),
        np.random.randint(0, 2),
        np.random.randint(0, 2)
    ]

# Detection logic
def detect_tremor(value):
    threshold = 0.7
    return abs(value) > threshold

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data')
def data():
    value = generate_tremor()
    detected = bool(detect_tremor(value))

    motors = generate_motor_pattern(detected)

    return jsonify({
        'value': float(value),
        'detected': detected,
        'motors': motors
    })

@app.route('/esp')
def esp():
    value = generate_tremor()
    detected = bool(detect_tremor(value))

    return jsonify({
        'motor': int(detected)  # 1 or 0
    })

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)