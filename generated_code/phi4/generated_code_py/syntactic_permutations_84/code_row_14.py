from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload = yaml.safe_load(payload_param)
        
        if isinstance(payload, dict) and payload.get('type') == 'Create':
            return jsonify({'error': 'Payload type is Create, which is not allowed'}), 400
        
        return jsonify({'message': 'Payload received successfully', 'payload': payload}), 200

    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400

if __name__ == '__main__':
    app.run(port=5000)