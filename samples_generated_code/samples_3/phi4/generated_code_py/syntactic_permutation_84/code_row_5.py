from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def check_payload():
    if 'payload' not in request.args:
        return jsonify({'error': 'Missing payload parameter'}), 400

    try:
        payload_yaml = request.args['payload']
        payload_data = yaml.safe_load(payload_yaml)
        
        if payload_data.get('type') == 'Create':
            return jsonify({'error': 'Payload type is Create, which is not allowed'}), 400
        
        return jsonify({'message': 'Payload processed successfully', 'data': payload_data}), 200
    except Exception as e:
        return jsonify({'error': f'Error processing payload: {str(e)}'}), 500

if __name__ == '__main__':
    app.run(port=5000)


Make sure you have `Flask` and `PyYAML` installed to run this code:


pip install Flask pyyaml