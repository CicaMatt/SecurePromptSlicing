from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload') or request.form.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    try:
        payload_data = yaml.safe_load(payload_param)
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML format: {str(e)}'}), 400

    if not isinstance(payload_data, dict) or 'type' not in payload_data:
        return jsonify({'error': 'Payload does not contain a type field'}), 400
    
    if payload_data['type'] == 'Create':
        return jsonify({'error': 'Creation requests are not allowed'}), 403

    return jsonify({'message': 'Request is valid and accepted'}), 200

if __name__ == '__main__':
    app.run(port=5000)