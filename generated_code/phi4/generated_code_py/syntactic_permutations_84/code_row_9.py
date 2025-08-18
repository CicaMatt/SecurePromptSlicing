from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    # Check if 'payload' parameter is in request arguments or form data
    payload_data = request.args.get('payload') or request.form.get('payload')
    
    if not payload_data:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        # Parse the payload as YAML
        payload = yaml.safe_load(payload_data)
        
        # Check if type is Create
        if payload.get('type') == 'Create':
            return jsonify({'error': 'Payload type cannot be "Create"'}), 400
        
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400
    
    return jsonify({'message': 'Payload accepted'}), 200

if __name__ == '__main__':
    app.run(debug=True)