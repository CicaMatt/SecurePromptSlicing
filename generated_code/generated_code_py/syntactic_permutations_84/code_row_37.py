import yaml, json
from flask import Flask
app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_payload():
    payload = request.get_json()
    if not payload or 'payload' not in payload:
        return 'Bad Request', 400
    
    payload = yaml.safe_load(payload['payload'])
    print(payload)
    if payload['type'] != 'Create':
        return jsonify({'error': 'type is not Create'}), 400
    
    return 'OK', 200

if __name__ == "__main__":
    app.run(port=5000)