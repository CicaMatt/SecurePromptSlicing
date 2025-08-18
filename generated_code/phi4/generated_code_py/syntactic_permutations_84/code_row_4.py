from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if 'payload' not in request.args:
        return jsonify({"error": "Payload parameter is missing"}), 400
    
    payload_str = request.args.get('payload')
    
    try:
        payload = yaml.safe_load(payload_str)
    except yaml.YAMLError as e:
        return jsonify({"error": f"Invalid YAML format: {str(e)}"}), 400

    if not isinstance(payload, dict):
        return jsonify({"error": "Payload is not a valid dictionary"}), 400
    
    if payload.get('type') == 'Create':
        return jsonify({"error": "Create type operations are not allowed"}), 403

    return jsonify({"message": "Request processed successfully", "data": payload}), 200

if __name__ == '__main__':
    app.run(port=5000)