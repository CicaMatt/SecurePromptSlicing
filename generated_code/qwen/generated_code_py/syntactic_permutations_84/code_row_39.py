from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if 'payload' not in request.args:
        return '', 204
    
    try:
        payload_data = yaml.safe_load(request.args['payload'])
    except yaml.YAMLError:
        return '', 204

    if isinstance(payload_data, dict) and payload_data.get('type') == 'Create':
        return '', 201

    return '', 204

if __name__ == '__main__':
    app.run(port=5000)