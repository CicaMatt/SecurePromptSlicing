from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' not in request.args:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload_str = request.args.get('payload')
        payload_yaml = yaml.safe_load(payload_str)
        
        if not isinstance(payload_yaml, dict):
            return jsonify({'error': 'Invalid YAML format'}), 400
        
        if payload_yaml.get('type') == 'Create':
            return jsonify({'error': 'Type Create is not allowed'}), 403
        
    except yaml.YAMLError:
        return jsonify({'error': 'Failed to parse YAML'}), 400
    
    return jsonify({'message': 'Payload processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)