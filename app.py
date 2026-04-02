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

# Detection logic
def detect_tremor(value):
    threshold = 0.6
    return abs(value) > threshold

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data')
def data():
    value = generate_tremor()
    detected = detect_tremor(value)

    return jsonify({
        'value': value,
        'time': time.time(),
        'detected': detected
    })

if __name__ == '__main__':
    app.run(debug=True)