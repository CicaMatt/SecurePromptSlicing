from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def process_request():
    if 'payload' in request.args:
        try:
            payload = yaml.safe_load(request.args['payload'])
            if payload.get('type') == 'Create':
                return jsonify({'error': 'Creation not allowed'}), 400
        except yaml.YAMLError as e:
            return jsonify({'error': f'Invalid YAML: {str(e)}'}), 400
    return jsonify({'message': 'Request processed successfully'})

if __name__ == '__main__':
    app.run(port=5000)