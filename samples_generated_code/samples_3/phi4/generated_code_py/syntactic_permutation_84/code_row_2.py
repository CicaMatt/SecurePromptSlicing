from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' not in request.args:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload_str = request.args['payload']
        payload_data = yaml.safe_load(payload_str)
        
        if payload_data.get('type') == 'Create':
            return jsonify({'error': 'Invalid type: Create not allowed'}), 400
        
        return jsonify({'message': 'Payload processed successfully'})
    
    except yaml.YAMLError as e:
        return jsonify({'error': f'Error parsing YAML: {str(e)}'}), 400

if __name__ == '__main__':
    app.run(port=5000)