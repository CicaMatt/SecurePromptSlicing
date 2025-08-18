from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload_data = yaml.safe_load(payload_param)
        
        if payload_data and payload_data.get('type') == 'Create':
            return jsonify({'error': 'Payload type cannot be Create'}), 400
        
        return jsonify({'message': 'Payload processed successfully', 'data': payload_data}), 200
    
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML format: {str(e)}'}), 400

if __name__ == '__main__':
    app.run(port=5000)