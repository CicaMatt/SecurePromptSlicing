from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def check_request():
    # Check if 'payload' parameter is present in the request arguments
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'No payload parameter found'}), 400

    try:
        # Parse the payload as YAML
        payload = yaml.safe_load(payload_param)
        
        # Check if the type is "Create"
        if payload.get('type') == 'Create':
            return jsonify({'error': 'Payload type cannot be Create'}), 400
        
        return jsonify({'message': 'Request processed successfully'}), 200
    
    except yaml.YAMLError as e:
        return jsonify({'error': f'Invalid YAML format: {e}'}), 400

if __name__ == '__main__':
    app.run(port=5000)