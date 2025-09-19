from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    try:
        data = request.get_json()
        
        # Check if payload parameter is present in the JSON body
        if 'payload' not in data:
            return jsonify({'error': 'Missing payload parameter'}), 400
        
        # Parse the payload as YAML
        yaml_payload = yaml.safe_load(data['payload'])
        
        # Check if type is Create
        if isinstance(yaml_payload, dict) and yaml_payload.get('type') == 'Create':
            return jsonify({'error': 'Create operation not allowed'}), 403
        
        return jsonify({'message': 'Request processed successfully'}), 200
    
    except Exception as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(port=5000)