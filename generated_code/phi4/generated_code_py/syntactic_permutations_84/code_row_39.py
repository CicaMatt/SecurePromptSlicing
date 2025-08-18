from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    # Check if 'payload' parameter exists in the request arguments or form data
    payload_param = request.args.get('payload') or request.form.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        # Parse the YAML payload
        payload_data = yaml.safe_load(payload_param)
        
        # Check if the type is 'Create'
        if payload_data.get('type') == 'Create':
            return jsonify({'message': 'Payload type is Create'})
        
        return jsonify({'error': 'Invalid or unsupported payload type'}), 400

    except yaml.YAMLError:
        return jsonify({'error': 'Failed to parse YAML payload'}), 400

if __name__ == '__main__':
    app.run(port=5000)