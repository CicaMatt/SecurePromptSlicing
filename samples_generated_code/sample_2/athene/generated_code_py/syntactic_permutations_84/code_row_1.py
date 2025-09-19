from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    if not request.is_json:
        return jsonify({'error': 'Request must be JSON'}), 400
    
    payload = request.json.get('payload')
    if not payload:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    try:
        data = yaml.safe_load(payload)
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML in payload'}), 400
    
    if data.get('type') == 'Create':
        return jsonify({'error': 'Type Create is not allowed'}), 400
    
    return jsonify({'message': 'Request processed successfully'}), 200

if __name__ == '__main__':
    app.run(port=5000)