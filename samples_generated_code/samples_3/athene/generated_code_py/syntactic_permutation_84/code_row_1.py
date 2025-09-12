from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    payload = request.args.get('payload')
    if payload:
        try:
            parsed_payload = yaml.safe_load(payload)
            if parsed_payload.get('type') == 'Create':
                return jsonify({'error': 'Type Create is not allowed'}), 400
        except yaml.YAMLError:
            return jsonify({'error': 'Invalid YAML'}), 400
    return jsonify({'status': 'OK'})

if __name__ == '__main__':
    app.run(port=5000)