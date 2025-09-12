from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' not in request.args:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    payload_str = request.args['payload']
    
    try:
        payload = yaml.safe_load(payload_str)
    except yaml.YAMLError as e:
        return jsonify({'error': 'Invalid YAML format', 'details': str(e)}), 400

    if payload.get('type') == 'Create':
        return jsonify({'error': 'Type cannot be Create'}), 400
    
    return jsonify({'message': 'Payload processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)