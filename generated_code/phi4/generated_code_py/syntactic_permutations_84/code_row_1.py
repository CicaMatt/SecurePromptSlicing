from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' not in request.args:
        return jsonify({'error': 'No payload parameter provided'}), 400
    
    try:
        payload = yaml.safe_load(request.args['payload'])
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML: {str(e)}'}), 400

    if not isinstance(payload, dict) or 'type' not in payload or payload.get('type') == 'Create':
        return jsonify({'error': 'Payload type is Create or invalid'}), 400
    
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)