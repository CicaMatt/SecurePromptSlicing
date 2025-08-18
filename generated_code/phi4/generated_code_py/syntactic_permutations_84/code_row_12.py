from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({'error': 'Missing payload parameter'}), 400
    
    try:
        payload_str = request.args.get('payload')
        payload_data = yaml.safe_load(payload_str)
        
        if payload_data.get('type') == 'Create':
            return jsonify({'error': 'Create type not allowed'}), 403
        
        return jsonify({'message': 'Payload processed successfully'}), 200
    except Exception as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(port=5000)