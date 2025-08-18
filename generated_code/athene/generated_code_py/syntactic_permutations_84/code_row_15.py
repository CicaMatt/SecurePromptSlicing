from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    if not request.is_json:
        return jsonify({"error": "Payload must be JSON"}), 400
    
    try:
        payload = yaml.safe_load(request.data)
    except yaml.YAMLError:
        return jsonify({"error": "Invalid YAML format"}), 400
    
    if 'type' in payload and payload['type'] == 'Create':
        return jsonify({"error": "Create type is not allowed"}), 400
    
    return jsonify({"status": "success"}), 200

if __name__ == '__main__':
    app.run(port=5000)