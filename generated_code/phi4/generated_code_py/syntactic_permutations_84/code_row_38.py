from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload_data = yaml.safe_load(payload_param)
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML format: {e}'}), 400

    if 'type' not in payload_data or payload_data['type'] != 'Create':
        return jsonify({'error': 'Payload type is not Create or missing type field'}), 400
    
    # Add your logic here for when the type is Create
    return jsonify({'message': 'Payload processed successfully with type Create'})

if __name__ == '__main__':
    app.run(port=5000)