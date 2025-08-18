from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def process_request():
    if 'payload' not in request.json:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload = yaml.safe_load(request.json['payload'])
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML: {e}'}), 400

    if payload.get('type') == 'Create':
        return jsonify({'error': 'Type Create is not allowed'}), 403
    
    return jsonify({'message': 'Request processed successfully'}), 200

if __name__ == '__main__':
    app.run(port=5000)