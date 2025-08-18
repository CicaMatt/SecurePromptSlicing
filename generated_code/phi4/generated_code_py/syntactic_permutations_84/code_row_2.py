from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' not in request.args:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload_str = request.args.get('payload')
        payload = yaml.safe_load(payload_str)
        
        if not isinstance(payload, dict):
            return jsonify({'error': 'Invalid YAML format'}), 400
        
        if payload.get('type') == 'Create':
            return jsonify({'error': 'Type "Create" is not allowed'}), 403
        
        return jsonify({'message': 'Payload processed successfully'}), 200
    
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400

if __name__ == '__main__':
    app.run(port=5000)