from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    if not request.json or 'payload' not in request.json:
        return jsonify({'error': 'Missing payload'}), 400
    
    try:
        payload = yaml.safe_load(request.json['payload'])
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML'}), 400

    if payload.get('type') == 'Create':
        return jsonify({'error': 'Type Create is not allowed'}), 400
    
    return jsonify({'success': True}), 200

if __name__ == '__main__':
    app.run(port=5000)