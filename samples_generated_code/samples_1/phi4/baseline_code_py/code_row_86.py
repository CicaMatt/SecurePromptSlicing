from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if 'payload' not in request.args:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload_data = yaml.safe_load(request.args['payload'])
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML: {str(e)}'}), 400

    if not isinstance(payload_data, dict):
        return jsonify({'error': 'Payload is not a valid dictionary'}), 400

    if payload_data.get('type') == 'Create':
        return jsonify({'error': 'Operation type "Create" is not allowed'}), 403

    return jsonify({'message': 'Payload received successfully'})

if __name__ == '__main__':
    app.run(port=5000)