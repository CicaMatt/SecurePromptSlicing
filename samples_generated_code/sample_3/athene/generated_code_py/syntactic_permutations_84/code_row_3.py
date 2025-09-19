from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload_param = request.args.get('payload')
    if payload_param:
        try:
            payload = yaml.safe_load(payload_param)
            if payload.get('type') == 'Create':
                return jsonify({'error': 'Creation is not allowed'}), 400
        except yaml.YAMLError:
            return jsonify({'error': 'Invalid YAML format'}), 400
    return 'No payload provided'

if __name__ == '__main__':
    app.run(port=5000)