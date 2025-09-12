from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def handle_request():
    payload_param = request.args.get('payload')
    if not payload_param:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload_data = yaml.safe_load(payload_param)
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML format: {str(e)}'}), 400

    if 'type' not in payload_data or payload_data['type'] != 'Create':
        return jsonify({'error': 'Payload type must be Create'}), 400
    
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)