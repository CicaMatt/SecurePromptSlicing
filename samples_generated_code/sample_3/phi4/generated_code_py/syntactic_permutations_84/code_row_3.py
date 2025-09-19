from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'No payload parameter provided'}), 400
    
    try:
        payload_data = yaml.safe_load(payload_param)
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML: {str(e)}'}), 400
    
    if not isinstance(payload_data, dict):
        return jsonify({'error': 'Payload is not a valid dictionary'}), 400

    if payload_data.get('type') == 'Create':
        return jsonify({'error': 'Type Create is not allowed'}), 403

    return jsonify({'message': 'Request received successfully'}), 200

if __name__ == '__main__':
    app.run(port=5000)