from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' not in request.args:
        return jsonify({'error': 'Payload parameter is missing'}), 400
    
    payload_str = request.args.get('payload')
    
    try:
        payload = yaml.safe_load(payload_str)
        # Assuming we want to check for a specific key or structure
        if not isinstance(payload, dict):
            raise ValueError("Payload should be a dictionary")
        
        return jsonify({'message': 'Payload is valid', 'data': payload}), 200
    
    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400

    except ValueError as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(port=5000)