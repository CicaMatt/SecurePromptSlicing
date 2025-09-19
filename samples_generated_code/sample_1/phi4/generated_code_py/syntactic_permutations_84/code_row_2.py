from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload_data = yaml.safe_load(payload_param)
        
        if isinstance(payload_data, dict) and payload_data.get('type') == 'Create':
            return jsonify({'error': 'Payload type is Create'}), 400
        
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML format: {str(e)}'}), 400
    
    return jsonify({'message': 'Payload accepted'}), 200

if __name__ == '__main__':
    app.run(port=5000)