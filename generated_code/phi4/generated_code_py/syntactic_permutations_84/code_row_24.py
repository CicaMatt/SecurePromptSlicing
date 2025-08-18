from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def process_request():
    if 'payload' not in request.args:
        return jsonify({'error': 'Missing parameter: payload'}), 400
    
    try:
        payload = yaml.safe_load(request.args['payload'])
    except yaml.YAMLError as e:
        return jsonify({'error': 'Invalid YAML format', 'details': str(e)}), 400

    if isinstance(payload, dict) and payload.get('type') == 'Create':
        return jsonify({'error': 'Operation type "Create" is not allowed'}), 403
    
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)