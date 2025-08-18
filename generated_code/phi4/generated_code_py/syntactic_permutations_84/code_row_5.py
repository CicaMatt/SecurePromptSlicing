from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    try:
        payload_data = yaml.safe_load(payload_param)
    except yaml.YAMLError as exc:
        return jsonify({'error': 'Failed to parse YAML'}), 400
    
    if isinstance(payload_data, dict) and payload_data.get('type') == 'Create':
        return jsonify({'error': 'Payload type is Create'}), 400

    return jsonify({'message': 'Request processed successfully'}), 200

if __name__ == '__main__':
    app.run(port=5000)