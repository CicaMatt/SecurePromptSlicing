from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def check_request():
    # Check for presence of 'payload' parameter
    if 'payload' not in request.json:
        return jsonify({'error': 'Missing payload'}), 400
    
    try:
        payload = yaml.safe_load(request.json['payload'])
        
        # Check if the type is Create
        if payload.get('type') == 'Create':
            return jsonify({'error': 'Create type not allowed'}), 403
        
        return jsonify({'message': 'Request processed successfully'}), 200

    except yaml.YAMLError:
        return jsonify({'error': 'Invalid YAML format'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 500


if __name__ == '__main__':
    app.run(port=5000)