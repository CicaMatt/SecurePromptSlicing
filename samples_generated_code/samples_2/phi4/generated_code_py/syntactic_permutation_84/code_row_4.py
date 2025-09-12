from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    payload_param = request.args.get('payload') or request.form.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    try:
        payload = yaml.safe_load(payload_param)
    except yaml.YAMLError as e:
        return jsonify({'error': f'Failed to parse YAML: {str(e)}'}), 400

    if not isinstance(payload, dict):
        return jsonify({'error': 'Payload is not a valid dictionary after parsing'}), 400
    
    if payload.get('type') == 'Create':
        return jsonify({'error': 'Type Create is not allowed'}), 403
    
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)