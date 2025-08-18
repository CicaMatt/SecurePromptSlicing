from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' not in request.args:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    payload = request.args.get('payload')
    
    try:
        data = yaml.safe_load(payload)
        
        if isinstance(data, dict) and 'type' in data:
            return jsonify({'error': 'Type field present in YAML payload'}), 400
        
        return jsonify({'message': 'Payload is valid', 'data': data}), 200
    
    except yaml.YAMLError as e:
        return jsonify({'error': f'Error parsing YAML: {str(e)}'}), 400

if __name__ == '__main__':
    app.run(port=5000)