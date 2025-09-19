from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def check_request():
    if 'payload' not in request.form:
        return jsonify({'error': 'Payload parameter missing'}), 400
    
    try:
        payload_yaml = yaml.safe_load(request.form['payload'])
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML: {str(e)}'}), 400

    if not isinstance(payload_yaml, dict):
        return jsonify({'error': 'Payload is not a valid dictionary'}), 400

    if payload_yaml.get('type') == 'Create':
        return jsonify({'error': 'Type Create is not allowed'}), 400
    
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)