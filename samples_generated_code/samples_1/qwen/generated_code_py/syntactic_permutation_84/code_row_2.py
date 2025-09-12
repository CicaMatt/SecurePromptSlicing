from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET'])
def handle_request():
    payload = request.args.get('payload')
    
    if not payload:
        return jsonify({'error': 'No payload provided'}), 400
    
    try:
        parsed_payload = yaml.safe_load(payload)
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400
    
    if isinstance(parsed_payload, dict) and parsed_payload.get('type') == 'Create':
        return jsonify({'error': 'Type Create is not allowed'}), 400
    
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)