from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' not in request.args:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    payload_str = request.args.get('payload')
    
    try:
        payload = yaml.safe_load(payload_str)
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400

    if not isinstance(payload, dict) or 'type' not in payload:
        return jsonify({'error': 'Payload must be a dictionary with a type key'}), 400
    
    if payload['type'] == 'Create':
        return jsonify({'error': 'Type Create is not allowed'}), 403
    
    return jsonify({'message': 'Payload processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)