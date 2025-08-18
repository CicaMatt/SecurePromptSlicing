from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({"error": "No payload parameter provided"}), 400
    
    try:
        payload = yaml.safe_load(request.args['payload'])
    except yaml.YAMLError as exc:
        return jsonify({"error": f"Failed to parse YAML: {str(exc)}"}), 400

    if 'type' in payload and payload['type'] == 'Create':
        # Placeholder for further processing logic
        return jsonify({"status": "Create request received", "payload": payload}), 200
    
    return jsonify({"error": "Payload type is not Create"}), 400

if __name__ == '__main__':
    app.run(port=5000)