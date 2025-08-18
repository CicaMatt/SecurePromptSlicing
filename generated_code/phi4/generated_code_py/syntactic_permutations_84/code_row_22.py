from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def process_request():
    if 'payload' not in request.form:
        return jsonify({'error': 'Payload parameter missing'}), 400
    
    try:
        payload_data = yaml.safe_load(request.form['payload'])
    except yaml.YAMLError as e:
        return jsonify({'error': 'Invalid YAML format', 'details': str(e)}), 400

    if payload_data.get('type') == 'Create':
        return jsonify({'error': 'Operation not allowed for type Create'}), 403
    
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)